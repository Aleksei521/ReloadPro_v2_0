/*******************************************************************************
* File Name: Gate_Sense_Low.h  
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

#if !defined(CY_PINS_Gate_Sense_Low_H) /* Pins Gate_Sense_Low_H */
#define CY_PINS_Gate_Sense_Low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gate_Sense_Low_aliases.h"


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
} Gate_Sense_Low_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Gate_Sense_Low_Read(void);
void    Gate_Sense_Low_Write(uint8 value);
uint8   Gate_Sense_Low_ReadDataReg(void);
#if defined(Gate_Sense_Low__PC) || (CY_PSOC4_4200L) 
    void    Gate_Sense_Low_SetDriveMode(uint8 mode);
#endif
void    Gate_Sense_Low_SetInterruptMode(uint16 position, uint16 mode);
uint8   Gate_Sense_Low_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Gate_Sense_Low_Sleep(void); 
void Gate_Sense_Low_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Gate_Sense_Low__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Gate_Sense_Low_DRIVE_MODE_BITS        (3)
    #define Gate_Sense_Low_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gate_Sense_Low_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Gate_Sense_Low_SetDriveMode() function.
         *  @{
         */
        #define Gate_Sense_Low_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Gate_Sense_Low_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Gate_Sense_Low_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Gate_Sense_Low_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Gate_Sense_Low_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Gate_Sense_Low_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Gate_Sense_Low_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Gate_Sense_Low_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Gate_Sense_Low_MASK               Gate_Sense_Low__MASK
#define Gate_Sense_Low_SHIFT              Gate_Sense_Low__SHIFT
#define Gate_Sense_Low_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Gate_Sense_Low_SetInterruptMode() function.
     *  @{
     */
        #define Gate_Sense_Low_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Gate_Sense_Low_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Gate_Sense_Low_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Gate_Sense_Low_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Gate_Sense_Low__SIO)
    #define Gate_Sense_Low_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Gate_Sense_Low__PC) && (CY_PSOC4_4200L)
    #define Gate_Sense_Low_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Gate_Sense_Low_USBIO_DISABLE              ((uint32)(~Gate_Sense_Low_USBIO_ENABLE))
    #define Gate_Sense_Low_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Gate_Sense_Low_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Gate_Sense_Low_USBIO_ENTER_SLEEP          ((uint32)((1u << Gate_Sense_Low_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Gate_Sense_Low_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gate_Sense_Low_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Gate_Sense_Low_USBIO_SUSPEND_SHIFT)))
    #define Gate_Sense_Low_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Gate_Sense_Low_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gate_Sense_Low_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Gate_Sense_Low__PC)
    /* Port Configuration */
    #define Gate_Sense_Low_PC                 (* (reg32 *) Gate_Sense_Low__PC)
#endif
/* Pin State */
#define Gate_Sense_Low_PS                     (* (reg32 *) Gate_Sense_Low__PS)
/* Data Register */
#define Gate_Sense_Low_DR                     (* (reg32 *) Gate_Sense_Low__DR)
/* Input Buffer Disable Override */
#define Gate_Sense_Low_INP_DIS                (* (reg32 *) Gate_Sense_Low__PC2)

/* Interrupt configuration Registers */
#define Gate_Sense_Low_INTCFG                 (* (reg32 *) Gate_Sense_Low__INTCFG)
#define Gate_Sense_Low_INTSTAT                (* (reg32 *) Gate_Sense_Low__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Gate_Sense_Low_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Gate_Sense_Low__SIO)
    #define Gate_Sense_Low_SIO_REG            (* (reg32 *) Gate_Sense_Low__SIO)
#endif /* (Gate_Sense_Low__SIO_CFG) */

/* USBIO registers */
#if !defined(Gate_Sense_Low__PC) && (CY_PSOC4_4200L)
    #define Gate_Sense_Low_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Gate_Sense_Low_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Gate_Sense_Low_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Gate_Sense_Low_DRIVE_MODE_SHIFT       (0x00u)
#define Gate_Sense_Low_DRIVE_MODE_MASK        (0x07u << Gate_Sense_Low_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Gate_Sense_Low_H */


/* [] END OF FILE */
