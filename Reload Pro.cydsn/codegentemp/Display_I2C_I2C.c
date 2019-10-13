/***************************************************************************//**
* \file Display_I2C_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
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
#include "Display_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 Display_I2C_state;  /* Current state of I2C FSM */

#if(Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const Display_I2C_I2C_INIT_STRUCT Display_I2C_configI2C =
    {
        Display_I2C_I2C_MODE,
        Display_I2C_I2C_OVS_FACTOR_LOW,
        Display_I2C_I2C_OVS_FACTOR_HIGH,
        Display_I2C_I2C_MEDIAN_FILTER_ENABLE,
        Display_I2C_I2C_SLAVE_ADDRESS,
        Display_I2C_I2C_SLAVE_ADDRESS_MASK,
        Display_I2C_I2C_ACCEPT_ADDRESS,
        Display_I2C_I2C_WAKE_ENABLE,
        Display_I2C_I2C_BYTE_MODE_ENABLE,
        Display_I2C_I2C_DATA_RATE,
        Display_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: Display_I2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the Display_I2C for I2C operation.
    *
    *  This function is intended specifically to be used when the Display_I2C 
    *  configuration is set to “Unconfigured Display_I2C” in the customizer. 
    *  After initializing the Display_I2C in I2C mode using this function, 
    *  the component can be enabled using the Display_I2C_Start() or 
    * Display_I2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void Display_I2C_I2CInit(const Display_I2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            Display_I2C_SetPins(Display_I2C_SCB_MODE_I2C, Display_I2C_DUMMY_PARAM,
                                     Display_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            Display_I2C_scbMode       = (uint8) Display_I2C_SCB_MODE_I2C;
            Display_I2C_scbEnableWake = (uint8) config->enableWake;
            Display_I2C_scbEnableIntr = (uint8) Display_I2C_SCB_IRQ_INTERNAL;

            Display_I2C_mode          = (uint8) config->mode;
            Display_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (Display_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            Display_I2C_SET_I2C_CFG_SDA_FILT_TRIM(Display_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (Display_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((Display_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= Display_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (Display_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                Display_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = Display_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                Display_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = Display_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!Display_I2C_CY_SCBIP_V0)
            locEnableWake = (Display_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!Display_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            Display_I2C_CTRL_REG     = Display_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            Display_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            Display_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            Display_I2C_I2C_CTRL_REG = Display_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    Display_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    Display_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    Display_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            Display_I2C_RX_CTRL_REG      = Display_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                Display_I2C_I2C_RX_CTRL;
            Display_I2C_RX_FIFO_CTRL_REG = Display_I2C_CLEAR_REG;

            /* Set default address and mask */
            Display_I2C_RX_MATCH_REG    = ((Display_I2C_I2C_SLAVE) ?
                                                (Display_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 Display_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (Display_I2C_CLEAR_REG));


            /* Configure TX direction */
            Display_I2C_TX_CTRL_REG      = Display_I2C_I2C_TX_CTRL;
            Display_I2C_TX_FIFO_CTRL_REG = Display_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (Display_I2C_ISR_NUMBER);
            CyIntSetPriority(Display_I2C_ISR_NUMBER, Display_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(Display_I2C_ISR_NUMBER, &Display_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!Display_I2C_CY_SCBIP_V1)
            Display_I2C_INTR_SPI_EC_MASK_REG = Display_I2C_NO_INTR_SOURCES;
        #endif /* (!Display_I2C_CY_SCBIP_V1) */

            Display_I2C_INTR_I2C_EC_MASK_REG = Display_I2C_NO_INTR_SOURCES;
            Display_I2C_INTR_RX_MASK_REG     = Display_I2C_NO_INTR_SOURCES;
            Display_I2C_INTR_TX_MASK_REG     = Display_I2C_NO_INTR_SOURCES;

            Display_I2C_INTR_SLAVE_MASK_REG  = ((Display_I2C_I2C_SLAVE) ?
                            (Display_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             Display_I2C_I2C_INTR_SLAVE_MASK) : (Display_I2C_CLEAR_REG));

            Display_I2C_INTR_MASTER_MASK_REG = Display_I2C_NO_INTR_SOURCES;

            /* Configure global variables */
            Display_I2C_state = Display_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            Display_I2C_slStatus        = 0u;
            Display_I2C_slRdBufIndex    = 0u;
            Display_I2C_slWrBufIndex    = 0u;
            Display_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            Display_I2C_mstrStatus     = 0u;
            Display_I2C_mstrRdBufIndex = 0u;
            Display_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Display_I2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void Display_I2C_I2CInit(void)
    {
    #if(Display_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        Display_I2C_SET_I2C_CFG_SDA_FILT_TRIM(Display_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (Display_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        Display_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        Display_I2C_CTRL_REG     = Display_I2C_I2C_DEFAULT_CTRL;
        Display_I2C_I2C_CTRL_REG = Display_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        Display_I2C_RX_CTRL_REG      = Display_I2C_I2C_DEFAULT_RX_CTRL;
        Display_I2C_RX_FIFO_CTRL_REG = Display_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        Display_I2C_RX_MATCH_REG     = Display_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        Display_I2C_TX_CTRL_REG      = Display_I2C_I2C_DEFAULT_TX_CTRL;
        Display_I2C_TX_FIFO_CTRL_REG = Display_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (Display_I2C_ISR_NUMBER);
        CyIntSetPriority(Display_I2C_ISR_NUMBER, Display_I2C_ISR_PRIORITY);
    #if(!Display_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(Display_I2C_ISR_NUMBER, &Display_I2C_I2C_ISR);
    #endif /* (Display_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!Display_I2C_CY_SCBIP_V1)
        Display_I2C_INTR_SPI_EC_MASK_REG = Display_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!Display_I2C_CY_SCBIP_V1) */

        Display_I2C_INTR_I2C_EC_MASK_REG = Display_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        Display_I2C_INTR_SLAVE_MASK_REG  = Display_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        Display_I2C_INTR_MASTER_MASK_REG = Display_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        Display_I2C_INTR_RX_MASK_REG     = Display_I2C_I2C_DEFAULT_INTR_RX_MASK;
        Display_I2C_INTR_TX_MASK_REG     = Display_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        Display_I2C_state = Display_I2C_I2C_FSM_IDLE;

    #if(Display_I2C_I2C_SLAVE)
        /* Internal slave variable */
        Display_I2C_slStatus        = 0u;
        Display_I2C_slRdBufIndex    = 0u;
        Display_I2C_slWrBufIndex    = 0u;
        Display_I2C_slOverFlowCount = 0u;
    #endif /* (Display_I2C_I2C_SLAVE) */

    #if(Display_I2C_I2C_MASTER)
    /* Internal master variable */
        Display_I2C_mstrStatus     = 0u;
        Display_I2C_mstrRdBufIndex = 0u;
        Display_I2C_mstrWrBufIndex = 0u;
    #endif /* (Display_I2C_I2C_MASTER) */
    }
#endif /* (Display_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Display_I2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void Display_I2C_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    Display_I2C_I2C_MASTER_CMD_REG = 0u;
    Display_I2C_I2C_SLAVE_CMD_REG  = 0u;
    
    Display_I2C_state = Display_I2C_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: Display_I2C_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void Display_I2C_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    Display_I2C_CTRL_REG &= (uint32) ~Display_I2C_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    Display_I2C_I2C_MASTER_CMD_REG = 0u;
    Display_I2C_I2C_SLAVE_CMD_REG  = 0u;

    Display_I2C_DISABLE_AUTO_DATA;

    Display_I2C_SetTxInterruptMode(Display_I2C_NO_INTR_SOURCES);
    Display_I2C_SetRxInterruptMode(Display_I2C_NO_INTR_SOURCES);
    
#if(Display_I2C_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    Display_I2C_ClearTxInterruptSource    (Display_I2C_INTR_TX_ALL);
    Display_I2C_ClearRxInterruptSource    (Display_I2C_INTR_RX_ALL);
    Display_I2C_ClearSlaveInterruptSource (Display_I2C_INTR_SLAVE_ALL);
    Display_I2C_ClearMasterInterruptSource(Display_I2C_INTR_MASTER_ALL);
#endif /* (Display_I2C_CY_SCBIP_V0) */

    Display_I2C_state = Display_I2C_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    Display_I2C_CTRL_REG |= (uint32) Display_I2C_CTRL_ENABLED;
}


#if(Display_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Display_I2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables Display_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void Display_I2C_I2CSaveConfig(void)
    {
    #if (!Display_I2C_CY_SCBIP_V0)
        #if (Display_I2C_I2C_MULTI_MASTER_SLAVE_CONST && Display_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (Display_I2C_CTRL_REG & Display_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                Display_I2C_Stop();
                Display_I2C_CTRL_REG |= Display_I2C_CTRL_EC_AM_MODE;
                Display_I2C_Enable();
            }
        #endif /* (Display_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (Display_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            Display_I2C_SCBCLK_Stop();
        #endif /* (Display_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!Display_I2C_CY_SCBIP_V0) */

        Display_I2C_SetI2CExtClkInterruptMode(Display_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: Display_I2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables Display_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void Display_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        Display_I2C_SetI2CExtClkInterruptMode(Display_I2C_NO_INTR_SOURCES);

    #if (!Display_I2C_CY_SCBIP_V0)
        #if (Display_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            Display_I2C_SCBCLK_Start();
        #endif /* (Display_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!Display_I2C_CY_SCBIP_V0) */
    }
#endif /* (Display_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
