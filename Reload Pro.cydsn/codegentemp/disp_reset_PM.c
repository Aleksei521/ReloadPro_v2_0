/*******************************************************************************
* File Name: disp_reset.c  
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
#include "disp_reset.h"

static disp_reset_BACKUP_STRUCT  disp_reset_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: disp_reset_Sleep
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
*  \snippet disp_reset_SUT.c usage_disp_reset_Sleep_Wakeup
*******************************************************************************/
void disp_reset_Sleep(void)
{
    #if defined(disp_reset__PC)
        disp_reset_backup.pcState = disp_reset_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            disp_reset_backup.usbState = disp_reset_CR1_REG;
            disp_reset_USB_POWER_REG |= disp_reset_USBIO_ENTER_SLEEP;
            disp_reset_CR1_REG &= disp_reset_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(disp_reset__SIO)
        disp_reset_backup.sioState = disp_reset_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        disp_reset_SIO_REG &= (uint32)(~disp_reset_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: disp_reset_Wakeup
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
*  Refer to disp_reset_Sleep() for an example usage.
*******************************************************************************/
void disp_reset_Wakeup(void)
{
    #if defined(disp_reset__PC)
        disp_reset_PC = disp_reset_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            disp_reset_USB_POWER_REG &= disp_reset_USBIO_EXIT_SLEEP_PH1;
            disp_reset_CR1_REG = disp_reset_backup.usbState;
            disp_reset_USB_POWER_REG &= disp_reset_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(disp_reset__SIO)
        disp_reset_SIO_REG = disp_reset_backup.sioState;
    #endif
}


/* [] END OF FILE */
