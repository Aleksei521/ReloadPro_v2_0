/*******************************************************************************
* File Name: Voltage_Sense.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Voltage_Sense.h"

static Voltage_Sense_BACKUP_STRUCT  Voltage_Sense_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Voltage_Sense_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Voltage_Sense_SUT.c usage_Voltage_Sense_Sleep_Wakeup
*******************************************************************************/
void Voltage_Sense_Sleep(void)
{
    #if defined(Voltage_Sense__PC)
        Voltage_Sense_backup.pcState = Voltage_Sense_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Voltage_Sense_backup.usbState = Voltage_Sense_CR1_REG;
            Voltage_Sense_USB_POWER_REG |= Voltage_Sense_USBIO_ENTER_SLEEP;
            Voltage_Sense_CR1_REG &= Voltage_Sense_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Voltage_Sense__SIO)
        Voltage_Sense_backup.sioState = Voltage_Sense_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Voltage_Sense_SIO_REG &= (uint32)(~Voltage_Sense_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Voltage_Sense_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Voltage_Sense_Sleep() for an example usage.
*******************************************************************************/
void Voltage_Sense_Wakeup(void)
{
    #if defined(Voltage_Sense__PC)
        Voltage_Sense_PC = Voltage_Sense_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Voltage_Sense_USB_POWER_REG &= Voltage_Sense_USBIO_EXIT_SLEEP_PH1;
            Voltage_Sense_CR1_REG = Voltage_Sense_backup.usbState;
            Voltage_Sense_USB_POWER_REG &= Voltage_Sense_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Voltage_Sense__SIO)
        Voltage_Sense_SIO_REG = Voltage_Sense_backup.sioState;
    #endif
}


/* [] END OF FILE */
