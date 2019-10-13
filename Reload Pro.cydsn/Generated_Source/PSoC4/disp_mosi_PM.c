/*******************************************************************************
* File Name: disp_mosi.c  
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
#include "disp_mosi.h"

static disp_mosi_BACKUP_STRUCT  disp_mosi_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: disp_mosi_Sleep
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
*  \snippet disp_mosi_SUT.c usage_disp_mosi_Sleep_Wakeup
*******************************************************************************/
void disp_mosi_Sleep(void)
{
    #if defined(disp_mosi__PC)
        disp_mosi_backup.pcState = disp_mosi_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            disp_mosi_backup.usbState = disp_mosi_CR1_REG;
            disp_mosi_USB_POWER_REG |= disp_mosi_USBIO_ENTER_SLEEP;
            disp_mosi_CR1_REG &= disp_mosi_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(disp_mosi__SIO)
        disp_mosi_backup.sioState = disp_mosi_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        disp_mosi_SIO_REG &= (uint32)(~disp_mosi_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: disp_mosi_Wakeup
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
*  Refer to disp_mosi_Sleep() for an example usage.
*******************************************************************************/
void disp_mosi_Wakeup(void)
{
    #if defined(disp_mosi__PC)
        disp_mosi_PC = disp_mosi_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            disp_mosi_USB_POWER_REG &= disp_mosi_USBIO_EXIT_SLEEP_PH1;
            disp_mosi_CR1_REG = disp_mosi_backup.usbState;
            disp_mosi_USB_POWER_REG &= disp_mosi_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(disp_mosi__SIO)
        disp_mosi_SIO_REG = disp_mosi_backup.sioState;
    #endif
}


/* [] END OF FILE */
