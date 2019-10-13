 /**
   CWG1 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    cwg1.h

   @Summary
     This is the generated header file for the CWG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This header file provides APIs for driver for CWG1.
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

#ifndef CWG1_H
 #define CWG1_H
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: CWG1 APIs
*/

/**
  @Summary
    Initializes the CWG1

  @Description
    This routine configures the CWG1 specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment


  @Example
    <code>
    CWG1_Initialize();
    </code>
*/
void CWG1_Initialize(void);

/**
  @Summary
    This function will write the rising dead band count into CWG registers

  @Description
    This function can be used to modify rising dead band count of CWG on the fly

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    value - 6 bit digital rising dead band count to CWG.

  @Example
    <code>
    uint8_t MyDutyValue;

    CWG1_Initialize();
    
    // Do something
   
    CWG1_LoadRiseDeadbandCount(MyDutyValue);
    </code>
*/
void CWG1_LoadRiseDeadbandCount(uint8_t dutyValue);

/**
  @Summary
    This function will write the falling dead band count into CWG registers

  @Description
    This function can be used to modify falling dead band count of CWG on the fly

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    value - 6 bit digital falling dead band count to CWG.

  @Example
    <code>
    uint8_t MyDutyValue;

    CWG1_initialize();
    
    // Do something
    
    CWG1_LoadFallDeadbandCount(MyDutyValue);
    </code>
*/
void CWG1_LoadFallDeadbandCount(uint8_t dutyValue);

/**
  @Summary
    Software generated Shutdown

  @Description
    This function forces the CWG into Shutdown state.

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG1_Initialize();
    
    // Do something
    
    CWG1_AutoShutdownEventSet();
    </code>
*/
void CWG1_AutoShutdownEventSet();

/**
  @Summary
    This function makes the CWG to resume its operations from the software
    generated shutdown state.

  @Description
    When auto-restart is disabled, the shutdown state will persist as long as the
    GxASE bit is set and hence to resume operations, this function should be used.

    However when auto-restart is enabled, the GxASE bit will clear automatically
    and resume operation on the next rising edge event. In that case, there is no
    need to call this function.

  @Preconditions
    CWG1_Initialize() and CWG1_AutoShutdownEventSet() functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG1_Initialize();
    
    // Do something
    
    CWG1_AutoShutdownEventSet();

    // Do something
    
    CWG1_AutoShutdownEventClear();
    </code>
*/
void CWG1_AutoShutdownEventClear();

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // CWG1_H
/**
 End of File
*/