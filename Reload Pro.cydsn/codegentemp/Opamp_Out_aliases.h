/*******************************************************************************
* File Name: Opamp_Out.h  
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

#if !defined(CY_PINS_Opamp_Out_ALIASES_H) /* Pins Opamp_Out_ALIASES_H */
#define CY_PINS_Opamp_Out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Opamp_Out_0			(Opamp_Out__0__PC)
#define Opamp_Out_0_PS		(Opamp_Out__0__PS)
#define Opamp_Out_0_PC		(Opamp_Out__0__PC)
#define Opamp_Out_0_DR		(Opamp_Out__0__DR)
#define Opamp_Out_0_SHIFT	(Opamp_Out__0__SHIFT)
#define Opamp_Out_0_INTR	((uint16)((uint16)0x0003u << (Opamp_Out__0__SHIFT*2u)))

#define Opamp_Out_INTR_ALL	 ((uint16)(Opamp_Out_0_INTR))


#endif /* End Pins Opamp_Out_ALIASES_H */


/* [] END OF FILE */
