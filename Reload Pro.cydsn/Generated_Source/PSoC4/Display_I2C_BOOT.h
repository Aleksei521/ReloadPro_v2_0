/***************************************************************************//**
* \file Display_I2C_BOOT.h
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

#if !defined(CY_SCB_BOOT_Display_I2C_H)
#define CY_SCB_BOOT_Display_I2C_H

#include "Display_I2C_PVT.h"

#if (Display_I2C_SCB_MODE_I2C_INC)
    #include "Display_I2C_I2C.h"
#endif /* (Display_I2C_SCB_MODE_I2C_INC) */

#if (Display_I2C_SCB_MODE_EZI2C_INC)
    #include "Display_I2C_EZI2C.h"
#endif /* (Display_I2C_SCB_MODE_EZI2C_INC) */

#if (Display_I2C_SCB_MODE_SPI_INC || Display_I2C_SCB_MODE_UART_INC)
    #include "Display_I2C_SPI_UART.h"
#endif /* (Display_I2C_SCB_MODE_SPI_INC || Display_I2C_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define Display_I2C_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Display_I2C) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (Display_I2C_SCB_MODE_I2C_INC)
    #define Display_I2C_I2C_BTLDR_COMM_ENABLED     (Display_I2C_BTLDR_COMM_ENABLED && \
                                                            (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Display_I2C_I2C_SLAVE_CONST))
#else
     #define Display_I2C_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (Display_I2C_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (Display_I2C_SCB_MODE_EZI2C_INC)
    #define Display_I2C_EZI2C_BTLDR_COMM_ENABLED   (Display_I2C_BTLDR_COMM_ENABLED && \
                                                         Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define Display_I2C_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Display_I2C_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (Display_I2C_SCB_MODE_SPI_INC)
    #define Display_I2C_SPI_BTLDR_COMM_ENABLED     (Display_I2C_BTLDR_COMM_ENABLED && \
                                                            (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Display_I2C_SPI_SLAVE_CONST))
#else
        #define Display_I2C_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (Display_I2C_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (Display_I2C_SCB_MODE_UART_INC)
       #define Display_I2C_UART_BTLDR_COMM_ENABLED    (Display_I2C_BTLDR_COMM_ENABLED && \
                                                            (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (Display_I2C_UART_RX_DIRECTION && \
                                                              Display_I2C_UART_TX_DIRECTION)))
#else
     #define Display_I2C_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (Display_I2C_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define Display_I2C_BTLDR_COMM_MODE_ENABLED    (Display_I2C_I2C_BTLDR_COMM_ENABLED   || \
                                                     Display_I2C_SPI_BTLDR_COMM_ENABLED   || \
                                                     Display_I2C_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Display_I2C_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void Display_I2C_I2CCyBtldrCommStart(void);
    void Display_I2C_I2CCyBtldrCommStop (void);
    void Display_I2C_I2CCyBtldrCommReset(void);
    cystatus Display_I2C_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Display_I2C_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (Display_I2C_SCB_MODE_I2C_CONST_CFG)
        #define Display_I2C_CyBtldrCommStart   Display_I2C_I2CCyBtldrCommStart
        #define Display_I2C_CyBtldrCommStop    Display_I2C_I2CCyBtldrCommStop
        #define Display_I2C_CyBtldrCommReset   Display_I2C_I2CCyBtldrCommReset
        #define Display_I2C_CyBtldrCommRead    Display_I2C_I2CCyBtldrCommRead
        #define Display_I2C_CyBtldrCommWrite   Display_I2C_I2CCyBtldrCommWrite
    #endif /* (Display_I2C_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Display_I2C_EzI2CCyBtldrCommStart(void);
    void Display_I2C_EzI2CCyBtldrCommStop (void);
    void Display_I2C_EzI2CCyBtldrCommReset(void);
    cystatus Display_I2C_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Display_I2C_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (Display_I2C_SCB_MODE_EZI2C_CONST_CFG)
        #define Display_I2C_CyBtldrCommStart   Display_I2C_EzI2CCyBtldrCommStart
        #define Display_I2C_CyBtldrCommStop    Display_I2C_EzI2CCyBtldrCommStop
        #define Display_I2C_CyBtldrCommReset   Display_I2C_EzI2CCyBtldrCommReset
        #define Display_I2C_CyBtldrCommRead    Display_I2C_EzI2CCyBtldrCommRead
        #define Display_I2C_CyBtldrCommWrite   Display_I2C_EzI2CCyBtldrCommWrite
    #endif /* (Display_I2C_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Display_I2C_SpiCyBtldrCommStart(void);
    void Display_I2C_SpiCyBtldrCommStop (void);
    void Display_I2C_SpiCyBtldrCommReset(void);
    cystatus Display_I2C_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Display_I2C_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (Display_I2C_SCB_MODE_SPI_CONST_CFG)
        #define Display_I2C_CyBtldrCommStart   Display_I2C_SpiCyBtldrCommStart
        #define Display_I2C_CyBtldrCommStop    Display_I2C_SpiCyBtldrCommStop
        #define Display_I2C_CyBtldrCommReset   Display_I2C_SpiCyBtldrCommReset
        #define Display_I2C_CyBtldrCommRead    Display_I2C_SpiCyBtldrCommRead
        #define Display_I2C_CyBtldrCommWrite   Display_I2C_SpiCyBtldrCommWrite
    #endif /* (Display_I2C_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Display_I2C_UartCyBtldrCommStart(void);
    void Display_I2C_UartCyBtldrCommStop (void);
    void Display_I2C_UartCyBtldrCommReset(void);
    cystatus Display_I2C_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Display_I2C_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (Display_I2C_SCB_MODE_UART_CONST_CFG)
        #define Display_I2C_CyBtldrCommStart   Display_I2C_UartCyBtldrCommStart
        #define Display_I2C_CyBtldrCommStop    Display_I2C_UartCyBtldrCommStop
        #define Display_I2C_CyBtldrCommReset   Display_I2C_UartCyBtldrCommReset
        #define Display_I2C_CyBtldrCommRead    Display_I2C_UartCyBtldrCommRead
        #define Display_I2C_CyBtldrCommWrite   Display_I2C_UartCyBtldrCommWrite
    #endif /* (Display_I2C_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_BTLDR_COMM_ENABLED)
    #if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void Display_I2C_CyBtldrCommStart(void);
        void Display_I2C_CyBtldrCommStop (void);
        void Display_I2C_CyBtldrCommReset(void);
        cystatus Display_I2C_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Display_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Display_I2C)
        #define CyBtldrCommStart    Display_I2C_CyBtldrCommStart
        #define CyBtldrCommStop     Display_I2C_CyBtldrCommStop
        #define CyBtldrCommReset    Display_I2C_CyBtldrCommReset
        #define CyBtldrCommWrite    Display_I2C_CyBtldrCommWrite
        #define CyBtldrCommRead     Display_I2C_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Display_I2C) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Display_I2C_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define Display_I2C_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define Display_I2C_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define Display_I2C_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define Display_I2C_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef Display_I2C_SPI_BYTE_TO_BYTE
    #define Display_I2C_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef Display_I2C_UART_BYTE_TO_BYTE
    #define Display_I2C_UART_BYTE_TO_BYTE  (2500u)
#endif /* Display_I2C_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_Display_I2C_H) */


/* [] END OF FILE */
