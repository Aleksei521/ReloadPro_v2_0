/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_LCD_G77_1_I2C_H)
#define CY_SCB_PVT_LCD_G77_1_I2C_H

#include "LCD_G77_1_I2C.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define LCD_G77_1_I2C_SetI2CExtClkInterruptMode(interruptMask) LCD_G77_1_I2C_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define LCD_G77_1_I2C_ClearI2CExtClkInterruptSource(interruptMask) LCD_G77_1_I2C_CLEAR_INTR_I2C_EC(interruptMask)
#define LCD_G77_1_I2C_GetI2CExtClkInterruptSource()                (LCD_G77_1_I2C_INTR_I2C_EC_REG)
#define LCD_G77_1_I2C_GetI2CExtClkInterruptMode()                  (LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG)
#define LCD_G77_1_I2C_GetI2CExtClkInterruptSourceMasked()          (LCD_G77_1_I2C_INTR_I2C_EC_MASKED_REG)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define LCD_G77_1_I2C_SetSpiExtClkInterruptMode(interruptMask) \
                                                                LCD_G77_1_I2C_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define LCD_G77_1_I2C_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                LCD_G77_1_I2C_CLEAR_INTR_SPI_EC(interruptMask)
    #define LCD_G77_1_I2C_GetExtSpiClkInterruptSource()                 (LCD_G77_1_I2C_INTR_SPI_EC_REG)
    #define LCD_G77_1_I2C_GetExtSpiClkInterruptMode()                   (LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG)
    #define LCD_G77_1_I2C_GetExtSpiClkInterruptSourceMasked()           (LCD_G77_1_I2C_INTR_SPI_EC_MASKED_REG)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void LCD_G77_1_I2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (LCD_G77_1_I2C_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LCD_G77_1_I2C_CUSTOM_INTR_HANDLER)
    extern cyisraddress LCD_G77_1_I2C_customIntrHandler;
#endif /* !defined (CY_REMOVE_LCD_G77_1_I2C_CUSTOM_INTR_HANDLER) */
#endif /* (LCD_G77_1_I2C_SCB_IRQ_INTERNAL) */

extern LCD_G77_1_I2C_BACKUP_STRUCT LCD_G77_1_I2C_backup;

#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 LCD_G77_1_I2C_scbMode;
    extern uint8 LCD_G77_1_I2C_scbEnableWake;
    extern uint8 LCD_G77_1_I2C_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 LCD_G77_1_I2C_mode;
    extern uint8 LCD_G77_1_I2C_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * LCD_G77_1_I2C_rxBuffer;
    extern uint8   LCD_G77_1_I2C_rxDataBits;
    extern uint32  LCD_G77_1_I2C_rxBufferSize;

    extern volatile uint8 * LCD_G77_1_I2C_txBuffer;
    extern uint8   LCD_G77_1_I2C_txDataBits;
    extern uint32  LCD_G77_1_I2C_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 LCD_G77_1_I2C_numberOfAddr;
    extern uint8 LCD_G77_1_I2C_subAddrSize;
#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG || \
        LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 LCD_G77_1_I2C_IntrTxMask;
#endif /* (! (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG || \
              LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define LCD_G77_1_I2C_SCB_MODE_I2C_RUNTM_CFG     (LCD_G77_1_I2C_SCB_MODE_I2C      == LCD_G77_1_I2C_scbMode)
    #define LCD_G77_1_I2C_SCB_MODE_SPI_RUNTM_CFG     (LCD_G77_1_I2C_SCB_MODE_SPI      == LCD_G77_1_I2C_scbMode)
    #define LCD_G77_1_I2C_SCB_MODE_UART_RUNTM_CFG    (LCD_G77_1_I2C_SCB_MODE_UART     == LCD_G77_1_I2C_scbMode)
    #define LCD_G77_1_I2C_SCB_MODE_EZI2C_RUNTM_CFG   (LCD_G77_1_I2C_SCB_MODE_EZI2C    == LCD_G77_1_I2C_scbMode)
    #define LCD_G77_1_I2C_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (LCD_G77_1_I2C_SCB_MODE_UNCONFIG == LCD_G77_1_I2C_scbMode)

    /* Defines wakeup enable */
    #define LCD_G77_1_I2C_SCB_WAKE_ENABLE_CHECK       (0u != LCD_G77_1_I2C_scbEnableWake)
#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_SCB_PINS_NUMBER    (7u)
#else
    #define LCD_G77_1_I2C_SCB_PINS_NUMBER    (2u)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_LCD_G77_1_I2C_H) */


/* [] END OF FILE */
