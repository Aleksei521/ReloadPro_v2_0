/*******************************************************************************
* File Name: Quadrature.h  
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

#if !defined(CY_PINS_Quadrature_ALIASES_H) /* Pins Quadrature_ALIASES_H */
#define CY_PINS_Quadrature_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Quadrature_0			(Quadrature__0__PC)
#define Quadrature_0_PS		(Quadrature__0__PS)
#define Quadrature_0_PC		(Quadrature__0__PC)
#define Quadrature_0_DR		(Quadrature__0__DR)
#define Quadrature_0_SHIFT	(Quadrature__0__SHIFT)
#define Quadrature_0_INTR	((uint16)((uint16)0x0003u << (Quadrature__0__SHIFT*2u)))

#define Quadrature_1			(Quadrature__1__PC)
#define Quadrature_1_PS		(Quadrature__1__PS)
#define Quadrature_1_PC		(Quadrature__1__PC)
#define Quadrature_1_DR		(Quadrature__1__DR)
#define Quadrature_1_SHIFT	(Quadrature__1__SHIFT)
#define Quadrature_1_INTR	((uint16)((uint16)0x0003u << (Quadrature__1__SHIFT*2u)))

#define Quadrature_INTR_ALL	 ((uint16)(Quadrature_0_INTR| Quadrature_1_INTR))


#endif /* End Pins Quadrature_ALIASES_H */


/* [] END OF FILE */
