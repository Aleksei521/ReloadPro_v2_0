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

#if !defined(CY_SCB_PVT_Display_I2C_H)
#define CY_SCB_PVT_Display_I2C_H

#include "Display_I2C.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Display_I2C_SetI2CExtClkInterruptMode(interruptMask) Display_I2C_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Display_I2C_ClearI2CExtClkInterruptSource(interruptMask) Display_I2C_CLEAR_INTR_I2C_EC(interruptMask)
#define Display_I2C_GetI2CExtClkInterruptSource()                (Display_I2C_INTR_I2C_EC_REG)
#define Display_I2C_GetI2CExtClkInterruptMode()                  (Display_I2C_INTR_I2C_EC_MASK_REG)
#define Display_I2C_GetI2CExtClkInterruptSourceMasked()          (Display_I2C_INTR_I2C_EC_MASKED_REG)

#if (!Display_I2C_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Display_I2C_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Display_I2C_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Display_I2C_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Display_I2C_CLEAR_INTR_SPI_EC(interruptMask)
    #define Display_I2C_GetExtSpiClkInterruptSource()                 (Display_I2C_INTR_SPI_EC_REG)
    #define Display_I2C_GetExtSpiClkInterruptMode()                   (Display_I2C_INTR_SPI_EC_MASK_REG)
    #define Display_I2C_GetExtSpiClkInterruptSourceMasked()           (Display_I2C_INTR_SPI_EC_MASKED_REG)
#endif /* (!Display_I2C_CY_SCBIP_V1) */

#if(Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Display_I2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (Display_I2C_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER)
    extern cyisraddress Display_I2C_customIntrHandler;
#endif /* !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER) */
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */

extern Display_I2C_BACKUP_STRUCT Display_I2C_backup;

#if(Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Display_I2C_scbMode;
    extern uint8 Display_I2C_scbEnableWake;
    extern uint8 Display_I2C_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Display_I2C_mode;
    extern uint8 Display_I2C_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Display_I2C_rxBuffer;
    extern uint8   Display_I2C_rxDataBits;
    extern uint32  Display_I2C_rxBufferSize;

    extern volatile uint8 * Display_I2C_txBuffer;
    extern uint8   Display_I2C_txDataBits;
    extern uint32  Display_I2C_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Display_I2C_numberOfAddr;
    extern uint8 Display_I2C_subAddrSize;
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (Display_I2C_SCB_MODE_I2C_CONST_CFG || \
        Display_I2C_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 Display_I2C_IntrTxMask;
#endif /* (! (Display_I2C_SCB_MODE_I2C_CONST_CFG || \
              Display_I2C_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Display_I2C_SCB_MODE_I2C_RUNTM_CFG     (Display_I2C_SCB_MODE_I2C      == Display_I2C_scbMode)
    #define Display_I2C_SCB_MODE_SPI_RUNTM_CFG     (Display_I2C_SCB_MODE_SPI      == Display_I2C_scbMode)
    #define Display_I2C_SCB_MODE_UART_RUNTM_CFG    (Display_I2C_SCB_MODE_UART     == Display_I2C_scbMode)
    #define Display_I2C_SCB_MODE_EZI2C_RUNTM_CFG   (Display_I2C_SCB_MODE_EZI2C    == Display_I2C_scbMode)
    #define Display_I2C_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Display_I2C_SCB_MODE_UNCONFIG == Display_I2C_scbMode)

    /* Defines wakeup enable */
    #define Display_I2C_SCB_WAKE_ENABLE_CHECK       (0u != Display_I2C_scbEnableWake)
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Display_I2C_CY_SCBIP_V1)
    #define Display_I2C_SCB_PINS_NUMBER    (7u)
#else
    #define Display_I2C_SCB_PINS_NUMBER    (2u)
#endif /* (!Display_I2C_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Display_I2C_H) */


/* [] END OF FILE */
