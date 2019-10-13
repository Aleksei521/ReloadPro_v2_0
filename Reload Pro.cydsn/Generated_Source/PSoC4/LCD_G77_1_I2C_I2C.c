/***************************************************************************//**
* \file LCD_G77_1_I2C_I2C.c
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

#include "LCD_G77_1_I2C_PVT.h"
#include "LCD_G77_1_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 LCD_G77_1_I2C_state;  /* Current state of I2C FSM */

#if(LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const LCD_G77_1_I2C_I2C_INIT_STRUCT LCD_G77_1_I2C_configI2C =
    {
        LCD_G77_1_I2C_I2C_MODE,
        LCD_G77_1_I2C_I2C_OVS_FACTOR_LOW,
        LCD_G77_1_I2C_I2C_OVS_FACTOR_HIGH,
        LCD_G77_1_I2C_I2C_MEDIAN_FILTER_ENABLE,
        LCD_G77_1_I2C_I2C_SLAVE_ADDRESS,
        LCD_G77_1_I2C_I2C_SLAVE_ADDRESS_MASK,
        LCD_G77_1_I2C_I2C_ACCEPT_ADDRESS,
        LCD_G77_1_I2C_I2C_WAKE_ENABLE,
        LCD_G77_1_I2C_I2C_BYTE_MODE_ENABLE,
        LCD_G77_1_I2C_I2C_DATA_RATE,
        LCD_G77_1_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the LCD_G77_1_I2C for I2C operation.
    *
    *  This function is intended specifically to be used when the LCD_G77_1_I2C 
    *  configuration is set to “Unconfigured LCD_G77_1_I2C” in the customizer. 
    *  After initializing the LCD_G77_1_I2C in I2C mode using this function, 
    *  the component can be enabled using the LCD_G77_1_I2C_Start() or 
    * LCD_G77_1_I2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void LCD_G77_1_I2C_I2CInit(const LCD_G77_1_I2C_I2C_INIT_STRUCT *config)
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
            LCD_G77_1_I2C_SetPins(LCD_G77_1_I2C_SCB_MODE_I2C, LCD_G77_1_I2C_DUMMY_PARAM,
                                     LCD_G77_1_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            LCD_G77_1_I2C_scbMode       = (uint8) LCD_G77_1_I2C_SCB_MODE_I2C;
            LCD_G77_1_I2C_scbEnableWake = (uint8) config->enableWake;
            LCD_G77_1_I2C_scbEnableIntr = (uint8) LCD_G77_1_I2C_SCB_IRQ_INTERNAL;

            LCD_G77_1_I2C_mode          = (uint8) config->mode;
            LCD_G77_1_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (LCD_G77_1_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            LCD_G77_1_I2C_SET_I2C_CFG_SDA_FILT_TRIM(LCD_G77_1_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((LCD_G77_1_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= LCD_G77_1_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (LCD_G77_1_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                LCD_G77_1_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = LCD_G77_1_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                LCD_G77_1_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = LCD_G77_1_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!LCD_G77_1_I2C_CY_SCBIP_V0)
            locEnableWake = (LCD_G77_1_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            LCD_G77_1_I2C_CTRL_REG     = LCD_G77_1_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            LCD_G77_1_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            LCD_G77_1_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            LCD_G77_1_I2C_I2C_CTRL_REG = LCD_G77_1_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    LCD_G77_1_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    LCD_G77_1_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    LCD_G77_1_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            LCD_G77_1_I2C_RX_CTRL_REG      = LCD_G77_1_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                LCD_G77_1_I2C_I2C_RX_CTRL;
            LCD_G77_1_I2C_RX_FIFO_CTRL_REG = LCD_G77_1_I2C_CLEAR_REG;

            /* Set default address and mask */
            LCD_G77_1_I2C_RX_MATCH_REG    = ((LCD_G77_1_I2C_I2C_SLAVE) ?
                                                (LCD_G77_1_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 LCD_G77_1_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (LCD_G77_1_I2C_CLEAR_REG));


            /* Configure TX direction */
            LCD_G77_1_I2C_TX_CTRL_REG      = LCD_G77_1_I2C_I2C_TX_CTRL;
            LCD_G77_1_I2C_TX_FIFO_CTRL_REG = LCD_G77_1_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (LCD_G77_1_I2C_ISR_NUMBER);
            CyIntSetPriority(LCD_G77_1_I2C_ISR_NUMBER, LCD_G77_1_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(LCD_G77_1_I2C_ISR_NUMBER, &LCD_G77_1_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!LCD_G77_1_I2C_CY_SCBIP_V1)
            LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG = LCD_G77_1_I2C_NO_INTR_SOURCES;
        #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

            LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG = LCD_G77_1_I2C_NO_INTR_SOURCES;
            LCD_G77_1_I2C_INTR_RX_MASK_REG     = LCD_G77_1_I2C_NO_INTR_SOURCES;
            LCD_G77_1_I2C_INTR_TX_MASK_REG     = LCD_G77_1_I2C_NO_INTR_SOURCES;

            LCD_G77_1_I2C_INTR_SLAVE_MASK_REG  = ((LCD_G77_1_I2C_I2C_SLAVE) ?
                            (LCD_G77_1_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             LCD_G77_1_I2C_I2C_INTR_SLAVE_MASK) : (LCD_G77_1_I2C_CLEAR_REG));

            LCD_G77_1_I2C_INTR_MASTER_MASK_REG = LCD_G77_1_I2C_NO_INTR_SOURCES;

            /* Configure global variables */
            LCD_G77_1_I2C_state = LCD_G77_1_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            LCD_G77_1_I2C_slStatus        = 0u;
            LCD_G77_1_I2C_slRdBufIndex    = 0u;
            LCD_G77_1_I2C_slWrBufIndex    = 0u;
            LCD_G77_1_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            LCD_G77_1_I2C_mstrStatus     = 0u;
            LCD_G77_1_I2C_mstrRdBufIndex = 0u;
            LCD_G77_1_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void LCD_G77_1_I2C_I2CInit(void)
    {
    #if(LCD_G77_1_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        LCD_G77_1_I2C_SET_I2C_CFG_SDA_FILT_TRIM(LCD_G77_1_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        LCD_G77_1_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        LCD_G77_1_I2C_CTRL_REG     = LCD_G77_1_I2C_I2C_DEFAULT_CTRL;
        LCD_G77_1_I2C_I2C_CTRL_REG = LCD_G77_1_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        LCD_G77_1_I2C_RX_CTRL_REG      = LCD_G77_1_I2C_I2C_DEFAULT_RX_CTRL;
        LCD_G77_1_I2C_RX_FIFO_CTRL_REG = LCD_G77_1_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        LCD_G77_1_I2C_RX_MATCH_REG     = LCD_G77_1_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        LCD_G77_1_I2C_TX_CTRL_REG      = LCD_G77_1_I2C_I2C_DEFAULT_TX_CTRL;
        LCD_G77_1_I2C_TX_FIFO_CTRL_REG = LCD_G77_1_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (LCD_G77_1_I2C_ISR_NUMBER);
        CyIntSetPriority(LCD_G77_1_I2C_ISR_NUMBER, LCD_G77_1_I2C_ISR_PRIORITY);
    #if(!LCD_G77_1_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(LCD_G77_1_I2C_ISR_NUMBER, &LCD_G77_1_I2C_I2C_ISR);
    #endif /* (LCD_G77_1_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!LCD_G77_1_I2C_CY_SCBIP_V1)
        LCD_G77_1_I2C_INTR_SPI_EC_MASK_REG = LCD_G77_1_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V1) */

        LCD_G77_1_I2C_INTR_I2C_EC_MASK_REG = LCD_G77_1_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        LCD_G77_1_I2C_INTR_SLAVE_MASK_REG  = LCD_G77_1_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        LCD_G77_1_I2C_INTR_MASTER_MASK_REG = LCD_G77_1_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        LCD_G77_1_I2C_INTR_RX_MASK_REG     = LCD_G77_1_I2C_I2C_DEFAULT_INTR_RX_MASK;
        LCD_G77_1_I2C_INTR_TX_MASK_REG     = LCD_G77_1_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        LCD_G77_1_I2C_state = LCD_G77_1_I2C_I2C_FSM_IDLE;

    #if(LCD_G77_1_I2C_I2C_SLAVE)
        /* Internal slave variable */
        LCD_G77_1_I2C_slStatus        = 0u;
        LCD_G77_1_I2C_slRdBufIndex    = 0u;
        LCD_G77_1_I2C_slWrBufIndex    = 0u;
        LCD_G77_1_I2C_slOverFlowCount = 0u;
    #endif /* (LCD_G77_1_I2C_I2C_SLAVE) */

    #if(LCD_G77_1_I2C_I2C_MASTER)
    /* Internal master variable */
        LCD_G77_1_I2C_mstrStatus     = 0u;
        LCD_G77_1_I2C_mstrRdBufIndex = 0u;
        LCD_G77_1_I2C_mstrWrBufIndex = 0u;
    #endif /* (LCD_G77_1_I2C_I2C_MASTER) */
    }
#endif /* (LCD_G77_1_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void LCD_G77_1_I2C_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    LCD_G77_1_I2C_I2C_MASTER_CMD_REG = 0u;
    LCD_G77_1_I2C_I2C_SLAVE_CMD_REG  = 0u;
    
    LCD_G77_1_I2C_state = LCD_G77_1_I2C_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: LCD_G77_1_I2C_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void LCD_G77_1_I2C_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    LCD_G77_1_I2C_CTRL_REG &= (uint32) ~LCD_G77_1_I2C_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    LCD_G77_1_I2C_I2C_MASTER_CMD_REG = 0u;
    LCD_G77_1_I2C_I2C_SLAVE_CMD_REG  = 0u;

    LCD_G77_1_I2C_DISABLE_AUTO_DATA;

    LCD_G77_1_I2C_SetTxInterruptMode(LCD_G77_1_I2C_NO_INTR_SOURCES);
    LCD_G77_1_I2C_SetRxInterruptMode(LCD_G77_1_I2C_NO_INTR_SOURCES);
    
#if(LCD_G77_1_I2C_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    LCD_G77_1_I2C_ClearTxInterruptSource    (LCD_G77_1_I2C_INTR_TX_ALL);
    LCD_G77_1_I2C_ClearRxInterruptSource    (LCD_G77_1_I2C_INTR_RX_ALL);
    LCD_G77_1_I2C_ClearSlaveInterruptSource (LCD_G77_1_I2C_INTR_SLAVE_ALL);
    LCD_G77_1_I2C_ClearMasterInterruptSource(LCD_G77_1_I2C_INTR_MASTER_ALL);
#endif /* (LCD_G77_1_I2C_CY_SCBIP_V0) */

    LCD_G77_1_I2C_state = LCD_G77_1_I2C_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    LCD_G77_1_I2C_CTRL_REG |= (uint32) LCD_G77_1_I2C_CTRL_ENABLED;
}


#if(LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void LCD_G77_1_I2C_I2CSaveConfig(void)
    {
    #if (!LCD_G77_1_I2C_CY_SCBIP_V0)
        #if (LCD_G77_1_I2C_I2C_MULTI_MASTER_SLAVE_CONST && LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (LCD_G77_1_I2C_CTRL_REG & LCD_G77_1_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                LCD_G77_1_I2C_Stop();
                LCD_G77_1_I2C_CTRL_REG |= LCD_G77_1_I2C_CTRL_EC_AM_MODE;
                LCD_G77_1_I2C_Enable();
            }
        #endif /* (LCD_G77_1_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (LCD_G77_1_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            LCD_G77_1_I2C_SCBCLK_Stop();
        #endif /* (LCD_G77_1_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V0) */

        LCD_G77_1_I2C_SetI2CExtClkInterruptMode(LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: LCD_G77_1_I2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables LCD_G77_1_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void LCD_G77_1_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        LCD_G77_1_I2C_SetI2CExtClkInterruptMode(LCD_G77_1_I2C_NO_INTR_SOURCES);

    #if (!LCD_G77_1_I2C_CY_SCBIP_V0)
        #if (LCD_G77_1_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            LCD_G77_1_I2C_SCBCLK_Start();
        #endif /* (LCD_G77_1_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!LCD_G77_1_I2C_CY_SCBIP_V0) */
    }
#endif /* (LCD_G77_1_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
