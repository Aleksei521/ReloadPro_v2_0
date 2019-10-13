/*******************************************************************************
* File Name: cooler_sensor.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_cooler_sensor_H) /* Pins cooler_sensor_H */
#define CY_PINS_cooler_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cooler_sensor_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} cooler_sensor_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cooler_sensor_Read(void);
void    cooler_sensor_Write(uint8 value);
uint8   cooler_sensor_ReadDataReg(void);
#if defined(cooler_sensor__PC) || (CY_PSOC4_4200L) 
    void    cooler_sensor_SetDriveMode(uint8 mode);
#endif
void    cooler_sensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   cooler_sensor_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cooler_sensor_Sleep(void); 
void cooler_sensor_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cooler_sensor__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cooler_sensor_DRIVE_MODE_BITS        (3)
    #define cooler_sensor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cooler_sensor_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cooler_sensor_SetDriveMode() function.
         *  @{
         */
        #define cooler_sensor_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cooler_sensor_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cooler_sensor_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cooler_sensor_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cooler_sensor_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cooler_sensor_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cooler_sensor_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cooler_sensor_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cooler_sensor_MASK               cooler_sensor__MASK
#define cooler_sensor_SHIFT              cooler_sensor__SHIFT
#define cooler_sensor_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cooler_sensor_SetInterruptMode() function.
     *  @{
     */
        #define cooler_sensor_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cooler_sensor_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cooler_sensor_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cooler_sensor_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cooler_sensor__SIO)
    #define cooler_sensor_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cooler_sensor__PC) && (CY_PSOC4_4200L)
    #define cooler_sensor_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cooler_sensor_USBIO_DISABLE              ((uint32)(~cooler_sensor_USBIO_ENABLE))
    #define cooler_sensor_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cooler_sensor_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cooler_sensor_USBIO_ENTER_SLEEP          ((uint32)((1u << cooler_sensor_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cooler_sensor_USBIO_SUSPEND_DEL_SHIFT)))
    #define cooler_sensor_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cooler_sensor_USBIO_SUSPEND_SHIFT)))
    #define cooler_sensor_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cooler_sensor_USBIO_SUSPEND_DEL_SHIFT)))
    #define cooler_sensor_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cooler_sensor__PC)
    /* Port Configuration */
    #define cooler_sensor_PC                 (* (reg32 *) cooler_sensor__PC)
#endif
/* Pin State */
#define cooler_sensor_PS                     (* (reg32 *) cooler_sensor__PS)
/* Data Register */
#define cooler_sensor_DR                     (* (reg32 *) cooler_sensor__DR)
/* Input Buffer Disable Override */
#define cooler_sensor_INP_DIS                (* (reg32 *) cooler_sensor__PC2)

/* Interrupt configuration Registers */
#define cooler_sensor_INTCFG                 (* (reg32 *) cooler_sensor__INTCFG)
#define cooler_sensor_INTSTAT                (* (reg32 *) cooler_sensor__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cooler_sensor_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cooler_sensor__SIO)
    #define cooler_sensor_SIO_REG            (* (reg32 *) cooler_sensor__SIO)
#endif /* (cooler_sensor__SIO_CFG) */

/* USBIO registers */
#if !defined(cooler_sensor__PC) && (CY_PSOC4_4200L)
    #define cooler_sensor_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cooler_sensor_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cooler_sensor_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cooler_sensor_DRIVE_MODE_SHIFT       (0x00u)
#define cooler_sensor_DRIVE_MODE_MASK        (0x07u << cooler_sensor_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cooler_sensor_H */


/* [] END OF FILE */
