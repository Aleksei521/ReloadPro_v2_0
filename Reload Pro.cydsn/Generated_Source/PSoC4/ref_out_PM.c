/*******************************************************************************
* File Name: ref_out.c  
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
#include "ref_out.h"

static ref_out_BACKUP_STRUCT  ref_out_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ref_out_Sleep
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
*  \snippet ref_out_SUT.c usage_ref_out_Sleep_Wakeup
*******************************************************************************/
void ref_out_Sleep(void)
{
    #if defined(ref_out__PC)
        ref_out_backup.pcState = ref_out_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ref_out_backup.usbState = ref_out_CR1_REG;
            ref_out_USB_POWER_REG |= ref_out_USBIO_ENTER_SLEEP;
            ref_out_CR1_REG &= ref_out_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ref_out__SIO)
        ref_out_backup.sioState = ref_out_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ref_out_SIO_REG &= (uint32)(~ref_out_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ref_out_Wakeup
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
*  Refer to ref_out_Sleep() for an example usage.
*******************************************************************************/
void ref_out_Wakeup(void)
{
    #if defined(ref_out__PC)
        ref_out_PC = ref_out_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ref_out_USB_POWER_REG &= ref_out_USBIO_EXIT_SLEEP_PH1;
            ref_out_CR1_REG = ref_out_backup.usbState;
            ref_out_USB_POWER_REG &= ref_out_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ref_out__SIO)
        ref_out_SIO_REG = ref_out_backup.sioState;
    #endif
}


/* [] END OF FILE */
