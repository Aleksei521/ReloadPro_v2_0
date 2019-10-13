/*******************************************************************************
* File Name: fan.h  
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

#if !defined(CY_PINS_fan_ALIASES_H) /* Pins fan_ALIASES_H */
#define CY_PINS_fan_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define fan_0			(fan__0__PC)
#define fan_0_PS		(fan__0__PS)
#define fan_0_PC		(fan__0__PC)
#define fan_0_DR		(fan__0__DR)
#define fan_0_SHIFT	(fan__0__SHIFT)
#define fan_0_INTR	((uint16)((uint16)0x0003u << (fan__0__SHIFT*2u)))

#define fan_INTR_ALL	 ((uint16)(fan_0_INTR))


#endif /* End Pins fan_ALIASES_H */


/* [] END OF FILE */
