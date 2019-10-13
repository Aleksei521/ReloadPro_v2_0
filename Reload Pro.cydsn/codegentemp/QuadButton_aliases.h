/*******************************************************************************
* File Name: QuadButton.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_QuadButton_ALIASES_H) /* Pins QuadButton_ALIASES_H */
#define CY_PINS_QuadButton_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define QuadButton_0			(QuadButton__0__PC)
#define QuadButton_0_PS		(QuadButton__0__PS)
#define QuadButton_0_PC		(QuadButton__0__PC)
#define QuadButton_0_DR		(QuadButton__0__DR)
#define QuadButton_0_SHIFT	(QuadButton__0__SHIFT)
#define QuadButton_0_INTR	((uint16)((uint16)0x0003u << (QuadButton__0__SHIFT*2u)))

#define QuadButton_INTR_ALL	 ((uint16)(QuadButton_0_INTR))


#endif /* End Pins QuadButton_ALIASES_H */


/* [] END OF FILE */
