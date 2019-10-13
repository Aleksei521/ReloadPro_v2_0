/*******************************************************************************
* File Name: tach.h  
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

#if !defined(CY_PINS_tach_ALIASES_H) /* Pins tach_ALIASES_H */
#define CY_PINS_tach_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define tach_0			(tach__0__PC)
#define tach_0_PS		(tach__0__PS)
#define tach_0_PC		(tach__0__PC)
#define tach_0_DR		(tach__0__DR)
#define tach_0_SHIFT	(tach__0__SHIFT)
#define tach_0_INTR	((uint16)((uint16)0x0003u << (tach__0__SHIFT*2u)))

#define tach_INTR_ALL	 ((uint16)(tach_0_INTR))


#endif /* End Pins tach_ALIASES_H */


/* [] END OF FILE */
