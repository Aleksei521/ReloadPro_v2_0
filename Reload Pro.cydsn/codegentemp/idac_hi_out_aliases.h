/*******************************************************************************
* File Name: idac_hi_out.h  
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

#if !defined(CY_PINS_idac_hi_out_ALIASES_H) /* Pins idac_hi_out_ALIASES_H */
#define CY_PINS_idac_hi_out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define idac_hi_out_0			(idac_hi_out__0__PC)
#define idac_hi_out_0_PS		(idac_hi_out__0__PS)
#define idac_hi_out_0_PC		(idac_hi_out__0__PC)
#define idac_hi_out_0_DR		(idac_hi_out__0__DR)
#define idac_hi_out_0_SHIFT	(idac_hi_out__0__SHIFT)
#define idac_hi_out_0_INTR	((uint16)((uint16)0x0003u << (idac_hi_out__0__SHIFT*2u)))

#define idac_hi_out_INTR_ALL	 ((uint16)(idac_hi_out_0_INTR))


#endif /* End Pins idac_hi_out_ALIASES_H */


/* [] END OF FILE */
