/***************************************************************************//**
* \file LCD_G77_1_I2C_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_LCD_G77_1_I2C_H)
#define CY_SCB_BOOT_LCD_G77_1_I2C_H

#include "LCD_G77_1_I2C_PVT.h"

#if (LCD_G77_1_I2C_SCB_MODE_I2C_INC)
    #include "LCD_G77_1_I2C_I2C.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_I2C_INC) */

#if (LCD_G77_1_I2C_SCB_MODE_EZI2C_INC)
    #include "LCD_G77_1_I2C_EZI2C.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_EZI2C_INC) */

#if (LCD_G77_1_I2C_SCB_MODE_SPI_INC || LCD_G77_1_I2C_SCB_MODE_UART_INC)
    #include "LCD_G77_1_I2C_SPI_UART.h"
#endif /* (LCD_G77_1_I2C_SCB_MODE_SPI_INC || LCD_G77_1_I2C_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define LCD_G77_1_I2C_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_G77_1_I2C) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (LCD_G77_1_I2C_SCB_MODE_I2C_INC)
    #define LCD_G77_1_I2C_I2C_BTLDR_COMM_ENABLED     (LCD_G77_1_I2C_BTLDR_COMM_ENABLED && \
                                                            (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LCD_G77_1_I2C_I2C_SLAVE_CONST))
#else
     #define LCD_G77_1_I2C_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (LCD_G77_1_I2C_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (LCD_G77_1_I2C_SCB_MODE_EZI2C_INC)
    #define LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED   (LCD_G77_1_I2C_BTLDR_COMM_ENABLED && \
                                                         LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (LCD_G77_1_I2C_SCB_MODE_SPI_INC)
    #define LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED     (LCD_G77_1_I2C_BTLDR_COMM_ENABLED && \
                                                            (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LCD_G77_1_I2C_SPI_SLAVE_CONST))
#else
        #define LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (LCD_G77_1_I2C_SCB_MODE_UART_INC)
       #define LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED    (LCD_G77_1_I2C_BTLDR_COMM_ENABLED && \
                                                            (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (LCD_G77_1_I2C_UART_RX_DIRECTION && \
                                                              LCD_G77_1_I2C_UART_TX_DIRECTION)))
#else
     #define LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define LCD_G77_1_I2C_BTLDR_COMM_MODE_ENABLED    (LCD_G77_1_I2C_I2C_BTLDR_COMM_ENABLED   || \
                                                     LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED   || \
                                                     LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED || \
                                                     LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void LCD_G77_1_I2C_I2CCyBtldrCommStart(void);
    void LCD_G77_1_I2C_I2CCyBtldrCommStop (void);
    void LCD_G77_1_I2C_I2CCyBtldrCommReset(void);
    cystatus LCD_G77_1_I2C_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCD_G77_1_I2C_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG)
        #define LCD_G77_1_I2C_CyBtldrCommStart   LCD_G77_1_I2C_I2CCyBtldrCommStart
        #define LCD_G77_1_I2C_CyBtldrCommStop    LCD_G77_1_I2C_I2CCyBtldrCommStop
        #define LCD_G77_1_I2C_CyBtldrCommReset   LCD_G77_1_I2C_I2CCyBtldrCommReset
        #define LCD_G77_1_I2C_CyBtldrCommRead    LCD_G77_1_I2C_I2CCyBtldrCommRead
        #define LCD_G77_1_I2C_CyBtldrCommWrite   LCD_G77_1_I2C_I2CCyBtldrCommWrite
    #endif /* (LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void LCD_G77_1_I2C_EzI2CCyBtldrCommStart(void);
    void LCD_G77_1_I2C_EzI2CCyBtldrCommStop (void);
    void LCD_G77_1_I2C_EzI2CCyBtldrCommReset(void);
    cystatus LCD_G77_1_I2C_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCD_G77_1_I2C_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG)
        #define LCD_G77_1_I2C_CyBtldrCommStart   LCD_G77_1_I2C_EzI2CCyBtldrCommStart
        #define LCD_G77_1_I2C_CyBtldrCommStop    LCD_G77_1_I2C_EzI2CCyBtldrCommStop
        #define LCD_G77_1_I2C_CyBtldrCommReset   LCD_G77_1_I2C_EzI2CCyBtldrCommReset
        #define LCD_G77_1_I2C_CyBtldrCommRead    LCD_G77_1_I2C_EzI2CCyBtldrCommRead
        #define LCD_G77_1_I2C_CyBtldrCommWrite   LCD_G77_1_I2C_EzI2CCyBtldrCommWrite
    #endif /* (LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void LCD_G77_1_I2C_SpiCyBtldrCommStart(void);
    void LCD_G77_1_I2C_SpiCyBtldrCommStop (void);
    void LCD_G77_1_I2C_SpiCyBtldrCommReset(void);
    cystatus LCD_G77_1_I2C_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCD_G77_1_I2C_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG)
        #define LCD_G77_1_I2C_CyBtldrCommStart   LCD_G77_1_I2C_SpiCyBtldrCommStart
        #define LCD_G77_1_I2C_CyBtldrCommStop    LCD_G77_1_I2C_SpiCyBtldrCommStop
        #define LCD_G77_1_I2C_CyBtldrCommReset   LCD_G77_1_I2C_SpiCyBtldrCommReset
        #define LCD_G77_1_I2C_CyBtldrCommRead    LCD_G77_1_I2C_SpiCyBtldrCommRead
        #define LCD_G77_1_I2C_CyBtldrCommWrite   LCD_G77_1_I2C_SpiCyBtldrCommWrite
    #endif /* (LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void LCD_G77_1_I2C_UartCyBtldrCommStart(void);
    void LCD_G77_1_I2C_UartCyBtldrCommStop (void);
    void LCD_G77_1_I2C_UartCyBtldrCommReset(void);
    cystatus LCD_G77_1_I2C_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LCD_G77_1_I2C_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG)
        #define LCD_G77_1_I2C_CyBtldrCommStart   LCD_G77_1_I2C_UartCyBtldrCommStart
        #define LCD_G77_1_I2C_CyBtldrCommStop    LCD_G77_1_I2C_UartCyBtldrCommStop
        #define LCD_G77_1_I2C_CyBtldrCommReset   LCD_G77_1_I2C_UartCyBtldrCommReset
        #define LCD_G77_1_I2C_CyBtldrCommRead    LCD_G77_1_I2C_UartCyBtldrCommRead
        #define LCD_G77_1_I2C_CyBtldrCommWrite   LCD_G77_1_I2C_UartCyBtldrCommWrite
    #endif /* (LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_BTLDR_COMM_ENABLED)
    #if (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void LCD_G77_1_I2C_CyBtldrCommStart(void);
        void LCD_G77_1_I2C_CyBtldrCommStop (void);
        void LCD_G77_1_I2C_CyBtldrCommReset(void);
        cystatus LCD_G77_1_I2C_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus LCD_G77_1_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_G77_1_I2C)
        #define CyBtldrCommStart    LCD_G77_1_I2C_CyBtldrCommStart
        #define CyBtldrCommStop     LCD_G77_1_I2C_CyBtldrCommStop
        #define CyBtldrCommReset    LCD_G77_1_I2C_CyBtldrCommReset
        #define CyBtldrCommWrite    LCD_G77_1_I2C_CyBtldrCommWrite
        #define CyBtldrCommRead     LCD_G77_1_I2C_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_G77_1_I2C) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LCD_G77_1_I2C_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define LCD_G77_1_I2C_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define LCD_G77_1_I2C_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define LCD_G77_1_I2C_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define LCD_G77_1_I2C_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef LCD_G77_1_I2C_SPI_BYTE_TO_BYTE
    #define LCD_G77_1_I2C_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef LCD_G77_1_I2C_UART_BYTE_TO_BYTE
    #define LCD_G77_1_I2C_UART_BYTE_TO_BYTE  (2500u)
#endif /* LCD_G77_1_I2C_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_LCD_G77_1_I2C_H) */


/* [] END OF FILE */
