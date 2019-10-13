/*******************************************************************************
* File Name: Gate_Sense_Low.h  
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

#if !defined(CY_PINS_Gate_Sense_Low_ALIASES_H) /* Pins Gate_Sense_Low_ALIASES_H */
#define CY_PINS_Gate_Sense_Low_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Gate_Sense_Low_0			(Gate_Sense_Low__0__PC)
#define Gate_Sense_Low_0_PS		(Gate_Sense_Low__0__PS)
#define Gate_Sense_Low_0_PC		(Gate_Sense_Low__0__PC)
#define Gate_Sense_Low_0_DR		(Gate_Sense_Low__0__DR)
#define Gate_Sense_Low_0_SHIFT	(Gate_Sense_Low__0__SHIFT)
#define Gate_Sense_Low_0_INTR	((uint16)((uint16)0x0003u << (Gate_Sense_Low__0__SHIFT*2u)))

#define Gate_Sense_Low_INTR_ALL	 ((uint16)(Gate_Sense_Low_0_INTR))


#endif /* End Pins Gate_Sense_Low_ALIASES_H */


/* [] END OF FILE */
