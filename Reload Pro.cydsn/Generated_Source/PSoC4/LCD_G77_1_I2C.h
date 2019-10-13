/***************************************************************************//**
* \file LCD_G77_1_I2C.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the SCB Component.
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

#if !defined(CY_SCB_LCD_G77_1_I2C_H)
#define CY_SCB_LCD_G77_1_I2C_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define LCD_G77_1_I2C_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define LCD_G77_1_I2C_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define LCD_G77_1_I2C_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

/** Component version major.minor */
#define LCD_G77_1_I2C_COMP_VERSION_MAJOR    (4)
#define LCD_G77_1_I2C_COMP_VERSION_MINOR    (0)
    
#define LCD_G77_1_I2C_SCB_MODE           (1u)

/* SCB modes enum */
#define LCD_G77_1_I2C_SCB_MODE_I2C       (0x01u)
#define LCD_G77_1_I2C_SCB_MODE_SPI       (0x02u)
#define LCD_G77_1_I2C_SCB_MODE_UART      (0x04u)
#define LCD_G77_1_I2C_SCB_MODE_EZI2C     (0x08u)
#define LCD_G77_1_I2C_SCB_MODE_UNCONFIG  (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define LCD_G77_1_I2C_SCB_MODE_I2C_CONST_CFG       (LCD_G77_1_I2C_SCB_MODE_I2C       == LCD_G77_1_I2C_SCB_MODE)
#define LCD_G77_1_I2C_SCB_MODE_SPI_CONST_CFG       (LCD_G77_1_I2C_SCB_MODE_SPI       == LCD_G77_1_I2C_SCB_MODE)
#define LCD_G77_1_I2C_SCB_MODE_UART_CONST_CFG      (LCD_G77_1_I2C_SCB_MODE_UART      == LCD_G77_1_I2C_SCB_MODE)
#define LCD_G77_1_I2C_SCB_MODE_EZI2C_CONST_CFG     (LCD_G77_1_I2C_SCB_MODE_EZI2C     == LCD_G77_1_I2C_SCB_MODE)
#define LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG  (LCD_G77_1_I2C_SCB_MODE_UNCONFIG  == LCD_G77_1_I2C_SCB_MODE)

/* Condition compilation for includes */
#define LCD_G77_1_I2C_SCB_MODE_I2C_INC      (0u !=(LCD_G77_1_I2C_SCB_MODE_I2C   & LCD_G77_1_I2C_SCB_MODE))
#define LCD_G77_1_I2C_SCB_MODE_EZI2C_INC    (0u !=(LCD_G77_1_I2C_SCB_MODE_EZI2C & LCD_G77_1_I2C_SCB_MODE))
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_SCB_MODE_SPI_INC  (0u !=(LCD_G77_1_I2C_SCB_MODE_SPI   & LCD_G77_1_I2C_SCB_MODE))
    #define LCD_G77_1_I2C_SCB_MODE_UART_INC (0u !=(LCD_G77_1_I2C_SCB_MODE_UART  & LCD_G77_1_I2C_SCB_MODE))
#else
    #define LCD_G77_1_I2C_SCB_MODE_SPI_INC  (0u)
    #define LCD_G77_1_I2C_SCB_MODE_UART_INC (0u)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

/* Interrupts remove options */
#define LCD_G77_1_I2C_REMOVE_SCB_IRQ             (0u)
#define LCD_G77_1_I2C_SCB_IRQ_INTERNAL           (0u == LCD_G77_1_I2C_REMOVE_SCB_IRQ)

#define LCD_G77_1_I2C_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define LCD_G77_1_I2C_UART_RX_WAKEUP_IRQ         (0u == LCD_G77_1_I2C_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define LCD_G77_1_I2C_SCB_INTR_MODE_NONE     (0u)
#define LCD_G77_1_I2C_SCB_INTR_MODE_INTERNAL (1u)
#define LCD_G77_1_I2C_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define LCD_G77_1_I2C_REMOVE_SCB_CLK     (0u)
#define LCD_G77_1_I2C_SCB_CLK_INTERNAL   (0u == LCD_G77_1_I2C_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "LCD_G77_1_I2C_PINS.h"

#if (LCD_G77_1_I2C_SCB_CLK_INTERNAL)
    #include "LCD_G77_1_I2C_SCBCLK.h"
#endif /* (LCD_G77_1_I2C_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} LCD_G77_1_I2C_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/* Start and Stop APIs */
void LCD_G77_1_I2C_Init(void);
void LCD_G77_1_I2C_Enable(void);
void LCD_G77_1_I2C_Start(void);
void LCD_G77_1_I2C_Stop(void);

/** @} general */

/**
* \addtogroup group_power
* @{
*/
/* Sleep and Wakeup APis */
void LCD_G77_1_I2C_Sleep(void);
void LCD_G77_1_I2C_Wakeup(void);
/** @} power */ 

/**
* \addtogroup group_interrupt
* @{
*/
#if (LCD_G77_1_I2C_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void LCD_G77_1_I2C_SetCustomInterruptHandler(void (*func)(void));
#endif /* (LCD_G77_1_I2C_SCB_IRQ_INTERNAL) */
/** @} interrupt */

/* Interface to internal interrupt component */
#if (LCD_G77_1_I2C_SCB_IRQ_INTERNAL)
    /**
    * \addtogroup group_interrupt
    * @{
    */    
    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_EnableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this enables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to enable the interrupt.
    *
    *******************************************************************************/
    #define LCD_G77_1_I2C_EnableInt()    CyIntEnable(LCD_G77_1_I2C_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_DisableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this disables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to disable the interrupt.
    *
    *******************************************************************************/    
    #define LCD_G77_1_I2C_DisableInt()   CyIntDisable(LCD_G77_1_I2C_ISR_NUMBER)
    /** @} interrupt */

    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_ClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt pending status in the NVIC. 
    *
    *******************************************************************************/
    #define LCD_G77_1_I2C_ClearPendingInt()  CyIntClearPending(LCD_G77_1_I2C_ISR_NUMBER)
#endif /* (LCD_G77_1_I2C_SCB_IRQ_INTERNAL) */

#if (LCD_G77_1_I2C_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_RxWakeEnableInt
    ****************************************************************************//**
    *
    *  This function enables the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define LCD_G77_1_I2C_RxWakeEnableInt()  CyIntEnable(LCD_G77_1_I2C_RX_WAKE_ISR_NUMBER)
    

    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_RxWakeDisableInt
    ****************************************************************************//**
    *
    *  This function disables the interrupt (RX_WAKE) pending status in the NVIC.  
    *
    *******************************************************************************/
    #define LCD_G77_1_I2C_RxWakeDisableInt() CyIntDisable(LCD_G77_1_I2C_RX_WAKE_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_RxWakeClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define LCD_G77_1_I2C_RxWakeClearPendingInt()  CyIntClearPending(LCD_G77_1_I2C_RX_WAKE_ISR_NUMBER)
#endif /* (LCD_G77_1_I2C_UART_RX_WAKEUP_IRQ) */

/**
* \addtogroup group_interrupt
* @{
*/
/* Get interrupt cause */
/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetInterruptCause
****************************************************************************//**
*
*  Returns a mask of bits showing the source of the current triggered interrupt. 
*  This is useful for modes of operation where an interrupt can be generated by 
*  conditions in multiple interrupt source registers.
*
*  \return
*   Mask with the OR of the following conditions that have been triggered.
*    - LCD_G77_1_I2C_INTR_CAUSE_MASTER - Interrupt from Master
*    - LCD_G77_1_I2C_INTR_CAUSE_SLAVE - Interrupt from Slave
*    - LCD_G77_1_I2C_INTR_CAUSE_TX - Interrupt from TX
*    - LCD_G77_1_I2C_INTR_CAUSE_RX - Interrupt from RX
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetInterruptCause()    (LCD_G77_1_I2C_INTR_CAUSE_REG)


/* APIs to service INTR_RX register */
/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetRxInterruptSource
****************************************************************************//**
*
*  Returns RX interrupt request register. This register contains current status 
*  of RX interrupt sources.
*
*  \return
*   Current status of RX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCD_G77_1_I2C_INTR_RX_FIFO_LEVEL - The number of data elements in the 
      RX FIFO is greater than the value of RX FIFO level.
*   - LCD_G77_1_I2C_INTR_RX_NOT_EMPTY - Receiver FIFO is not empty.
*   - LCD_G77_1_I2C_INTR_RX_FULL - Receiver FIFO is full.
*   - LCD_G77_1_I2C_INTR_RX_OVERFLOW - Attempt to write to a full 
*     receiver FIFO.
*   - LCD_G77_1_I2C_INTR_RX_UNDERFLOW - Attempt to read from an empty 
*     receiver FIFO.
*   - LCD_G77_1_I2C_INTR_RX_FRAME_ERROR - UART framing error detected.
*   - LCD_G77_1_I2C_INTR_RX_PARITY_ERROR - UART parity error detected.
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetRxInterruptSource() (LCD_G77_1_I2C_INTR_RX_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetRxInterruptMode
****************************************************************************//**
*
*  Writes RX interrupt mask register. This register configures which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: RX interrupt sources to be enabled (refer to 
*   LCD_G77_1_I2C_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetRxInterruptMode(interruptMask)     LCD_G77_1_I2C_WRITE_INTR_RX_MASK(interruptMask)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetRxInterruptMode
****************************************************************************//**
*
*  Returns RX interrupt mask register This register specifies which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \return 
*   RX interrupt sources to be enabled (refer to 
*   LCD_G77_1_I2C_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetRxInterruptMode()   (LCD_G77_1_I2C_INTR_RX_MASK_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetRxInterruptSourceMasked
****************************************************************************//**
*
*  Returns RX interrupt masked request register. This register contains logical
*  AND of corresponding bits from RX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled RX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled RX interrupt sources (refer to 
*   LCD_G77_1_I2C_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetRxInterruptSourceMasked()   (LCD_G77_1_I2C_INTR_RX_MASKED_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_ClearRxInterruptSource
****************************************************************************//**
*
*  Clears RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to be cleared (refer to 
*   LCD_G77_1_I2C_GetRxInterruptSource() function for bit fields values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each 
*   affected interrupt source. Refer to section RX FIFO interrupt sources for 
*   detailed description.
*   - LCD_G77_1_I2C_INTR_RX_FIFO_LEVEL Interrupt source is not cleared when 
*     the receiver FIFO has more entries than level.
*   - LCD_G77_1_I2C_INTR_RX_NOT_EMPTY Interrupt source is not cleared when
*     receiver FIFO is not empty.
*   - LCD_G77_1_I2C_INTR_RX_FULL Interrupt source is not cleared when 
*      receiver FIFO is full.
*
*******************************************************************************/
#define LCD_G77_1_I2C_ClearRxInterruptSource(interruptMask)  LCD_G77_1_I2C_CLEAR_INTR_RX(interruptMask)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetRxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to LCD_G77_1_I2C_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetRxInterrupt(interruptMask)  LCD_G77_1_I2C_SET_INTR_RX(interruptMask)

void LCD_G77_1_I2C_SetRxFifoLevel(uint32 level);


/* APIs to service INTR_TX register */
/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetTxInterruptSource
****************************************************************************//**
*
*  Returns TX interrupt request register. This register contains current status 
*  of TX interrupt sources.
* 
*  \return 
*   Current status of TX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCD_G77_1_I2C_INTR_TX_FIFO_LEVEL - The number of data elements in the 
*     TX FIFO is less than the value of TX FIFO level.
*   - LCD_G77_1_I2C_INTR_TX_NOT_FULL - Transmitter FIFO is not full.
*   - LCD_G77_1_I2C_INTR_TX_EMPTY - Transmitter FIFO is empty.
*   - LCD_G77_1_I2C_INTR_TX_OVERFLOW - Attempt to write to a full 
*     transmitter FIFO.
*   - LCD_G77_1_I2C_INTR_TX_UNDERFLOW - Attempt to read from an empty 
*     transmitter FIFO.
*   - LCD_G77_1_I2C_INTR_TX_UART_NACK - UART received a NACK in SmartCard 
*   mode.
*   - LCD_G77_1_I2C_INTR_TX_UART_DONE - UART transfer is complete. 
*     All data elements from the TX FIFO are sent.
*   - LCD_G77_1_I2C_INTR_TX_UART_ARB_LOST - Value on the TX line of the UART
*     does not match the value on the RX line.
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetTxInterruptSource() (LCD_G77_1_I2C_INTR_TX_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetTxInterruptMode
****************************************************************************//**
*
*  Writes TX interrupt mask register. This register configures which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: TX interrupt sources to be enabled (refer to 
*   LCD_G77_1_I2C_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetTxInterruptMode(interruptMask)  LCD_G77_1_I2C_WRITE_INTR_TX_MASK(interruptMask)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetTxInterruptMode
****************************************************************************//**
*
*  Returns TX interrupt mask register This register specifies which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled TX interrupt sources (refer to 
*   LCD_G77_1_I2C_GetTxInterruptSource() function for bit field values).
*   
*******************************************************************************/
#define LCD_G77_1_I2C_GetTxInterruptMode()   (LCD_G77_1_I2C_INTR_TX_MASK_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetTxInterruptSourceMasked
****************************************************************************//**
*
*  Returns TX interrupt masked request register. This register contains logical
*  AND of corresponding bits from TX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to identify 
*  which of enabled TX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled TX interrupt sources (refer to 
*   LCD_G77_1_I2C_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetTxInterruptSourceMasked()   (LCD_G77_1_I2C_INTR_TX_MASKED_REG)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_ClearTxInterruptSource
****************************************************************************//**
*
*  Clears TX interrupt sources in the interrupt request register.
*
*  \param interruptMask: TX interrupt sources to be cleared (refer to 
*   LCD_G77_1_I2C_GetTxInterruptSource() function for bit field values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each affected interrupt 
*   source. Refer to section TX FIFO interrupt sources for detailed description.
*   - LCD_G77_1_I2C_INTR_TX_FIFO_LEVEL - Interrupt source is not cleared when 
*     transmitter FIFO has less entries than level.
*   - LCD_G77_1_I2C_INTR_TX_NOT_FULL - Interrupt source is not cleared when
*     transmitter FIFO has empty entries.
*   - LCD_G77_1_I2C_INTR_TX_EMPTY - Interrupt source is not cleared when 
*     transmitter FIFO is empty.
*   - LCD_G77_1_I2C_INTR_TX_UNDERFLOW - Interrupt source is not cleared when 
*     transmitter FIFO is empty and I2C mode with clock stretching is selected. 
*     Put data into the transmitter FIFO before clearing it. This behavior only 
*     applicable for PSoC 4100/PSoC 4200 devices.
*
*******************************************************************************/
#define LCD_G77_1_I2C_ClearTxInterruptSource(interruptMask)  LCD_G77_1_I2C_CLEAR_INTR_TX(interruptMask)


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetTxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to LCD_G77_1_I2C_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetTxInterrupt(interruptMask)  LCD_G77_1_I2C_SET_INTR_TX(interruptMask)

void LCD_G77_1_I2C_SetTxFifoLevel(uint32 level);


/* APIs to service INTR_MASTER register */
/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetMasterInterruptSource
****************************************************************************//**
*
*  Returns Master interrupt request register. This register contains current 
*  status of Master interrupt sources.
*
*  \return 
*   Current status of Master interrupt sources. 
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCD_G77_1_I2C_INTR_MASTER_SPI_DONE - SPI master transfer is complete.
*     Refer to Interrupt sources section for detailed description.
*   - LCD_G77_1_I2C_INTR_MASTER_I2C_ARB_LOST - I2C master lost arbitration.
*   - LCD_G77_1_I2C_INTR_MASTER_I2C_NACK - I2C master received negative 
*    acknowledgement (NAK).
*   - LCD_G77_1_I2C_INTR_MASTER_I2C_ACK - I2C master received acknowledgement.
*   - LCD_G77_1_I2C_INTR_MASTER_I2C_STOP - I2C master generated STOP.
*   - LCD_G77_1_I2C_INTR_MASTER_I2C_BUS_ERROR - I2C master bus error 
*     (detection of unexpected START or STOP condition).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetMasterInterruptSource() (LCD_G77_1_I2C_INTR_MASTER_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetMasterInterruptMode
****************************************************************************//**
*
*  Writes Master interrupt mask register. This register configures which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: Master interrupt sources to be enabled (refer to 
*   LCD_G77_1_I2C_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetMasterInterruptMode(interruptMask)  LCD_G77_1_I2C_WRITE_INTR_MASTER_MASK(interruptMask)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetMasterInterruptMode
****************************************************************************//**
*
*  Returns Master interrupt mask register This register specifies which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled Master interrupt sources (refer to 
*   LCD_G77_1_I2C_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetMasterInterruptMode()   (LCD_G77_1_I2C_INTR_MASTER_MASK_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetMasterInterruptSourceMasked
****************************************************************************//**
*
*  Returns Master interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Master interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Master interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Master interrupt sources (refer to 
*   LCD_G77_1_I2C_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetMasterInterruptSourceMasked()   (LCD_G77_1_I2C_INTR_MASTER_MASKED_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_ClearMasterInterruptSource
****************************************************************************//**
*
*  Clears Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to be cleared (refer to 
*   LCD_G77_1_I2C_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_ClearMasterInterruptSource(interruptMask)  LCD_G77_1_I2C_CLEAR_INTR_MASTER(interruptMask)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetMasterInterrupt
****************************************************************************//**
*
*  Sets Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to set in the Master interrupt
*   request register (refer to LCD_G77_1_I2C_GetMasterInterruptSource() 
*   function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetMasterInterrupt(interruptMask)  LCD_G77_1_I2C_SET_INTR_MASTER(interruptMask)


/* APIs to service INTR_SLAVE register */
/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetSlaveInterruptSource
****************************************************************************//**
*
*  Returns Slave interrupt request register. This register contains current 
*  status of Slave interrupt sources.
*
*  \return 
*   Current status of Slave interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_ARB_LOST - I2C slave lost arbitration: 
*     the value driven on the SDA line is not the same as the value observed 
*     on the SDA line.
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_NACK - I2C slave received negative 
*     acknowledgement (NAK).
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_ACK - I2C slave received 
*     acknowledgement (ACK).
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_WRITE_STOP - Stop or Repeated Start 
*     event for write transfer intended for this slave (address matching 
*     is performed).
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_STOP - Stop or Repeated Start event 
*     for (read or write) transfer intended for this slave (address matching 
*     is performed).
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_START - I2C slave received Start 
*     condition.
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_ADDR_MATCH - I2C slave received matching 
*     address.
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL - I2C Slave received general 
*     call address.
*   - LCD_G77_1_I2C_INTR_SLAVE_I2C_BUS_ERROR - I2C slave bus error (detection 
*      of unexpected Start or Stop condition).
*   - LCD_G77_1_I2C_INTR_SLAVE_SPI_BUS_ERROR - SPI slave select line is 
*      deselected at an expected time while the SPI transfer.
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetSlaveInterruptSource()  (LCD_G77_1_I2C_INTR_SLAVE_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetSlaveInterruptMode
****************************************************************************//**
*
*  Writes Slave interrupt mask register. 
*  This register configures which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \param interruptMask: Slave interrupt sources to be enabled (refer to 
*   LCD_G77_1_I2C_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetSlaveInterruptMode(interruptMask)   LCD_G77_1_I2C_WRITE_INTR_SLAVE_MASK(interruptMask)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetSlaveInterruptMode
****************************************************************************//**
*
*  Returns Slave interrupt mask register.
*  This register specifies which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \return 
*   Enabled Slave interrupt sources(refer to 
*   LCD_G77_1_I2C_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetSlaveInterruptMode()    (LCD_G77_1_I2C_INTR_SLAVE_MASK_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_GetSlaveInterruptSourceMasked
****************************************************************************//**
*
*  Returns Slave interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Slave interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Slave interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Slave interrupt sources (refer to 
*   LCD_G77_1_I2C_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_GetSlaveInterruptSourceMasked()    (LCD_G77_1_I2C_INTR_SLAVE_MASKED_REG)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_ClearSlaveInterruptSource
****************************************************************************//**
*
*  Clears Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to be cleared (refer to 
*   LCD_G77_1_I2C_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_ClearSlaveInterruptSource(interruptMask)   LCD_G77_1_I2C_CLEAR_INTR_SLAVE(interruptMask)

/*******************************************************************************
* Function Name: LCD_G77_1_I2C_SetSlaveInterrupt
****************************************************************************//**
*
*  Sets Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to set in the Slave interrupt 
*   request register (refer to LCD_G77_1_I2C_GetSlaveInterruptSource() 
*   function for return values).
*
*******************************************************************************/
#define LCD_G77_1_I2C_SetSlaveInterrupt(interruptMask)   LCD_G77_1_I2C_SET_INTR_SLAVE(interruptMask)

/** @} interrupt */ 


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/

/** LCD_G77_1_I2C_initVar indicates whether the LCD_G77_1_I2C 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the LCD_G77_1_I2C_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  LCD_G77_1_I2C_Init() function can be called before the 
*  LCD_G77_1_I2C_Start() or LCD_G77_1_I2C_Enable() function.
*/
extern uint8 LCD_G77_1_I2C_initVar;
/** @} globals */

/***************************************
*              Registers
***************************************/

#define LCD_G77_1_I2C_CTRL_REG               (*(reg32 *) LCD_G77_1_I2C_SCB__CTRL)
#define LCD_G77_1_I2C_CTRL_PTR               ( (reg32 *) LCD_G77_1_I2C_SCB__CTRL)

#define LCD_G77_1_I2C_STATUS_REG             (*(reg32 *) LCD_G77_1_I2C_SCB__STATUS)
#define LCD_G77_1_I2C_STATUS_PTR             ( (reg32 *) LCD_G77_1_I2C_SCB__STATUS)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_SPI_CTRL_REG           (*(reg32 *) LCD_G77_1_I2C_SCB__SPI_CTRL)
    #define LCD_G77_1_I2C_SPI_CTRL_PTR           ( (reg32 *) LCD_G77_1_I2C_SCB__SPI_CTRL)

    #define LCD_G77_1_I2C_SPI_STATUS_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__SPI_STATUS)
    #define LCD_G77_1_I2C_SPI_STATUS_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__SPI_STATUS)

    #define LCD_G77_1_I2C_UART_CTRL_REG          (*(reg32 *) LCD_G77_1_I2C_SCB__UART_CTRL)
    #define LCD_G77_1_I2C_UART_CTRL_PTR          ( (reg32 *) LCD_G77_1_I2C_SCB__UART_CTRL)

    #define LCD_G77_1_I2C_UART_TX_CTRL_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__UART_TX_CTRL)
    #define LCD_G77_1_I2C_UART_TX_CTRL_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__UART_TX_CTRL)

    #define LCD_G77_1_I2C_UART_RX_CTRL_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__UART_RX_CTRL)
    #define LCD_G77_1_I2C_UART_RX_CTRL_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__UART_RX_CTRL)

    #define LCD_G77_1_I2C_UART_RX_STATUS_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__UART_RX_STATUS)
    #define LCD_G77_1_I2C_UART_RX_STATUS_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__UART_RX_STATUS)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__UART_FLOW_CTRL)
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__UART_FLOW_CTRL)
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_I2C_CTRL_REG           (*(reg32 *) LCD_G77_1_I2C_SCB__I2C_CTRL)
#define LCD_G77_1_I2C_I2C_CTRL_PTR           ( (reg32 *) LCD_G77_1_I2C_SCB__I2C_CTRL)

#define LCD_G77_1_I2C_I2C_STATUS_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__I2C_STATUS)
#define LCD_G77_1_I2C_I2C_STATUS_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__I2C_STATUS)

#define LCD_G77_1_I2C_I2C_MASTER_CMD_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__I2C_M_CMD)
#define LCD_G77_1_I2C_I2C_MASTER_CMD_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__I2C_M_CMD)

#define LCD_G77_1_I2C_I2C_SLAVE_CMD_REG      (*(reg32 *) LCD_G77_1_I2C_SCB__I2C_S_CMD)
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_PTR      ( (reg32 *) LCD_G77_1_I2C_SCB__I2C_S_CMD)

#define LCD_G77_1_I2C_I2C_CFG_REG            (*(reg32 *) LCD_G77_1_I2C_SCB__I2C_CFG)
#define LCD_G77_1_I2C_I2C_CFG_PTR            ( (reg32 *) LCD_G77_1_I2C_SCB__I2C_CFG)

#define LCD_G77_1_I2C_TX_CTRL_REG            (*(reg32 *) LCD_G77_1_I2C_SCB__TX_CTRL)
#define LCD_G77_1_I2C_TX_CTRL_PTR            ( (reg32 *) LCD_G77_1_I2C_SCB__TX_CTRL)

#define LCD_G77_1_I2C_TX_FIFO_CTRL_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_CTRL)
#define LCD_G77_1_I2C_TX_FIFO_CTRL_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_CTRL)

#define LCD_G77_1_I2C_TX_FIFO_STATUS_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_STATUS)
#define LCD_G77_1_I2C_TX_FIFO_STATUS_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_STATUS)

#define LCD_G77_1_I2C_TX_FIFO_WR_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_WR)
#define LCD_G77_1_I2C_TX_FIFO_WR_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__TX_FIFO_WR)

#define LCD_G77_1_I2C_RX_CTRL_REG            (*(reg32 *) LCD_G77_1_I2C_SCB__RX_CTRL)
#define LCD_G77_1_I2C_RX_CTRL_PTR            ( (reg32 *) LCD_G77_1_I2C_SCB__RX_CTRL)

#define LCD_G77_1_I2C_RX_FIFO_CTRL_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_CTRL)
#define LCD_G77_1_I2C_RX_FIFO_CTRL_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_CTRL)

#define LCD_G77_1_I2C_RX_FIFO_STATUS_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_STATUS)
#define LCD_G77_1_I2C_RX_FIFO_STATUS_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_STATUS)

#define LCD_G77_1_I2C_RX_MATCH_REG           (*(reg32 *) LCD_G77_1_I2C_SCB__RX_MATCH)
#define LCD_G77_1_I2C_RX_MATCH_PTR           ( (reg32 *) LCD_G77_1_I2C_SCB__RX_MATCH)

#define LCD_G77_1_I2C_RX_FIFO_RD_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_RD)
#define LCD_G77_1_I2C_RX_FIFO_RD_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_RD)

#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_REG  (*(reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_RD_SILENT)
#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) LCD_G77_1_I2C_SCB__RX_FIFO_RD_SILENT)

#ifdef LCD_G77_1_I2C_SCB__EZ_DATA0
    #define LCD_G77_1_I2C_EZBUF_DATA0_REG    (*(reg32 *) LCD_G77_1_I2C_SCB__EZ_DATA0)
    #define LCD_G77_1_I2C_EZBUF_DATA0_PTR    ( (reg32 *) LCD_G77_1_I2C_SCB__EZ_DATA0)
#else
    #define LCD_G77_1_I2C_EZBUF_DATA0_REG    (*(reg32 *) LCD_G77_1_I2C_SCB__EZ_DATA00)
    #define LCD_G77_1_I2C_EZBUF_DATA0_PTR    ( (reg32 *) LCD_G77_1_I2C_SCB__EZ_DATA00)
#endif /* LCD_G77_1_I2C_SCB__EZ_DATA00 */

#define LCD_G77_1_I2C_INTR_CAUSE_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_CAUSE)
#define LCD_G77_1_I2C_INTR_CAUSE_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_CAUSE)

#define LCD_G77_1_I2C_INTR_I2C_EC_REG        (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC)
#define LCD_G77_1_I2C_INTR_I2C_EC_PTR        ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC)

#define LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG   (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC_MASK)
#define LCD_G77_1_I2C_INTR_I2C_EC_MASK_PTR   ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC_MASK)

#define LCD_G77_1_I2C_INTR_I2C_EC_MASKED_REG (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC_MASKED)
#define LCD_G77_1_I2C_INTR_I2C_EC_MASKED_PTR ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_I2C_EC_MASKED)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_INTR_SPI_EC_REG        (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC)
    #define LCD_G77_1_I2C_INTR_SPI_EC_PTR        ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC)

    #define LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG   (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC_MASK)
    #define LCD_G77_1_I2C_INTR_SPI_EC_MASK_PTR   ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC_MASK)

    #define LCD_G77_1_I2C_INTR_SPI_EC_MASKED_REG (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC_MASKED)
    #define LCD_G77_1_I2C_INTR_SPI_EC_MASKED_PTR ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_SPI_EC_MASKED)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_INTR_MASTER_REG        (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_M)
#define LCD_G77_1_I2C_INTR_MASTER_PTR        ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_M)

#define LCD_G77_1_I2C_INTR_MASTER_SET_REG    (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_M_SET)
#define LCD_G77_1_I2C_INTR_MASTER_SET_PTR    ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_M_SET)

#define LCD_G77_1_I2C_INTR_MASTER_MASK_REG   (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_M_MASK)
#define LCD_G77_1_I2C_INTR_MASTER_MASK_PTR   ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_M_MASK)

#define LCD_G77_1_I2C_INTR_MASTER_MASKED_REG (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_M_MASKED)
#define LCD_G77_1_I2C_INTR_MASTER_MASKED_PTR ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_M_MASKED)

#define LCD_G77_1_I2C_INTR_SLAVE_REG         (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_S)
#define LCD_G77_1_I2C_INTR_SLAVE_PTR         ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_S)

#define LCD_G77_1_I2C_INTR_SLAVE_SET_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_S_SET)
#define LCD_G77_1_I2C_INTR_SLAVE_SET_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_S_SET)

#define LCD_G77_1_I2C_INTR_SLAVE_MASK_REG    (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_S_MASK)
#define LCD_G77_1_I2C_INTR_SLAVE_MASK_PTR    ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_S_MASK)

#define LCD_G77_1_I2C_INTR_SLAVE_MASKED_REG  (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_S_MASKED)
#define LCD_G77_1_I2C_INTR_SLAVE_MASKED_PTR  ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_S_MASKED)

#define LCD_G77_1_I2C_INTR_TX_REG            (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_TX)
#define LCD_G77_1_I2C_INTR_TX_PTR            ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_TX)

#define LCD_G77_1_I2C_INTR_TX_SET_REG        (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_SET)
#define LCD_G77_1_I2C_INTR_TX_SET_PTR        ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_SET)

#define LCD_G77_1_I2C_INTR_TX_MASK_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_MASK)
#define LCD_G77_1_I2C_INTR_TX_MASK_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_MASK)

#define LCD_G77_1_I2C_INTR_TX_MASKED_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_MASKED)
#define LCD_G77_1_I2C_INTR_TX_MASKED_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_TX_MASKED)

#define LCD_G77_1_I2C_INTR_RX_REG            (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_RX)
#define LCD_G77_1_I2C_INTR_RX_PTR            ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_RX)

#define LCD_G77_1_I2C_INTR_RX_SET_REG        (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_SET)
#define LCD_G77_1_I2C_INTR_RX_SET_PTR        ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_SET)

#define LCD_G77_1_I2C_INTR_RX_MASK_REG       (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_MASK)
#define LCD_G77_1_I2C_INTR_RX_MASK_PTR       ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_MASK)

#define LCD_G77_1_I2C_INTR_RX_MASKED_REG     (*(reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_MASKED)
#define LCD_G77_1_I2C_INTR_RX_MASKED_PTR     ( (reg32 *) LCD_G77_1_I2C_SCB__INTR_RX_MASKED)

/* Defines get from SCB IP parameters. */
#define LCD_G77_1_I2C_FIFO_SIZE      (8u)  /* TX or RX FIFO size. */
#define LCD_G77_1_I2C_EZ_DATA_NR     (32u)  /* Number of words in EZ memory. */ 
#define LCD_G77_1_I2C_ONE_BYTE_WIDTH (8u)            /* Number of bits in one byte. */
#define LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK       (0x07u)      /* Number of bits to represent a FIFO address. */
#define LCD_G77_1_I2C_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* Number of bits to represent #bytes in FIFO. */


/***************************************
*        Registers Constants
***************************************/

#if (LCD_G77_1_I2C_SCB_IRQ_INTERNAL)
    #define LCD_G77_1_I2C_ISR_NUMBER     ((uint8) LCD_G77_1_I2C_SCB_IRQ__INTC_NUMBER)
    #define LCD_G77_1_I2C_ISR_PRIORITY   ((uint8) LCD_G77_1_I2C_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (LCD_G77_1_I2C_SCB_IRQ_INTERNAL) */

#if (LCD_G77_1_I2C_UART_RX_WAKEUP_IRQ)
    #define LCD_G77_1_I2C_RX_WAKE_ISR_NUMBER     ((uint8) LCD_G77_1_I2C_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define LCD_G77_1_I2C_RX_WAKE_ISR_PRIORITY   ((uint8) LCD_G77_1_I2C_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (LCD_G77_1_I2C_UART_RX_WAKEUP_IRQ) */

/* LCD_G77_1_I2C_CTRL_REG */
#define LCD_G77_1_I2C_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define LCD_G77_1_I2C_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define LCD_G77_1_I2C_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define LCD_G77_1_I2C_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */
#define LCD_G77_1_I2C_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define LCD_G77_1_I2C_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define LCD_G77_1_I2C_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define LCD_G77_1_I2C_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define LCD_G77_1_I2C_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define LCD_G77_1_I2C_CTRL_EC_AM_MODE        ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_EC_AM_MODE_POS)
#define LCD_G77_1_I2C_CTRL_EC_OP_MODE        ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_EC_OP_MODE_POS)
#define LCD_G77_1_I2C_CTRL_EZBUF_MODE        ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_EZBUF_MODE_POS)
#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CTRL_BYTE_MODE ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_BYTE_MODE_POS)
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */
#define LCD_G77_1_I2C_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_ADDR_ACCEPT_POS)
#define LCD_G77_1_I2C_CTRL_BLOCK             ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_BLOCK_POS)
#define LCD_G77_1_I2C_CTRL_MODE_MASK         ((uint32) 0x03u << LCD_G77_1_I2C_CTRL_MODE_POS)
#define LCD_G77_1_I2C_CTRL_MODE_I2C          ((uint32) 0x00u)
#define LCD_G77_1_I2C_CTRL_MODE_SPI          ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_MODE_POS)
#define LCD_G77_1_I2C_CTRL_MODE_UART         ((uint32) 0x02u << LCD_G77_1_I2C_CTRL_MODE_POS)
#define LCD_G77_1_I2C_CTRL_ENABLED           ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_ENABLED_POS)

/* LCD_G77_1_I2C_STATUS_REG */
#define LCD_G77_1_I2C_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define LCD_G77_1_I2C_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* LCD_G77_1_I2C_SPI_CTRL_REG  */
#define LCD_G77_1_I2C_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define LCD_G77_1_I2C_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define LCD_G77_1_I2C_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define LCD_G77_1_I2C_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define LCD_G77_1_I2C_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */
#define LCD_G77_1_I2C_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define LCD_G77_1_I2C_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define LCD_G77_1_I2C_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define LCD_G77_1_I2C_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define LCD_G77_1_I2C_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SELECT_PRECEDE_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << LCD_G77_1_I2C_SPI_CTRL_CPHA_POS)
#define LCD_G77_1_I2C_SPI_CTRL_CPHA                  ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_CPHA_POS)
#define LCD_G77_1_I2C_SPI_CTRL_CPOL                  ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_CPOL_POS)
#define LCD_G77_1_I2C_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY_POS)
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SSEL1_POLARITY_POS)
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SSEL2_POLARITY_POS)
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SSEL3_POLARITY_POS)
    #define LCD_G77_1_I2C_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_LOOPBACK_POS)
#define LCD_G77_1_I2C_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << LCD_G77_1_I2C_SPI_CTRL_MODE_POS)
#define LCD_G77_1_I2C_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define LCD_G77_1_I2C_SPI_CTRL_MODE_TI               ((uint32) 0x01u << LCD_G77_1_I2C_CTRL_MODE_POS)
#define LCD_G77_1_I2C_SPI_CTRL_MODE_NS               ((uint32) 0x02u << LCD_G77_1_I2C_CTRL_MODE_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS)
#define LCD_G77_1_I2C_SPI_CTRL_MASTER                ((uint32) 0x01u << LCD_G77_1_I2C_SPI_CTRL_MASTER_MODE_POS)
#define LCD_G77_1_I2C_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* LCD_G77_1_I2C_SPI_STATUS_REG  */
#define LCD_G77_1_I2C_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define LCD_G77_1_I2C_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define LCD_G77_1_I2C_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LCD_G77_1_I2C_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LCD_G77_1_I2C_I2C_STATUS_EZBUF_ADDR_POS)

/* LCD_G77_1_I2C_UART_CTRL */
#define LCD_G77_1_I2C_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define LCD_G77_1_I2C_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define LCD_G77_1_I2C_UART_CTRL_LOOPBACK             ((uint32) 0x01u << LCD_G77_1_I2C_UART_CTRL_LOOPBACK_POS)
#define LCD_G77_1_I2C_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define LCD_G77_1_I2C_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << LCD_G77_1_I2C_UART_CTRL_MODE_POS)
#define LCD_G77_1_I2C_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << LCD_G77_1_I2C_UART_CTRL_MODE_POS)
#define LCD_G77_1_I2C_UART_CTRL_MODE_MASK            ((uint32) 0x03u << LCD_G77_1_I2C_UART_CTRL_MODE_POS)

/* LCD_G77_1_I2C_UART_TX_CTRL */
#define LCD_G77_1_I2C_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define LCD_G77_1_I2C_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define LCD_G77_1_I2C_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define LCD_G77_1_I2C_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define LCD_G77_1_I2C_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define LCD_G77_1_I2C_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define LCD_G77_1_I2C_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define LCD_G77_1_I2C_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define LCD_G77_1_I2C_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_TX_CTRL_PARITY_POS)
#define LCD_G77_1_I2C_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_TX_CTRL_PARITY_ENABLED_POS)
#define LCD_G77_1_I2C_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* LCD_G77_1_I2C_UART_RX_CTRL */
#define LCD_G77_1_I2C_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define LCD_G77_1_I2C_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define LCD_G77_1_I2C_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define LCD_G77_1_I2C_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define LCD_G77_1_I2C_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define LCD_G77_1_I2C_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define LCD_G77_1_I2C_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define LCD_G77_1_I2C_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define LCD_G77_1_I2C_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define LCD_G77_1_I2C_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define LCD_G77_1_I2C_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define LCD_G77_1_I2C_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define LCD_G77_1_I2C_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_PARITY_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_PARITY_ENABLED_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_POLARITY_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_MP_MODE_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_LIN_MODE_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_SKIP_START_POS)
#define LCD_G77_1_I2C_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_BREAK_WIDTH_POS)
/* LCD_G77_1_I2C_UART_RX_STATUS_REG */
#define LCD_G77_1_I2C_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define LCD_G77_1_I2C_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    /* LCD_G77_1_I2C_UART_FLOW_CTRL_REG */
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK)
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       LCD_G77_1_I2C_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

/* LCD_G77_1_I2C_I2C_CTRL */
#define LCD_G77_1_I2C_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define LCD_G77_1_I2C_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define LCD_G77_1_I2C_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define LCD_G77_1_I2C_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define LCD_G77_1_I2C_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define LCD_G77_1_I2C_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define LCD_G77_1_I2C_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define LCD_G77_1_I2C_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define LCD_G77_1_I2C_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                LCD_G77_1_I2C_I2C_CTRL_LOW_PHASE_OVS_POS)
#define LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define LCD_G77_1_I2C_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_LOOPBACK_POS)
#define LCD_G77_1_I2C_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_SLAVE_MODE_POS)
#define LCD_G77_1_I2C_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_MASTER_MODE_POS)
#define LCD_G77_1_I2C_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CTRL_SLAVE_MODE_POS)

/* LCD_G77_1_I2C_I2C_STATUS_REG  */
#define LCD_G77_1_I2C_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define LCD_G77_1_I2C_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define LCD_G77_1_I2C_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define LCD_G77_1_I2C_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define LCD_G77_1_I2C_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LCD_G77_1_I2C_I2C_STATUS_S_READ          ((uint32) 0x01u << LCD_G77_1_I2C_I2C_STATUS_S_READ_POS)
#define LCD_G77_1_I2C_I2C_STATUS_M_READ          ((uint32) 0x01u << LCD_G77_1_I2C_I2C_STATUS_M_READ_POS)
#define LCD_G77_1_I2C_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LCD_G77_1_I2C_I2C_STATUS_EZBUF_ADDR_POS)

/* LCD_G77_1_I2C_I2C_MASTER_CMD_REG */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   LCD_G77_1_I2C_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   LCD_G77_1_I2C_I2C_MASTER_CMD_M_ACK_POS)
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_I2C_MASTER_CMD_M_NACK_POS)
#define LCD_G77_1_I2C_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_I2C_MASTER_CMD_M_STOP_POS)

/* LCD_G77_1_I2C_I2C_SLAVE_CMD_REG  */
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK_POS)

#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK_POS)

/* LCD_G77_1_I2C_I2C_CFG_REG */
#if (LCD_G77_1_I2C_CY_SCBIP_V0)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HYS_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SCL_FILT_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_HS_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_ENABLED_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SCL_FILT_HS_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SCL_FILT_ENABLED_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */


/* LCD_G77_1_I2C_TX_CTRL_REG */
#define LCD_G77_1_I2C_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LCD_G77_1_I2C_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LCD_G77_1_I2C_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define LCD_G77_1_I2C_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LCD_G77_1_I2C_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << LCD_G77_1_I2C_TX_CTRL_MSB_FIRST_POS)
#define LCD_G77_1_I2C_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LCD_G77_1_I2C_TX_CTRL_ENABLED            ((uint32) 0x01u << LCD_G77_1_I2C_TX_CTRL_ENABLED_POS)

/* LCD_G77_1_I2C_TX_CTRL_FIFO_REG */
#define LCD_G77_1_I2C_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define LCD_G77_1_I2C_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define LCD_G77_1_I2C_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define LCD_G77_1_I2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK)
#define LCD_G77_1_I2C_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LCD_G77_1_I2C_TX_FIFO_CTRL_CLEAR_POS)
#define LCD_G77_1_I2C_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LCD_G77_1_I2C_TX_FIFO_CTRL_FREEZE_POS)

/* LCD_G77_1_I2C_TX_FIFO_STATUS_REG */
#define LCD_G77_1_I2C_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define LCD_G77_1_I2C_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define LCD_G77_1_I2C_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define LCD_G77_1_I2C_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define LCD_G77_1_I2C_TX_FIFO_STATUS_USED_MASK   ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LCD_G77_1_I2C_TX_FIFO_SR_VALID           ((uint32) 0x01u << LCD_G77_1_I2C_TX_FIFO_SR_VALID_POS)
#define LCD_G77_1_I2C_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK << \
                                                                    LCD_G77_1_I2C_TX_FIFO_STATUS_RD_PTR_POS)
#define LCD_G77_1_I2C_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK << \
                                                                    LCD_G77_1_I2C_TX_FIFO_STATUS_WR_PTR_POS)

/* LCD_G77_1_I2C_TX_FIFO_WR_REG */
#define LCD_G77_1_I2C_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define LCD_G77_1_I2C_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* LCD_G77_1_I2C_RX_CTRL_REG */
#define LCD_G77_1_I2C_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LCD_G77_1_I2C_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LCD_G77_1_I2C_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define LCD_G77_1_I2C_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define LCD_G77_1_I2C_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LCD_G77_1_I2C_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << LCD_G77_1_I2C_RX_CTRL_MSB_FIRST_POS)
#define LCD_G77_1_I2C_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LCD_G77_1_I2C_RX_CTRL_MEDIAN             ((uint32) 0x01u << LCD_G77_1_I2C_RX_CTRL_MEDIAN_POS)
#define LCD_G77_1_I2C_RX_CTRL_ENABLED            ((uint32) 0x01u << LCD_G77_1_I2C_RX_CTRL_ENABLED_POS)


/* LCD_G77_1_I2C_RX_FIFO_CTRL_REG */
#define LCD_G77_1_I2C_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define LCD_G77_1_I2C_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define LCD_G77_1_I2C_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define LCD_G77_1_I2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK)
#define LCD_G77_1_I2C_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LCD_G77_1_I2C_RX_FIFO_CTRL_CLEAR_POS)
#define LCD_G77_1_I2C_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LCD_G77_1_I2C_RX_FIFO_CTRL_FREEZE_POS)

/* LCD_G77_1_I2C_RX_FIFO_STATUS_REG */
#define LCD_G77_1_I2C_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define LCD_G77_1_I2C_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define LCD_G77_1_I2C_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define LCD_G77_1_I2C_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define LCD_G77_1_I2C_RX_FIFO_STATUS_USED_MASK   ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LCD_G77_1_I2C_RX_FIFO_SR_VALID           ((uint32) 0x01u << LCD_G77_1_I2C_RX_FIFO_SR_VALID_POS)
#define LCD_G77_1_I2C_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK << \
                                                                    LCD_G77_1_I2C_RX_FIFO_STATUS_RD_PTR_POS)
#define LCD_G77_1_I2C_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) LCD_G77_1_I2C_FF_DATA_NR_LOG2_MASK << \
                                                                    LCD_G77_1_I2C_RX_FIFO_STATUS_WR_PTR_POS)

/* LCD_G77_1_I2C_RX_MATCH_REG */
#define LCD_G77_1_I2C_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define LCD_G77_1_I2C_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define LCD_G77_1_I2C_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define LCD_G77_1_I2C_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << LCD_G77_1_I2C_RX_MATCH_MASK_POS)

/* LCD_G77_1_I2C_RX_FIFO_WR_REG */
#define LCD_G77_1_I2C_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define LCD_G77_1_I2C_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* LCD_G77_1_I2C_RX_FIFO_RD_SILENT_REG */
#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LCD_G77_1_I2C_RX_FIFO_RD_SILENT_REG */
#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LCD_G77_1_I2C_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LCD_G77_1_I2C_EZBUF_DATA_REG */
#define LCD_G77_1_I2C_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define LCD_G77_1_I2C_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  LCD_G77_1_I2C_INTR_CAUSE_REG */
#define LCD_G77_1_I2C_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define LCD_G77_1_I2C_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define LCD_G77_1_I2C_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define LCD_G77_1_I2C_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define LCD_G77_1_I2C_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define LCD_G77_1_I2C_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define LCD_G77_1_I2C_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_CAUSE_SLAVE       ((uint32) 0x01u << LCD_G77_1_I2C_INTR_CAUSE_SLAVE_POS)
#define LCD_G77_1_I2C_INTR_CAUSE_TX          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_CAUSE_TX_POS)
#define LCD_G77_1_I2C_INTR_CAUSE_RX          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_CAUSE_RX_POS)
#define LCD_G77_1_I2C_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << LCD_G77_1_I2C_INTR_CAUSE_I2C_EC_POS)
#define LCD_G77_1_I2C_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << LCD_G77_1_I2C_INTR_CAUSE_SPI_EC_POS)

/* LCD_G77_1_I2C_INTR_SPI_EC_REG, LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG, LCD_G77_1_I2C_INTR_SPI_EC_MASKED_REG */
#define LCD_G77_1_I2C_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LCD_G77_1_I2C_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_STOP_POS)
#define LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* LCD_G77_1_I2C_INTR_I2C_EC, LCD_G77_1_I2C_INTR_I2C_EC_MASK, LCD_G77_1_I2C_INTR_I2C_EC_MASKED */
#define LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_STOP_POS)
#define LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* LCD_G77_1_I2C_INTR_MASTER, LCD_G77_1_I2C_INTR_MASTER_SET,
   LCD_G77_1_I2C_INTR_MASTER_MASK, LCD_G77_1_I2C_INTR_MASTER_MASKED */
#define LCD_G77_1_I2C_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define LCD_G77_1_I2C_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define LCD_G77_1_I2C_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define LCD_G77_1_I2C_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define LCD_G77_1_I2C_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define LCD_G77_1_I2C_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define LCD_G77_1_I2C_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_MASTER_I2C_NACK_POS)
#define LCD_G77_1_I2C_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << LCD_G77_1_I2C_INTR_MASTER_I2C_ACK_POS)
#define LCD_G77_1_I2C_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_MASTER_I2C_STOP_POS)
#define LCD_G77_1_I2C_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_MASTER_I2C_BUS_ERROR_POS)
#define LCD_G77_1_I2C_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_MASTER_SPI_DONE_POS)

/*
* LCD_G77_1_I2C_INTR_SLAVE, LCD_G77_1_I2C_INTR_SLAVE_SET,
* LCD_G77_1_I2C_INTR_SLAVE_MASK, LCD_G77_1_I2C_INTR_SLAVE_MASKED
*/
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_NACK_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_ACK_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_STOP_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_START_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define LCD_G77_1_I2C_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    LCD_G77_1_I2C_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* LCD_G77_1_I2C_INTR_TX, LCD_G77_1_I2C_INTR_TX_SET,
* LCD_G77_1_I2C_INTR_TX_MASK, LCD_G77_1_I2C_INTR_TX_MASKED
*/
#define LCD_G77_1_I2C_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define LCD_G77_1_I2C_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define LCD_G77_1_I2C_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define LCD_G77_1_I2C_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define LCD_G77_1_I2C_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define LCD_G77_1_I2C_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define LCD_G77_1_I2C_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define LCD_G77_1_I2C_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define LCD_G77_1_I2C_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define LCD_G77_1_I2C_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_TX_FIFO_LEVEL         (LCD_G77_1_I2C_INTR_TX_TRIGGER)
#define LCD_G77_1_I2C_INTR_TX_NOT_FULL           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_NOT_FULL_POS)
#define LCD_G77_1_I2C_INTR_TX_EMPTY              ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_EMPTY_POS)
#define LCD_G77_1_I2C_INTR_TX_OVERFLOW           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_OVERFLOW_POS)
#define LCD_G77_1_I2C_INTR_TX_UNDERFLOW          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_UNDERFLOW_POS)
#define LCD_G77_1_I2C_INTR_TX_BLOCKED            ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_BLOCKED_POS)
#define LCD_G77_1_I2C_INTR_TX_UART_NACK          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_UART_NACK_POS)
#define LCD_G77_1_I2C_INTR_TX_UART_DONE          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_UART_DONE_POS)
#define LCD_G77_1_I2C_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << LCD_G77_1_I2C_INTR_TX_UART_ARB_LOST_POS)

/*
* LCD_G77_1_I2C_INTR_RX, LCD_G77_1_I2C_INTR_RX_SET,
* LCD_G77_1_I2C_INTR_RX_MASK, LCD_G77_1_I2C_INTR_RX_MASKED
*/
#define LCD_G77_1_I2C_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define LCD_G77_1_I2C_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define LCD_G77_1_I2C_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define LCD_G77_1_I2C_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define LCD_G77_1_I2C_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define LCD_G77_1_I2C_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define LCD_G77_1_I2C_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define LCD_G77_1_I2C_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define LCD_G77_1_I2C_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define LCD_G77_1_I2C_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define LCD_G77_1_I2C_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define LCD_G77_1_I2C_INTR_RX_FIFO_LEVEL         (LCD_G77_1_I2C_INTR_RX_TRIGGER)
#define LCD_G77_1_I2C_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_NOT_EMPTY_POS)
#define LCD_G77_1_I2C_INTR_RX_FULL               ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_FULL_POS)
#define LCD_G77_1_I2C_INTR_RX_OVERFLOW           ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_OVERFLOW_POS)
#define LCD_G77_1_I2C_INTR_RX_UNDERFLOW          ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_UNDERFLOW_POS)
#define LCD_G77_1_I2C_INTR_RX_BLOCKED            ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_BLOCKED_POS)
#define LCD_G77_1_I2C_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_FRAME_ERROR_POS)
#define LCD_G77_1_I2C_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_PARITY_ERROR_POS)
#define LCD_G77_1_I2C_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_BAUD_DETECT_POS)
#define LCD_G77_1_I2C_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << LCD_G77_1_I2C_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define LCD_G77_1_I2C_INTR_I2C_EC_ALL    (LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP    | \
                                             LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_STOP | \
                                             LCD_G77_1_I2C_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define LCD_G77_1_I2C_INTR_SPI_EC_ALL    (LCD_G77_1_I2C_INTR_SPI_EC_WAKE_UP    | \
                                             LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_STOP | \
                                             LCD_G77_1_I2C_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define LCD_G77_1_I2C_INTR_MASTER_ALL    (LCD_G77_1_I2C_INTR_MASTER_I2C_ARB_LOST  | \
                                             LCD_G77_1_I2C_INTR_MASTER_I2C_NACK      | \
                                             LCD_G77_1_I2C_INTR_MASTER_I2C_ACK       | \
                                             LCD_G77_1_I2C_INTR_MASTER_I2C_STOP      | \
                                             LCD_G77_1_I2C_INTR_MASTER_I2C_BUS_ERROR | \
                                             LCD_G77_1_I2C_INTR_MASTER_SPI_DONE)

#define LCD_G77_1_I2C_INTR_SLAVE_ALL     (LCD_G77_1_I2C_INTR_SLAVE_I2C_ARB_LOST      | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_NACK          | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_ACK           | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_STOP          | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_START         | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL       | \
                                             LCD_G77_1_I2C_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             LCD_G77_1_I2C_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             LCD_G77_1_I2C_INTR_SLAVE_SPI_BUS_ERROR)

#define LCD_G77_1_I2C_INTR_TX_ALL        (LCD_G77_1_I2C_INTR_TX_TRIGGER   | \
                                             LCD_G77_1_I2C_INTR_TX_NOT_FULL  | \
                                             LCD_G77_1_I2C_INTR_TX_EMPTY     | \
                                             LCD_G77_1_I2C_INTR_TX_OVERFLOW  | \
                                             LCD_G77_1_I2C_INTR_TX_UNDERFLOW | \
                                             LCD_G77_1_I2C_INTR_TX_BLOCKED   | \
                                             LCD_G77_1_I2C_INTR_TX_UART_NACK | \
                                             LCD_G77_1_I2C_INTR_TX_UART_DONE | \
                                             LCD_G77_1_I2C_INTR_TX_UART_ARB_LOST)

#define LCD_G77_1_I2C_INTR_RX_ALL        (LCD_G77_1_I2C_INTR_RX_TRIGGER      | \
                                             LCD_G77_1_I2C_INTR_RX_NOT_EMPTY    | \
                                             LCD_G77_1_I2C_INTR_RX_FULL         | \
                                             LCD_G77_1_I2C_INTR_RX_OVERFLOW     | \
                                             LCD_G77_1_I2C_INTR_RX_UNDERFLOW    | \
                                             LCD_G77_1_I2C_INTR_RX_BLOCKED      | \
                                             LCD_G77_1_I2C_INTR_RX_FRAME_ERROR  | \
                                             LCD_G77_1_I2C_INTR_RX_PARITY_ERROR | \
                                             LCD_G77_1_I2C_INTR_RX_BAUD_DETECT  | \
                                             LCD_G77_1_I2C_INTR_RX_BREAK_DETECT)

/* I2C and EZI2C slave address defines */
#define LCD_G77_1_I2C_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define LCD_G77_1_I2C_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define LCD_G77_1_I2C_CTRL_OVS_IRDA_OVS16        (LCD_G77_1_I2C_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
* Clear I2C command registers are because they are not impacted by re-enable.
*/
#define LCD_G77_1_I2C_SCB_SW_RESET   LCD_G77_1_I2C_I2CFwBlockReset()

/* TX FIFO macro */
#define LCD_G77_1_I2C_CLEAR_TX_FIFO \
                            do{        \
                                LCD_G77_1_I2C_TX_FIFO_CTRL_REG |= ((uint32)  LCD_G77_1_I2C_TX_FIFO_CTRL_CLEAR); \
                                LCD_G77_1_I2C_TX_FIFO_CTRL_REG &= ((uint32) ~LCD_G77_1_I2C_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LCD_G77_1_I2C_GET_TX_FIFO_ENTRIES    (LCD_G77_1_I2C_TX_FIFO_STATUS_REG & \
                                                 LCD_G77_1_I2C_TX_FIFO_STATUS_USED_MASK)

#define LCD_G77_1_I2C_GET_TX_FIFO_SR_VALID   ((0u != (LCD_G77_1_I2C_TX_FIFO_STATUS_REG & \
                                                         LCD_G77_1_I2C_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define LCD_G77_1_I2C_CLEAR_RX_FIFO \
                            do{        \
                                LCD_G77_1_I2C_RX_FIFO_CTRL_REG |= ((uint32)  LCD_G77_1_I2C_RX_FIFO_CTRL_CLEAR); \
                                LCD_G77_1_I2C_RX_FIFO_CTRL_REG &= ((uint32) ~LCD_G77_1_I2C_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LCD_G77_1_I2C_GET_RX_FIFO_ENTRIES    (LCD_G77_1_I2C_RX_FIFO_STATUS_REG & \
                                                    LCD_G77_1_I2C_RX_FIFO_STATUS_USED_MASK)

#define LCD_G77_1_I2C_GET_RX_FIFO_SR_VALID   ((0u != (LCD_G77_1_I2C_RX_FIFO_STATUS_REG & \
                                                         LCD_G77_1_I2C_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in LCD_G77_1_I2C_INTR_X_MASK_REG */
#define LCD_G77_1_I2C_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    LCD_G77_1_I2C_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in LCD_G77_1_I2C_INTR_X_MASK_REG */
#define LCD_G77_1_I2C_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in LCD_G77_1_I2C_INTR_X_MASK_REG */
#define LCD_G77_1_I2C_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                LCD_G77_1_I2C_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LCD_G77_1_I2C_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    LCD_G77_1_I2C_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LCD_G77_1_I2C_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    LCD_G77_1_I2C_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define LCD_G77_1_I2C_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    LCD_G77_1_I2C_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in LCD_G77_1_I2C_INTR_X_SET_REG */
#define LCD_G77_1_I2C_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    LCD_G77_1_I2C_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    LCD_G77_1_I2C_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    LCD_G77_1_I2C_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in LCD_G77_1_I2C_INTR_X_REG */
#define LCD_G77_1_I2C_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define LCD_G77_1_I2C_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    LCD_G77_1_I2C_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in LCD_G77_1_I2C_INTR_CAUSE_REG */
#define LCD_G77_1_I2C_CHECK_CAUSE_INTR(sourceMask)    (0u != (LCD_G77_1_I2C_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define LCD_G77_1_I2C_CHECK_INTR_I2C_EC(sourceMask)  (0u != (LCD_G77_1_I2C_INTR_I2C_EC_REG & (sourceMask)))
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CHECK_INTR_SPI_EC(sourceMask)  (0u != (LCD_G77_1_I2C_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */
#define LCD_G77_1_I2C_CHECK_INTR_MASTER(sourceMask)  (0u != (LCD_G77_1_I2C_INTR_MASTER_REG & (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_SLAVE(sourceMask)   (0u != (LCD_G77_1_I2C_INTR_SLAVE_REG  & (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_TX(sourceMask)      (0u != (LCD_G77_1_I2C_INTR_TX_REG     & (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_RX(sourceMask)      (0u != (LCD_G77_1_I2C_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in LCD_G77_1_I2C_INTR_X_MASKED_REG */
#define LCD_G77_1_I2C_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (LCD_G77_1_I2C_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (LCD_G77_1_I2C_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */
#define LCD_G77_1_I2C_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (LCD_G77_1_I2C_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (LCD_G77_1_I2C_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (LCD_G77_1_I2C_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define LCD_G77_1_I2C_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (LCD_G77_1_I2C_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in LCD_G77_1_I2C_CTRL_REG: generally is used to check enable bit */
#define LCD_G77_1_I2C_GET_CTRL_ENABLED    (0u != (LCD_G77_1_I2C_CTRL_REG & LCD_G77_1_I2C_CTRL_ENABLED))

#define LCD_G77_1_I2C_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (LCD_G77_1_I2C_I2C_CTRL_REG & \
                                                                LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define LCD_G77_1_I2C_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCD_G77_1_I2C_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LCD_G77_1_I2C_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCD_G77_1_I2C_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LCD_G77_1_I2C_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define LCD_G77_1_I2C_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ~LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCD_G77_1_I2C_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ~LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LCD_G77_1_I2C_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ~LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LCD_G77_1_I2C_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ~LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LCD_G77_1_I2C_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ~LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define LCD_G77_1_I2C_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                LCD_G77_1_I2C_I2C_CTRL_REG |= (LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define LCD_G77_1_I2C_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define LCD_G77_1_I2C_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                LCD_G77_1_I2C_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)
/* Disables auto data ACK/NACK bits */
#define LCD_G77_1_I2C_DISABLE_AUTO_DATA \
                do{                        \
                    LCD_G77_1_I2C_I2C_CTRL_REG &= ((uint32) ~(LCD_G77_1_I2C_I2C_CTRL_M_READY_DATA_ACK      |  \
                                                                 LCD_G77_1_I2C_I2C_CTRL_M_NOT_READY_DATA_NACK |  \
                                                                 LCD_G77_1_I2C_I2C_CTRL_S_READY_DATA_ACK      |  \
                                                                 LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                }while(0)

/* Master commands */
#define LCD_G77_1_I2C_I2C_MASTER_GENERATE_START \
                            do{                    \
                                LCD_G77_1_I2C_I2C_MASTER_CMD_REG = LCD_G77_1_I2C_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define LCD_G77_1_I2C_I2C_MASTER_CLEAR_START \
                            do{                 \
                                LCD_G77_1_I2C_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define LCD_G77_1_I2C_I2C_MASTER_GENERATE_RESTART LCD_G77_1_I2C_I2CReStartGeneration()

#define LCD_G77_1_I2C_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                LCD_G77_1_I2C_I2C_MASTER_CMD_REG =                                            \
                                    (LCD_G77_1_I2C_I2C_MASTER_CMD_M_STOP |                                    \
                                        (LCD_G77_1_I2C_CHECK_I2C_STATUS(LCD_G77_1_I2C_I2C_STATUS_M_READ) ? \
                                            (LCD_G77_1_I2C_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define LCD_G77_1_I2C_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                LCD_G77_1_I2C_I2C_MASTER_CMD_REG = LCD_G77_1_I2C_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define LCD_G77_1_I2C_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                LCD_G77_1_I2C_I2C_MASTER_CMD_REG = LCD_G77_1_I2C_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define LCD_G77_1_I2C_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                LCD_G77_1_I2C_I2C_SLAVE_CMD_REG = LCD_G77_1_I2C_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void LCD_G77_1_I2C_I2CSlaveNackGeneration(void);
    #define LCD_G77_1_I2C_I2C_SLAVE_GENERATE_NACK LCD_G77_1_I2C_I2CSlaveNackGeneration()

#else
    #define LCD_G77_1_I2C_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                LCD_G77_1_I2C_I2C_SLAVE_CMD_REG = LCD_G77_1_I2C_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                LCD_G77_1_I2C_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define LCD_G77_1_I2C_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    LCD_G77_1_I2C_I2C_SLAVE_ADDR_POS)) & \
                                                                        LCD_G77_1_I2C_I2C_SLAVE_ADDR_MASK)

#define LCD_G77_1_I2C_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> LCD_G77_1_I2C_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define LCD_G77_1_I2C_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define LCD_G77_1_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (LCD_G77_1_I2C_CY_SCBIP_V0)
    #define LCD_G77_1_I2C_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            LCD_G77_1_I2C_I2C_CFG_REG =                  \
                            ((LCD_G77_1_I2C_I2C_CFG_REG & (uint32) ~LCD_G77_1_I2C_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<LCD_G77_1_I2C_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define LCD_G77_1_I2C_DIGITAL_FILTER_DISABLE    (0u)
#define LCD_G77_1_I2C_DIGITAL_FILTER_ENABLE     (1u)
#define LCD_G77_1_I2C_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (LCD_G77_1_I2C_CY_SCBIP_V0)
    /* LCD_G77_1_I2C_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define LCD_G77_1_I2C_I2C_CFG_FILT_MASK  (LCD_G77_1_I2C_I2C_CFG_SDA_FILT_ENABLED | \
                                                 LCD_G77_1_I2C_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* LCD_G77_1_I2C_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define LCD_G77_1_I2C_I2C_CFG_FILT_MASK  (LCD_G77_1_I2C_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 LCD_G77_1_I2C_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */

#define LCD_G77_1_I2C_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            LCD_G77_1_I2C_I2C_CFG_REG &= (uint32) ~LCD_G77_1_I2C_I2C_CFG_FILT_MASK; \
        }while(0)

#define LCD_G77_1_I2C_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            LCD_G77_1_I2C_I2C_CFG_REG |= (uint32)  LCD_G77_1_I2C_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define LCD_G77_1_I2C_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in LCD_G77_1_I2C_I2C_STATUS_REG */
#define LCD_G77_1_I2C_CHECK_I2C_STATUS(sourceMask)   (0u != (LCD_G77_1_I2C_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in LCD_G77_1_I2C_SPI_STATUS_REG */
#define LCD_G77_1_I2C_CHECK_SPI_STATUS(sourceMask)   (0u != (LCD_G77_1_I2C_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on LCD_G77_1_I2C_CTRL_BYTE_MODE bit */
#define LCD_G77_1_I2C_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * LCD_G77_1_I2C_FIFO_SIZE) : (LCD_G77_1_I2C_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* LCD_G77_1_I2C_CTRL */
#define LCD_G77_1_I2C_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & LCD_G77_1_I2C_CTRL_OVS_MASK)

#define LCD_G77_1_I2C_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (LCD_G77_1_I2C_CTRL_EC_OP_MODE)  : (0u))

#define LCD_G77_1_I2C_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (LCD_G77_1_I2C_CTRL_EC_AM_MODE)  : (0u))

#define LCD_G77_1_I2C_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (LCD_G77_1_I2C_CTRL_BLOCK)       : (0u))

#define LCD_G77_1_I2C_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (LCD_G77_1_I2C_CTRL_ADDR_ACCEPT) : (0u))

#if (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define LCD_G77_1_I2C_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (LCD_G77_1_I2C_CTRL_BYTE_MODE) : (0u))
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

/* LCD_G77_1_I2C_I2C_CTRL */
#define LCD_G77_1_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        LCD_G77_1_I2C_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define LCD_G77_1_I2C_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    LCD_G77_1_I2C_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    LCD_G77_1_I2C_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define LCD_G77_1_I2C_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (LCD_G77_1_I2C_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define LCD_G77_1_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (LCD_G77_1_I2C_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define LCD_G77_1_I2C_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << LCD_G77_1_I2C_I2C_CTRL_SLAVE_MODE_POS)

/* LCD_G77_1_I2C_SPI_CTRL */
#define LCD_G77_1_I2C_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (LCD_G77_1_I2C_SPI_CTRL_CONTINUOUS) : (0u))

#define LCD_G77_1_I2C_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (LCD_G77_1_I2C_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define LCD_G77_1_I2C_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        LCD_G77_1_I2C_SPI_CTRL_CPHA_POS) & \
                                                                        LCD_G77_1_I2C_SPI_CTRL_SCLK_MODE_MASK)

#define LCD_G77_1_I2C_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (LCD_G77_1_I2C_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define LCD_G77_1_I2C_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define LCD_G77_1_I2C_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (LCD_G77_1_I2C_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define LCD_G77_1_I2C_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     LCD_G77_1_I2C_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << LCD_G77_1_I2C_SPI_CTRL_MODE_POS) & \
                                                                                 LCD_G77_1_I2C_SPI_CTRL_MODE_MASK)

#define LCD_G77_1_I2C_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      LCD_G77_1_I2C_SPI_CTRL_SLAVE_SELECT_MASK)

#define LCD_G77_1_I2C_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (LCD_G77_1_I2C_SPI_CTRL_MASTER) : (0u))

/* LCD_G77_1_I2C_UART_CTRL */
#define LCD_G77_1_I2C_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            LCD_G77_1_I2C_UART_CTRL_MODE_POS) & \
                                                                            LCD_G77_1_I2C_UART_CTRL_MODE_MASK)

/* LCD_G77_1_I2C_UART_RX_CTRL */
#define LCD_G77_1_I2C_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        LCD_G77_1_I2C_UART_RX_CTRL_STOP_BITS_MASK)

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (LCD_G77_1_I2C_UART_RX_CTRL_PARITY) : (0u))

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (LCD_G77_1_I2C_UART_RX_CTRL_POLARITY) : (0u))

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LCD_G77_1_I2C_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (LCD_G77_1_I2C_UART_RX_CTRL_MP_MODE) : (0u))

#define LCD_G77_1_I2C_GET_UART_RX_CTRL_BREAK_WIDTH(width)    (((uint32) ((uint32) (width) - 1u) << \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_BREAK_WIDTH_POS) & \
                                                                    LCD_G77_1_I2C_UART_RX_CTRL_BREAK_WIDTH_MASK)

/* LCD_G77_1_I2C_UART_TX_CTRL */
#define LCD_G77_1_I2C_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                LCD_G77_1_I2C_UART_RX_CTRL_STOP_BITS_MASK)

#define LCD_G77_1_I2C_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (LCD_G77_1_I2C_UART_TX_CTRL_PARITY) : (0u))

#define LCD_G77_1_I2C_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (LCD_G77_1_I2C_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* LCD_G77_1_I2C_UART_FLOW_CTRL */
#if !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 LCD_G77_1_I2C_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define LCD_G77_1_I2C_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LCD_G77_1_I2C_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define LCD_G77_1_I2C_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define LCD_G77_1_I2C_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (LCD_G77_1_I2C_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

/* LCD_G77_1_I2C_RX_CTRL */
#define LCD_G77_1_I2C_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LCD_G77_1_I2C_RX_CTRL_DATA_WIDTH_MASK)

#define LCD_G77_1_I2C_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LCD_G77_1_I2C_RX_CTRL_MSB_FIRST) : (0u))

#define LCD_G77_1_I2C_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (LCD_G77_1_I2C_RX_CTRL_MEDIAN) : (0u))

/* LCD_G77_1_I2C_RX_MATCH */
#define LCD_G77_1_I2C_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & LCD_G77_1_I2C_RX_MATCH_ADDR_MASK)
#define LCD_G77_1_I2C_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            LCD_G77_1_I2C_RX_MATCH_MASK_POS) & \
                                                            LCD_G77_1_I2C_RX_MATCH_MASK_MASK)

/* LCD_G77_1_I2C_RX_FIFO_CTRL */
#define LCD_G77_1_I2C_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LCD_G77_1_I2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LCD_G77_1_I2C_TX_CTRL */
#define LCD_G77_1_I2C_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LCD_G77_1_I2C_TX_CTRL_DATA_WIDTH_MASK)

#define LCD_G77_1_I2C_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LCD_G77_1_I2C_TX_CTRL_MSB_FIRST) : (0u))

/* LCD_G77_1_I2C_TX_FIFO_CTRL */
#define LCD_G77_1_I2C_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LCD_G77_1_I2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL */
#define LCD_G77_1_I2C_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (LCD_G77_1_I2C_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled LCD_G77_1_I2C_SPI_CTRL_REG */
#define LCD_G77_1_I2C_CHECK_SPI_MASTER   (0u != (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define LCD_G77_1_I2C_GET_SPI_SCLK_INACTIVE \
            ((0u == (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1)
#define LCD_G77_1_I2C_GET_SPI_SS0_INACTIVE       (1u)
#define LCD_G77_1_I2C_GET_SPI_SS1_INACTIVE       (1u)
#define LCD_G77_1_I2C_GET_SPI_SS2_INACTIVE       (1u)
#define LCD_G77_1_I2C_GET_SPI_SS3_INACTIVE       (1u)
#define LCD_G77_1_I2C_GET_UART_RTS_INACTIVE      (1u)

#else
#define LCD_G77_1_I2C_GET_SPI_SS0_INACTIVE  \
        ((0u != (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define LCD_G77_1_I2C_GET_SPI_SS1_INACTIVE  \
        ((0u != (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define LCD_G77_1_I2C_GET_SPI_SS2_INACTIVE  \
        ((0u != (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define LCD_G77_1_I2C_GET_SPI_SS3_INACTIVE  \
        ((0u != (LCD_G77_1_I2C_SPI_CTRL_REG & LCD_G77_1_I2C_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define LCD_G77_1_I2C_GET_UART_RTS_INACTIVE \
        ((0u == (LCD_G77_1_I2C_UART_FLOW_CTRL_REG & LCD_G77_1_I2C_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(LCD_G77_1_I2C_CY_SCBIP_V0 || LCD_G77_1_I2C_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define LCD_G77_1_I2C_CLEAR_REG          ((uint32) (0u))
#define LCD_G77_1_I2C_NO_INTR_SOURCES    ((uint32) (0u))
#define LCD_G77_1_I2C_DUMMY_PARAM        ((uint32) (0u))
#define LCD_G77_1_I2C_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define LCD_G77_1_I2C_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define LCD_G77_1_I2C_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define LCD_G77_1_I2C_CHECK_INTR_EC_I2C(sourceMask)  LCD_G77_1_I2C_CHECK_INTR_I2C_EC(sourceMask)
#if (!LCD_G77_1_I2C_CY_SCBIP_V1)
    #define LCD_G77_1_I2C_CHECK_INTR_EC_SPI(sourceMask)  LCD_G77_1_I2C_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

#define LCD_G77_1_I2C_CY_SCBIP_V1_I2C_ONLY   (LCD_G77_1_I2C_CY_SCBIP_V1)
#define LCD_G77_1_I2C_EZBUFFER_SIZE          (LCD_G77_1_I2C_EZ_DATA_NR)

#define LCD_G77_1_I2C_EZBUF_DATA00_REG   LCD_G77_1_I2C_EZBUF_DATA0_REG
#define LCD_G77_1_I2C_EZBUF_DATA00_PTR   LCD_G77_1_I2C_EZBUF_DATA0_PTR

#endif /* (CY_SCB_LCD_G77_1_I2C_H) */


/* [] END OF FILE */
