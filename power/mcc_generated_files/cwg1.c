/**
   CWG1 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cwg1.c
 
   @Summary
     This is the generated driver implementation file for the CWG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for CWG1.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
         Device            :  PIC10F322
         Driver Version    :  2.01
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.00 or later
         MPLAB             :  MPLAB X 5.10
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
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "cwg1.h"

/**
  Section: CWG1 APIs
*/

void CWG1_Initialize(void)
{
    // Set the CWG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G1IS PWM1OUT; G1ASDLA driven_low; G1ASDLB driven_low; 
    CWG1CON1 = 0xA0;

    // G1ARSEN disabled; G1ASDSCLC1 disabled; G1ASDSFLT disabled; G1ASE no_auto_shutdown; 
    CWG1CON2 = 0x00;

    // CWG1DBR 16to17_counts; 
    CWG1DBR = 0x10;

    // CWG1DBF 0_counts; 
    CWG1DBF = 0x00;

    // G1EN enabled; G1POLB normal_polarity; G1OEB disabled; G1POLA normal_polarity; G1OEA disabled; G1CS0 FOSC; 
    CWG1CON0 = 0x80;

}

void CWG1_LoadRiseDeadbandCount(uint8_t dutyValue)
{
    CWG1DBR = dutyValue;
}

void CWG1_LoadFallDeadbandCount(uint8_t dutyValue)
{
    CWG1DBF = dutyValue;
}

void CWG1_AutoShutdownEventSet()
{
    CWG1CON2bits.G1ASE = 1;
}

void CWG1_AutoShutdownEventClear()
{
    CWG1CON2bits.G1ASE = 0;
}
/**
 End of File
*/
