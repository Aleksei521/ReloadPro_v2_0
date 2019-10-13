/***************************************************************************//**
* \file Display_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Display_I2C_PVT.h"

#if (Display_I2C_SCB_MODE_I2C_INC)
    #include "Display_I2C_I2C_PVT.h"
#endif /* (Display_I2C_SCB_MODE_I2C_INC) */

#if (Display_I2C_SCB_MODE_EZI2C_INC)
    #include "Display_I2C_EZI2C_PVT.h"
#endif /* (Display_I2C_SCB_MODE_EZI2C_INC) */

#if (Display_I2C_SCB_MODE_SPI_INC || Display_I2C_SCB_MODE_UART_INC)
    #include "Display_I2C_SPI_UART_PVT.h"
#endif /* (Display_I2C_SCB_MODE_SPI_INC || Display_I2C_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 Display_I2C_scbMode = Display_I2C_SCB_MODE_UNCONFIG;
    uint8 Display_I2C_scbEnableWake;
    uint8 Display_I2C_scbEnableIntr;

    /* I2C configuration variables */
    uint8 Display_I2C_mode;
    uint8 Display_I2C_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * Display_I2C_rxBuffer;
    uint8  Display_I2C_rxDataBits;
    uint32 Display_I2C_rxBufferSize;

    volatile uint8 * Display_I2C_txBuffer;
    uint8  Display_I2C_txDataBits;
    uint32 Display_I2C_txBufferSize;

    /* EZI2C configuration variables */
    uint8 Display_I2C_numberOfAddr;
    uint8 Display_I2C_subAddrSize;
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** Display_I2C_initVar indicates whether the Display_I2C 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the Display_I2C_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  Display_I2C_Init() function can be called before the 
*  Display_I2C_Start() or Display_I2C_Enable() function.
*/
uint8 Display_I2C_initVar = 0u;


#if (! (Display_I2C_SCB_MODE_I2C_CONST_CFG || \
        Display_I2C_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * Display_I2C_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent Display_I2C_Enable() call.
    */
    uint16 Display_I2C_IntrTxMask = 0u;
#endif /* (! (Display_I2C_SCB_MODE_I2C_CONST_CFG || \
              Display_I2C_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (Display_I2C_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER)
    void (*Display_I2C_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER) */
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void Display_I2C_ScbEnableIntr(void);
static void Display_I2C_ScbModeStop(void);
static void Display_I2C_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: Display_I2C_Init
****************************************************************************//**
*
*  Initializes the Display_I2C component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  Display_I2C_I2CInit, Display_I2C_SpiInit, 
*  Display_I2C_UartInit or Display_I2C_EzI2CInit.
*
*******************************************************************************/
void Display_I2C_Init(void)
{
#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    if (Display_I2C_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Display_I2C_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (Display_I2C_SCB_MODE_I2C_CONST_CFG)
    Display_I2C_I2CInit();

#elif (Display_I2C_SCB_MODE_SPI_CONST_CFG)
    Display_I2C_SpiInit();

#elif (Display_I2C_SCB_MODE_UART_CONST_CFG)
    Display_I2C_UartInit();

#elif (Display_I2C_SCB_MODE_EZI2C_CONST_CFG)
    Display_I2C_EzI2CInit();

#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Display_I2C_Enable
****************************************************************************//**
*
*  Enables Display_I2C component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  Display_I2C_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The Display_I2C configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured Display_I2C”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void Display_I2C_Enable(void)
{
#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!Display_I2C_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Display_I2C_CTRL_REG |= Display_I2C_CTRL_ENABLED;

        Display_I2C_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        Display_I2C_ScbModePostEnable();
    }
#else
    Display_I2C_CTRL_REG |= Display_I2C_CTRL_ENABLED;

    Display_I2C_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    Display_I2C_ScbModePostEnable();
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Display_I2C_Start
****************************************************************************//**
*
*  Invokes Display_I2C_Init() and Display_I2C_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  Display_I2C_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void Display_I2C_Start(void)
{
    if (0u == Display_I2C_initVar)
    {
        Display_I2C_Init();
        Display_I2C_initVar = 1u; /* Component was initialized */
    }

    Display_I2C_Enable();
}


/*******************************************************************************
* Function Name: Display_I2C_Stop
****************************************************************************//**
*
*  Disables the Display_I2C component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function Display_I2C_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void Display_I2C_Stop(void)
{
#if (Display_I2C_SCB_IRQ_INTERNAL)
    Display_I2C_DisableInt();
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    Display_I2C_ScbModeStop();

    /* Disable SCB IP */
    Display_I2C_CTRL_REG &= (uint32) ~Display_I2C_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    Display_I2C_SetTxInterruptMode(Display_I2C_NO_INTR_SOURCES);

#if (Display_I2C_SCB_IRQ_INTERNAL)
    Display_I2C_ClearPendingInt();
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Display_I2C_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void Display_I2C_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = Display_I2C_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~Display_I2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (Display_I2C_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Display_I2C_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: Display_I2C_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void Display_I2C_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = Display_I2C_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~Display_I2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (Display_I2C_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Display_I2C_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (Display_I2C_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: Display_I2C_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void Display_I2C_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER)
        Display_I2C_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_Display_I2C_CUSTOM_INTR_HANDLER) */
    }
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: Display_I2C_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void Display_I2C_ScbEnableIntr(void)
{
#if (Display_I2C_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != Display_I2C_scbEnableIntr)
        {
            Display_I2C_EnableInt();
        }

    #else
        Display_I2C_EnableInt();

    #endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (Display_I2C_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Display_I2C_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void Display_I2C_ScbModePostEnable(void)
{
#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!Display_I2C_CY_SCBIP_V1)
    if (Display_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        Display_I2C_SpiPostEnable();
    }
    else if (Display_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        Display_I2C_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!Display_I2C_CY_SCBIP_V1) */

#elif (Display_I2C_SCB_MODE_SPI_CONST_CFG)
    Display_I2C_SpiPostEnable();

#elif (Display_I2C_SCB_MODE_UART_CONST_CFG)
    Display_I2C_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Display_I2C_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void Display_I2C_ScbModeStop(void)
{
#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    if (Display_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        Display_I2C_I2CStop();
    }
    else if (Display_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Display_I2C_EzI2CStop();
    }
#if (!Display_I2C_CY_SCBIP_V1)
    else if (Display_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        Display_I2C_SpiStop();
    }
    else if (Display_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        Display_I2C_UartStop();
    }
#endif /* (!Display_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (Display_I2C_SCB_MODE_I2C_CONST_CFG)
    Display_I2C_I2CStop();

#elif (Display_I2C_SCB_MODE_EZI2C_CONST_CFG)
    Display_I2C_EzI2CStop();

#elif (Display_I2C_SCB_MODE_SPI_CONST_CFG)
    Display_I2C_SpiStop();

#elif (Display_I2C_SCB_MODE_UART_CONST_CFG)
    Display_I2C_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Display_I2C_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void Display_I2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[Display_I2C_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!Display_I2C_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!Display_I2C_CY_SCBIP_V1) */
        
        uint32 hsiomSel[Display_I2C_SCB_PINS_NUMBER] = 
        {
            Display_I2C_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            Display_I2C_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (Display_I2C_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (Display_I2C_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < Display_I2C_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = Display_I2C_PIN_DM_ALG_HIZ;
        }

        if ((Display_I2C_SCB_MODE_I2C   == mode) ||
            (Display_I2C_SCB_MODE_EZI2C == mode))
        {
        #if (Display_I2C_RX_SCL_MOSI_PIN)
            hsiomSel[Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_OD_LO;
        #elif (Display_I2C_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_OD_LO;
        #else
        #endif /* (Display_I2C_RX_SCL_MOSI_PIN) */
        
        #if (Display_I2C_TX_SDA_MISO_PIN)
            hsiomSel[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_PIN_DM_OD_LO;
        #endif /* (Display_I2C_TX_SDA_MISO_PIN) */
        }
    #if (!Display_I2C_CY_SCBIP_V1)
        else if (Display_I2C_SCB_MODE_SPI == mode)
        {
        #if (Display_I2C_RX_SCL_MOSI_PIN)
            hsiomSel[Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (Display_I2C_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (Display_I2C_RX_SCL_MOSI_PIN) */
        
        #if (Display_I2C_TX_SDA_MISO_PIN)
            hsiomSel[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (Display_I2C_TX_SDA_MISO_PIN) */
        
        #if (Display_I2C_SCLK_PIN)
            hsiomSel[Display_I2C_SCLK_PIN_INDEX] = Display_I2C_SCLK_HSIOM_SEL_SPI;
        #endif /* (Display_I2C_SCLK_PIN) */

            if (Display_I2C_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
                pinsDm[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsDm[Display_I2C_SCLK_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;

            #if (Display_I2C_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[Display_I2C_SS0_PIN_INDEX] = Display_I2C_SS0_HSIOM_SEL_SPI;
                pinsDm  [Display_I2C_SS0_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
            #endif /* (Display_I2C_SS0_PIN) */

            #if (Display_I2C_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= Display_I2C_TX_SDA_MISO_PIN_MASK;
            #endif /* (Display_I2C_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsDm[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
                pinsDm[Display_I2C_SCLK_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;

            #if (Display_I2C_SS0_PIN)
                hsiomSel [Display_I2C_SS0_PIN_INDEX] = Display_I2C_SS0_HSIOM_SEL_SPI;
                pinsDm   [Display_I2C_SS0_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsInBuf |= Display_I2C_SS0_PIN_MASK;
            #endif /* (Display_I2C_SS0_PIN) */

            #if (Display_I2C_SS1_PIN)
                hsiomSel [Display_I2C_SS1_PIN_INDEX] = Display_I2C_SS1_HSIOM_SEL_SPI;
                pinsDm   [Display_I2C_SS1_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsInBuf |= Display_I2C_SS1_PIN_MASK;
            #endif /* (Display_I2C_SS1_PIN) */

            #if (Display_I2C_SS2_PIN)
                hsiomSel [Display_I2C_SS2_PIN_INDEX] = Display_I2C_SS2_HSIOM_SEL_SPI;
                pinsDm   [Display_I2C_SS2_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsInBuf |= Display_I2C_SS2_PIN_MASK;
            #endif /* (Display_I2C_SS2_PIN) */

            #if (Display_I2C_SS3_PIN)
                hsiomSel [Display_I2C_SS3_PIN_INDEX] = Display_I2C_SS3_HSIOM_SEL_SPI;
                pinsDm   [Display_I2C_SS3_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                pinsInBuf |= Display_I2C_SS3_PIN_MASK;
            #endif /* (Display_I2C_SS3_PIN) */

                /* Disable input buffers */
            #if (Display_I2C_RX_SCL_MOSI_PIN)
                pinsInBuf |= Display_I2C_RX_SCL_MOSI_PIN_MASK;
            #elif (Display_I2C_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= Display_I2C_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (Display_I2C_RX_SCL_MOSI_PIN) */

            #if (Display_I2C_SCLK_PIN)
                pinsInBuf |= Display_I2C_SCLK_PIN_MASK;
            #endif /* (Display_I2C_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (Display_I2C_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (Display_I2C_TX_SDA_MISO_PIN)
                hsiomSel[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_PIN_DM_OD_LO;
            #endif /* (Display_I2C_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (Display_I2C_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (Display_I2C_RX_SCL_MOSI_PIN)
                    hsiomSel[Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [Display_I2C_RX_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
                #elif (Display_I2C_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX] = Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
                #else
                #endif /* (Display_I2C_RX_SCL_MOSI_PIN) */
                }

                if (0u != (Display_I2C_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (Display_I2C_TX_SDA_MISO_PIN)
                    hsiomSel[Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [Display_I2C_TX_SDA_MISO_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= Display_I2C_TX_SDA_MISO_PIN_MASK;
                #endif /* (Display_I2C_TX_SDA_MISO_PIN) */
                }

            #if !(Display_I2C_CY_SCBIP_V0 || Display_I2C_CY_SCBIP_V1)
                if (Display_I2C_UART_MODE_STD == subMode)
                {
                    if (0u != (Display_I2C_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (Display_I2C_SCLK_PIN)
                        hsiomSel[Display_I2C_SCLK_PIN_INDEX] = Display_I2C_SCLK_HSIOM_SEL_UART;
                        pinsDm  [Display_I2C_SCLK_PIN_INDEX] = Display_I2C_PIN_DM_DIG_HIZ;
                    #endif /* (Display_I2C_SCLK_PIN) */
                    }

                    if (0u != (Display_I2C_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (Display_I2C_SS0_PIN)
                        hsiomSel[Display_I2C_SS0_PIN_INDEX] = Display_I2C_SS0_HSIOM_SEL_UART;
                        pinsDm  [Display_I2C_SS0_PIN_INDEX] = Display_I2C_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= Display_I2C_SS0_PIN_MASK;
                    #endif /* (Display_I2C_SS0_PIN) */
                    }
                }
            #endif /* !(Display_I2C_CY_SCBIP_V0 || Display_I2C_CY_SCBIP_V1) */
            }
        }
    #endif /* (!Display_I2C_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (Display_I2C_RX_SCL_MOSI_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_RX_SCL_MOSI_HSIOM_REG,
                                       Display_I2C_RX_SCL_MOSI_HSIOM_MASK,
                                       Display_I2C_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[Display_I2C_RX_SCL_MOSI_PIN_INDEX]);

        Display_I2C_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[Display_I2C_RX_SCL_MOSI_PIN_INDEX]);

        #if (!Display_I2C_CY_SCBIP_V1)
            Display_I2C_SET_INP_DIS(Display_I2C_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         Display_I2C_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & Display_I2C_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!Display_I2C_CY_SCBIP_V1) */
    
    #elif (Display_I2C_RX_WAKE_SCL_MOSI_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       Display_I2C_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        Display_I2C_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[Display_I2C_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     Display_I2C_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & Display_I2C_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        Display_I2C_SET_INCFG_TYPE(Display_I2C_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        Display_I2C_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        Display_I2C_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        Display_I2C_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (Display_I2C_RX_WAKE_SCL_MOSI_PIN) */

    #if (Display_I2C_TX_SDA_MISO_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_TX_SDA_MISO_HSIOM_REG,
                                       Display_I2C_TX_SDA_MISO_HSIOM_MASK,
                                       Display_I2C_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[Display_I2C_TX_SDA_MISO_PIN_INDEX]);

        Display_I2C_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[Display_I2C_TX_SDA_MISO_PIN_INDEX]);

    #if (!Display_I2C_CY_SCBIP_V1)
        Display_I2C_SET_INP_DIS(Display_I2C_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     Display_I2C_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & Display_I2C_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!Display_I2C_CY_SCBIP_V1) */
    #endif /* (Display_I2C_RX_SCL_MOSI_PIN) */

    #if (Display_I2C_SCLK_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_SCLK_HSIOM_REG,
                                       Display_I2C_SCLK_HSIOM_MASK,
                                       Display_I2C_SCLK_HSIOM_POS,
                                       hsiomSel[Display_I2C_SCLK_PIN_INDEX]);

        Display_I2C_spi_sclk_SetDriveMode((uint8) pinsDm[Display_I2C_SCLK_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_spi_sclk_INP_DIS,
                                     Display_I2C_spi_sclk_MASK,
                                     (0u != (pinsInBuf & Display_I2C_SCLK_PIN_MASK)));
    #endif /* (Display_I2C_SCLK_PIN) */

    #if (Display_I2C_SS0_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_SS0_HSIOM_REG,
                                       Display_I2C_SS0_HSIOM_MASK,
                                       Display_I2C_SS0_HSIOM_POS,
                                       hsiomSel[Display_I2C_SS0_PIN_INDEX]);

        Display_I2C_spi_ss0_SetDriveMode((uint8) pinsDm[Display_I2C_SS0_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_spi_ss0_INP_DIS,
                                     Display_I2C_spi_ss0_MASK,
                                     (0u != (pinsInBuf & Display_I2C_SS0_PIN_MASK)));
    #endif /* (Display_I2C_SS0_PIN) */

    #if (Display_I2C_SS1_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_SS1_HSIOM_REG,
                                       Display_I2C_SS1_HSIOM_MASK,
                                       Display_I2C_SS1_HSIOM_POS,
                                       hsiomSel[Display_I2C_SS1_PIN_INDEX]);

        Display_I2C_spi_ss1_SetDriveMode((uint8) pinsDm[Display_I2C_SS1_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_spi_ss1_INP_DIS,
                                     Display_I2C_spi_ss1_MASK,
                                     (0u != (pinsInBuf & Display_I2C_SS1_PIN_MASK)));
    #endif /* (Display_I2C_SS1_PIN) */

    #if (Display_I2C_SS2_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_SS2_HSIOM_REG,
                                       Display_I2C_SS2_HSIOM_MASK,
                                       Display_I2C_SS2_HSIOM_POS,
                                       hsiomSel[Display_I2C_SS2_PIN_INDEX]);

        Display_I2C_spi_ss2_SetDriveMode((uint8) pinsDm[Display_I2C_SS2_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_spi_ss2_INP_DIS,
                                     Display_I2C_spi_ss2_MASK,
                                     (0u != (pinsInBuf & Display_I2C_SS2_PIN_MASK)));
    #endif /* (Display_I2C_SS2_PIN) */

    #if (Display_I2C_SS3_PIN)
        Display_I2C_SET_HSIOM_SEL(Display_I2C_SS3_HSIOM_REG,
                                       Display_I2C_SS3_HSIOM_MASK,
                                       Display_I2C_SS3_HSIOM_POS,
                                       hsiomSel[Display_I2C_SS3_PIN_INDEX]);

        Display_I2C_spi_ss3_SetDriveMode((uint8) pinsDm[Display_I2C_SS3_PIN_INDEX]);

        Display_I2C_SET_INP_DIS(Display_I2C_spi_ss3_INP_DIS,
                                     Display_I2C_spi_ss3_MASK,
                                     (0u != (pinsInBuf & Display_I2C_SS3_PIN_MASK)));
    #endif /* (Display_I2C_SS3_PIN) */
    }

#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (Display_I2C_CY_SCBIP_V0 || Display_I2C_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: Display_I2C_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void Display_I2C_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (Display_I2C_CTRL_REG & Display_I2C_CTRL_EC_AM_MODE)) &&
            (0u == (Display_I2C_I2C_CTRL_REG & Display_I2C_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            Display_I2C_CTRL_REG &= ~Display_I2C_CTRL_EC_AM_MODE;
            Display_I2C_CTRL_REG |=  Display_I2C_CTRL_EC_AM_MODE;
        }

        Display_I2C_I2C_SLAVE_CMD_REG = Display_I2C_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (Display_I2C_CY_SCBIP_V0 || Display_I2C_CY_SCBIP_V1) */


/* [] END OF FILE */
