/*******************************************************************************
* File Name: Temperuture.h  
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

#if !defined(CY_PINS_Temperuture_ALIASES_H) /* Pins Temperuture_ALIASES_H */
#define CY_PINS_Temperuture_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Temperuture_0			(Temperuture__0__PC)
#define Temperuture_0_PS		(Temperuture__0__PS)
#define Temperuture_0_PC		(Temperuture__0__PC)
#define Temperuture_0_DR		(Temperuture__0__DR)
#define Temperuture_0_SHIFT	(Temperuture__0__SHIFT)
#define Temperuture_0_INTR	((uint16)((uint16)0x0003u << (Temperuture__0__SHIFT*2u)))

#define Temperuture_INTR_ALL	 ((uint16)(Temperuture_0_INTR))


#endif /* End Pins Temperuture_ALIASES_H */


/* [] END OF FILE */
