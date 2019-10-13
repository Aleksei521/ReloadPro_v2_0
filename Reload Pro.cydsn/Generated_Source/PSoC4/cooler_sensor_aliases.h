/*******************************************************************************
* File Name: cooler_sensor.h  
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

#if !defined(CY_PINS_cooler_sensor_ALIASES_H) /* Pins cooler_sensor_ALIASES_H */
#define CY_PINS_cooler_sensor_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cooler_sensor_0			(cooler_sensor__0__PC)
#define cooler_sensor_0_PS		(cooler_sensor__0__PS)
#define cooler_sensor_0_PC		(cooler_sensor__0__PC)
#define cooler_sensor_0_DR		(cooler_sensor__0__DR)
#define cooler_sensor_0_SHIFT	(cooler_sensor__0__SHIFT)
#define cooler_sensor_0_INTR	((uint16)((uint16)0x0003u << (cooler_sensor__0__SHIFT*2u)))

#define cooler_sensor_INTR_ALL	 ((uint16)(cooler_sensor_0_INTR))


#endif /* End Pins cooler_sensor_ALIASES_H */


/* [] END OF FILE */
