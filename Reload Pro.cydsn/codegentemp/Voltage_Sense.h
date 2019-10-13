/*******************************************************************************
* File Name: Voltage_Sense.h  
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

#if !defined(CY_PINS_Voltage_Sense_H) /* Pins Voltage_Sense_H */
#define CY_PINS_Voltage_Sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Voltage_Sense_aliases.h"


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
} Voltage_Sense_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Voltage_Sense_Read(void);
void    Voltage_Sense_Write(uint8 value);
uint8   Voltage_Sense_ReadDataReg(void);
#if defined(Voltage_Sense__PC) || (CY_PSOC4_4200L) 
    void    Voltage_Sense_SetDriveMode(uint8 mode);
#endif
void    Voltage_Sense_SetInterruptMode(uint16 position, uint16 mode);
uint8   Voltage_Sense_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Voltage_Sense_Sleep(void); 
void Voltage_Sense_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Voltage_Sense__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Voltage_Sense_DRIVE_MODE_BITS        (3)
    #define Voltage_Sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Voltage_Sense_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Voltage_Sense_SetDriveMode() function.
         *  @{
         */
        #define Voltage_Sense_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Voltage_Sense_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Voltage_Sense_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Voltage_Sense_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Voltage_Sense_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Voltage_Sense_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Voltage_Sense_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Voltage_Sense_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Voltage_Sense_MASK               Voltage_Sense__MASK
#define Voltage_Sense_SHIFT              Voltage_Sense__SHIFT
#define Voltage_Sense_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Voltage_Sense_SetInterruptMode() function.
     *  @{
     */
        #define Voltage_Sense_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Voltage_Sense_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Voltage_Sense_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Voltage_Sense_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Voltage_Sense__SIO)
    #define Voltage_Sense_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Voltage_Sense__PC) && (CY_PSOC4_4200L)
    #define Voltage_Sense_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Voltage_Sense_USBIO_DISABLE              ((uint32)(~Voltage_Sense_USBIO_ENABLE))
    #define Voltage_Sense_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Voltage_Sense_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Voltage_Sense_USBIO_ENTER_SLEEP          ((uint32)((1u << Voltage_Sense_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Voltage_Sense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Voltage_Sense_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Voltage_Sense_USBIO_SUSPEND_SHIFT)))
    #define Voltage_Sense_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Voltage_Sense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Voltage_Sense_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Voltage_Sense__PC)
    /* Port Configuration */
    #define Voltage_Sense_PC                 (* (reg32 *) Voltage_Sense__PC)
#endif
/* Pin State */
#define Voltage_Sense_PS                     (* (reg32 *) Voltage_Sense__PS)
/* Data Register */
#define Voltage_Sense_DR                     (* (reg32 *) Voltage_Sense__DR)
/* Input Buffer Disable Override */
#define Voltage_Sense_INP_DIS                (* (reg32 *) Voltage_Sense__PC2)

/* Interrupt configuration Registers */
#define Voltage_Sense_INTCFG                 (* (reg32 *) Voltage_Sense__INTCFG)
#define Voltage_Sense_INTSTAT                (* (reg32 *) Voltage_Sense__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Voltage_Sense_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Voltage_Sense__SIO)
    #define Voltage_Sense_SIO_REG            (* (reg32 *) Voltage_Sense__SIO)
#endif /* (Voltage_Sense__SIO_CFG) */

/* USBIO registers */
#if !defined(Voltage_Sense__PC) && (CY_PSOC4_4200L)
    #define Voltage_Sense_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Voltage_Sense_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Voltage_Sense_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Voltage_Sense_DRIVE_MODE_SHIFT       (0x00u)
#define Voltage_Sense_DRIVE_MODE_MASK        (0x07u << Voltage_Sense_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Voltage_Sense_H */


/* [] END OF FILE */
