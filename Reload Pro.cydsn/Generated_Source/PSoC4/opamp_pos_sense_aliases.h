/*******************************************************************************
* File Name: opamp_pos_sense.h  
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

#if !defined(CY_PINS_opamp_pos_sense_ALIASES_H) /* Pins opamp_pos_sense_ALIASES_H */
#define CY_PINS_opamp_pos_sense_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define opamp_pos_sense_0			(opamp_pos_sense__0__PC)
#define opamp_pos_sense_0_PS		(opamp_pos_sense__0__PS)
#define opamp_pos_sense_0_PC		(opamp_pos_sense__0__PC)
#define opamp_pos_sense_0_DR		(opamp_pos_sense__0__DR)
#define opamp_pos_sense_0_SHIFT	(opamp_pos_sense__0__SHIFT)
#define opamp_pos_sense_0_INTR	((uint16)((uint16)0x0003u << (opamp_pos_sense__0__SHIFT*2u)))

#define opamp_pos_sense_INTR_ALL	 ((uint16)(opamp_pos_sense_0_INTR))


#endif /* End Pins opamp_pos_sense_ALIASES_H */


/* [] END OF FILE */
