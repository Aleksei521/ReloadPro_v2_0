/***************************************************************************//**
* \file LCD_G77_1_I2C_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_G77_1_I2C.h"
#include "LCD_G77_1_I2C_PVT.h"

#if(LCD_G77_1_I2C_SCB_MODE_I2C_INC)
    #include "LCD_G77_1_I2C_I2C_PVT.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_I2C_INC) */

#if(LCD_G77_1_I2C_SCB_MODE_EZI2C_INC)
    #include "LCD_G77_1_I2C_EZI2C_PVT.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_EZI2C_INC) */

#if(LCD_G77_1_I2C_SCB_MODE_SPI_INC || LCD_G77_1_I2C_SCB_MODE_UART_INC)
    #include "LCD_G77_1_I2C_SPI_UART_PVT.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_SPI_INC || LCD_G77_1_I2C_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
   (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG   && (!LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST))   || \
   (LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG && (!LCD_G77_1_I2C_EZI2C_WAKE_ENABLE_CONST)) || \
   (LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG   && (!LCD_G77_1_I2C_SPI_WAKE_ENABLE_CONST))   || \
   (LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG  && (!LCD_G77_1_I2C_UART_WAKE_ENABLE_CONST)))

    LCD_G77_1_I2C_BACKUP_STRUCT LCD_G77_1_I2C_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_Sleep
****************************************************************************//**
*
*  Prepares the LCD_G77_1_I2C component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the LCD_G77_1_I2C_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void LCD_G77_1_I2C_Sleep(void)
{
#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCD_G77_1_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCD_G77_1_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCD_G77_1_I2C_I2CSaveConfig();
        }
        else if(LCD_G77_1_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCD_G77_1_I2C_EzI2CSaveConfig();
        }
    #if(!LCD_G77_1_I2C_CY_SCBIP_V1)
        else if(LCD_G77_1_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCD_G77_1_I2C_SpiSaveConfig();
        }
        else if(LCD_G77_1_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            LCD_G77_1_I2C_UartSaveConfig();
        }
    #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        LCD_G77_1_I2C_backup.enableState = (uint8) LCD_G77_1_I2C_GET_CTRL_ENABLED;

        if(0u != LCD_G77_1_I2C_backup.enableState)
        {
            LCD_G77_1_I2C_Stop();
        }
    }

#else

    #if (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG && LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_I2CSaveConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG && LCD_G77_1_I2C_EZI2C_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_EzI2CSaveConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG && LCD_G77_1_I2C_SPI_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_SpiSaveConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG && LCD_G77_1_I2C_UART_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_UartSaveConfig();

    #else

        LCD_G77_1_I2C_backup.enableState = (uint8) LCD_G77_1_I2C_GET_CTRL_ENABLED;

        if(0u != LCD_G77_1_I2C_backup.enableState)
        {
            LCD_G77_1_I2C_Stop();
        }

    #endif /* defined (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG) && (LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_Wakeup
****************************************************************************//**
*
*  Prepares the LCD_G77_1_I2C component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the LCD_G77_1_I2C_Wakeup() function without first calling the 
*   LCD_G77_1_I2C_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void LCD_G77_1_I2C_Wakeup(void)
{
#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LCD_G77_1_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(LCD_G77_1_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            LCD_G77_1_I2C_I2CRestoreConfig();
        }
        else if(LCD_G77_1_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LCD_G77_1_I2C_EzI2CRestoreConfig();
        }
    #if(!LCD_G77_1_I2C_CY_SCBIP_V1)
        else if(LCD_G77_1_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            LCD_G77_1_I2C_SpiRestoreConfig();
        }
        else if(LCD_G77_1_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            LCD_G77_1_I2C_UartRestoreConfig();
        }
    #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != LCD_G77_1_I2C_backup.enableState)
        {
            LCD_G77_1_I2C_Enable();
        }
    }

#else

    #if (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG  && LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_I2CRestoreConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG && LCD_G77_1_I2C_EZI2C_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_EzI2CRestoreConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG && LCD_G77_1_I2C_SPI_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_SpiRestoreConfig();

    #elif (LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG && LCD_G77_1_I2C_UART_WAKE_ENABLE_CONST)
        LCD_G77_1_I2C_UartRestoreConfig();

    #else

        if(0u != LCD_G77_1_I2C_backup.enableState)
        {
            LCD_G77_1_I2C_Enable();
        }

    #endif /* (LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
