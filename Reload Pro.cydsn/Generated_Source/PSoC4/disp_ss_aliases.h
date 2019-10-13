/*******************************************************************************
* File Name: disp_ss.h  
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

#if !defined(CY_PINS_disp_ss_ALIASES_H) /* Pins disp_ss_ALIASES_H */
#define CY_PINS_disp_ss_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define disp_ss_0			(disp_ss__0__PC)
#define disp_ss_0_PS		(disp_ss__0__PS)
#define disp_ss_0_PC		(disp_ss__0__PC)
#define disp_ss_0_DR		(disp_ss__0__DR)
#define disp_ss_0_SHIFT	(disp_ss__0__SHIFT)
#define disp_ss_0_INTR	((uint16)((uint16)0x0003u << (disp_ss__0__SHIFT*2u)))

#define disp_ss_INTR_ALL	 ((uint16)(disp_ss_0_INTR))


#endif /* End Pins disp_ss_ALIASES_H */


/* [] END OF FILE */
