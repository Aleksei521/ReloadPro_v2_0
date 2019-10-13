/*******************************************************************************
* File Name: fan.h  
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

#if !defined(CY_PINS_fan_H) /* Pins fan_H */
#define CY_PINS_fan_H

#include "cytypes.h"
#include "cyfitter.h"
#include "fan_aliases.h"


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
} fan_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   fan_Read(void);
void    fan_Write(uint8 value);
uint8   fan_ReadDataReg(void);
#if defined(fan__PC) || (CY_PSOC4_4200L) 
    void    fan_SetDriveMode(uint8 mode);
#endif
void    fan_SetInterruptMode(uint16 position, uint16 mode);
uint8   fan_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void fan_Sleep(void); 
void fan_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(fan__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define fan_DRIVE_MODE_BITS        (3)
    #define fan_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - fan_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the fan_SetDriveMode() function.
         *  @{
         */
        #define fan_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define fan_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define fan_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define fan_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define fan_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define fan_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define fan_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define fan_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define fan_MASK               fan__MASK
#define fan_SHIFT              fan__SHIFT
#define fan_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fan_SetInterruptMode() function.
     *  @{
     */
        #define fan_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define fan_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define fan_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define fan_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(fan__SIO)
    #define fan_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(fan__PC) && (CY_PSOC4_4200L)
    #define fan_USBIO_ENABLE               ((uint32)0x80000000u)
    #define fan_USBIO_DISABLE              ((uint32)(~fan_USBIO_ENABLE))
    #define fan_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define fan_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define fan_USBIO_ENTER_SLEEP          ((uint32)((1u << fan_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << fan_USBIO_SUSPEND_DEL_SHIFT)))
    #define fan_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << fan_USBIO_SUSPEND_SHIFT)))
    #define fan_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << fan_USBIO_SUSPEND_DEL_SHIFT)))
    #define fan_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(fan__PC)
    /* Port Configuration */
    #define fan_PC                 (* (reg32 *) fan__PC)
#endif
/* Pin State */
#define fan_PS                     (* (reg32 *) fan__PS)
/* Data Register */
#define fan_DR                     (* (reg32 *) fan__DR)
/* Input Buffer Disable Override */
#define fan_INP_DIS                (* (reg32 *) fan__PC2)

/* Interrupt configuration Registers */
#define fan_INTCFG                 (* (reg32 *) fan__INTCFG)
#define fan_INTSTAT                (* (reg32 *) fan__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define fan_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(fan__SIO)
    #define fan_SIO_REG            (* (reg32 *) fan__SIO)
#endif /* (fan__SIO_CFG) */

/* USBIO registers */
#if !defined(fan__PC) && (CY_PSOC4_4200L)
    #define fan_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define fan_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define fan_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define fan_DRIVE_MODE_SHIFT       (0x00u)
#define fan_DRIVE_MODE_MASK        (0x07u << fan_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins fan_H */


/* [] END OF FILE */
