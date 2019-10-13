/*******************************************************************************
* File Name: Backlight.c  
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
#include "Backlight.h"

static Backlight_BACKUP_STRUCT  Backlight_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Backlight_Sleep
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
*  \snippet Backlight_SUT.c usage_Backlight_Sleep_Wakeup
*******************************************************************************/
void Backlight_Sleep(void)
{
    #if defined(Backlight__PC)
        Backlight_backup.pcState = Backlight_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Backlight_backup.usbState = Backlight_CR1_REG;
            Backlight_USB_POWER_REG |= Backlight_USBIO_ENTER_SLEEP;
            Backlight_CR1_REG &= Backlight_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Backlight__SIO)
        Backlight_backup.sioState = Backlight_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Backlight_SIO_REG &= (uint32)(~Backlight_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Backlight_Wakeup
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
*  Refer to Backlight_Sleep() for an example usage.
*******************************************************************************/
void Backlight_Wakeup(void)
{
    #if defined(Backlight__PC)
        Backlight_PC = Backlight_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Backlight_USB_POWER_REG &= Backlight_USBIO_EXIT_SLEEP_PH1;
            Backlight_CR1_REG = Backlight_backup.usbState;
            Backlight_USB_POWER_REG &= Backlight_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Backlight__SIO)
        Backlight_SIO_REG = Backlight_backup.sioState;
    #endif
}


/* [] END OF FILE */
