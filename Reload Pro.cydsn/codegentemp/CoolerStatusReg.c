/*******************************************************************************
* File Name: CoolerStatusReg.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "CoolerStatusReg.h"

#if !defined(CoolerStatusReg_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: CoolerStatusReg_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 CoolerStatusReg_Read(void) 
{ 
    return CoolerStatusReg_Status;
}


/*******************************************************************************
* Function Name: CoolerStatusReg_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CoolerStatusReg_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    CoolerStatusReg_Status_Aux_Ctrl |= CoolerStatusReg_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CoolerStatusReg_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void CoolerStatusReg_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    CoolerStatusReg_Status_Aux_Ctrl &= (uint8)(~CoolerStatusReg_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CoolerStatusReg_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void CoolerStatusReg_WriteMask(uint8 mask) 
{
    #if(CoolerStatusReg_INPUTS < 8u)
    	mask &= ((uint8)(1u << CoolerStatusReg_INPUTS) - 1u);
	#endif /* End CoolerStatusReg_INPUTS < 8u */
    CoolerStatusReg_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: CoolerStatusReg_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 CoolerStatusReg_ReadMask(void) 
{
    return CoolerStatusReg_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
