/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PI16 / PIC18 MCUs - 1.76
        Device            :  PIC10F322
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <limits.h>

#define PWM_1_MAX 78//������������ �������� ��� PWM1DC
#define PWM_1_MIN 16//����������� �������� ��� PWM1DC
#define PWM_2_MAX 160//������������ �������� ��� PWM2DC
#define DUTY_AVG ((PWM_1_MAX-PWM_1_MIN)/2+PWM_1_MIN)
//��� ��������� ����� ��� ���� ����� ������������ ����� ��������
//������������ �������� �������� �������� �������� ����� , � �� �� 0
#define PID_KP_SHIFT 3// ����������� ���������������� ������������
#define PID_KI_SHIFT 4// ����������� ������������ ������������
#define PID_KD_SHIFT 3// ����������� ���������������� ������������
#define PID_REF 127//���������� ������������ ��� ���
#define ISUM_MAX (PWM_1_MAX<<PID_KI_SHIFT)//������������ ������������ �����
//���� �� ������� ������� �������, ��� ��������� ����� ����� �����������������
//����� ��������� ����������� � ���������
#define ISUM_MIN ((ISUM_MAX-DUTY_AVG)*(-1))//����������� ������������ �����
//���� �� ������� ������� ���������, ��� ��������� ����� ����� �����������������
//����� ��������� ����������� � ��������

struct pid_flags{
    unsigned char data_ready :1;//���� ���������� ������ ��� ��������� �������� ����� PWM1,PWM2
    unsigned char pwm2_on :1;//��� ���������� ������������ ��������� ����� ������ ����������������
    //��� ��������� �������� PWM2 ����� �������� � ����� CWG ����. ����� ������� ������������ TMR2,
    //������ PWM2 � CWG ������������ � ������� ���������������� � ��������������� ���� ����.
    unsigned char pid_d_ini :1;//���� ������������� ����������� �������
    //����� ������������� ��������������� � 1.
};
struct{
    volatile struct pid_flags flags;
    int16_t isum;//������������ ������������
    signed int e;//������
    signed int e_m;//������ �� ���������� �����
    signed int duty;//������� ����
    volatile unsigned char h_2;//������� ���� �������� ����� PWM2
    volatile unsigned char l_2;//������� ���� �������� ����� PWM2
    volatile unsigned char h_1;//������� ���� �������� ����� PWM1
    volatile unsigned char l_1;//������� ���� �������� ����� PWM1
}pid={{0,0,0},0,0,0,PWM_1_MIN+1,0,0,0,0};

void set_duty(void);
void __interrupt tmr2_isr(void);

void __interrupt tmr2_isr(void)
{
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF=0;
        if(!pid.flags.pwm2_on)//��������� �� ������ ��������� � ����������
        {
            pid.flags.pwm2_on=1;//���� ������, ������������� ����
            PWM2CON = 0xD0;//�������� ����� PWM2
            CWG1CON0 = 0xA0;//�������� ����� CWG
        }
        if(pid.flags.data_ready)//���� ���� ����� ������ �������� ����� ����������
        {//������ � �������� �������� ����� PWM1, PWM2 ����� ������
        PWM1DCH =pid.h_1;
        PWM1DCL =pid.l_1;
        PWM2DCH =pid.h_2;
        PWM2DCL =pid.l_2;
        pid.flags.data_ready=0;//����� �������� ���������� ����
        }
    }
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    set_duty();//������������� ������� ����

    PIE1bits.TMR2IE=1;

    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;

    while (1)
    {
        // Add your application code
        CLRWDT();
        if(INTCONbits.TMR0IF)//��������� ���� ������������ TMR0
        {
            INTCONbits.TMR0IF=0;//���� ������������ ����, ���������� ����
            pid.e=PID_REF-(signed int)ADC_GetConversion(channel_AN2);//��������� ������
            if(!pid.flags.pid_d_ini) //���� ���� ������������� ����������� ������� �������
            {
                pid.flags.pid_d_ini=1;//������������� ����
                pid.e_m=pid.e;//�������������� ���������� ������
            }
            pid.duty=(pid.e>>PID_KP_SHIFT);//��������� ���������������� ������������
            if((pid.isum>0 && pid.e <0) || (pid.isum<0 && pid.e >0) || ((pid.isum<ISUM_MAX) && (pid.isum>ISUM_MIN)))
                //��������� ������������ ����� �� ���������
                pid.isum+=(int32_t)(pid.e);//���� ��������� ���, ��������� ������� ������
            pid.duty+=(signed int)(pid.isum>>PID_KI_SHIFT);//��������� ������������ ������������
            pid.duty+=((pid.e-pid.e_m)>>PID_KD_SHIFT)+DUTY_AVG;//��������� ���������������� ������������
            pid.e_m=pid.e;//��������� ������� ������  � ������� ����������� �������
            set_duty();//������ ������� ���� PWM1 � PWM2
        }
    }
}

void set_duty(void)
{
    unsigned int tmp;
    while(pid.flags.data_ready);//���� ����� � ���������� TMR2 ��������� ���������� ������
    if(pid.duty>PWM_1_MAX) pid.duty=PWM_1_MAX;//��������� �� ����� �� ������� �������� �������� ����� 
    if(pid.duty<PWM_1_MIN) pid.duty=PWM_1_MIN;
    pid.h_1 = ((unsigned int)pid.duty & 0x03FC)>>2;//��������� ������ ��� PWM1
    pid.l_1 = ((unsigned int)pid.duty & 0x0003)<<6;
    tmp=PWM_2_MAX-(unsigned int)pid.duty+PWM_1_MIN;
    pid.h_2 = (tmp & 0x3FC)>>2;//��������� ������ ��� PWM2
    pid.l_2 = (tmp & 0x3)<<6;
    pid.flags.data_ready=1;//������������� ���� ���������� ������ �������� �����
    
}

/**
 End of File
*/