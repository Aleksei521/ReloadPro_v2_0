/*******************************************************************************
* File Name: opamp_neg.h  
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

#if !defined(CY_PINS_opamp_neg_H) /* Pins opamp_neg_H */
#define CY_PINS_opamp_neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "opamp_neg_aliases.h"


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
} opamp_neg_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   opamp_neg_Read(void);
void    opamp_neg_Write(uint8 value);
uint8   opamp_neg_ReadDataReg(void);
#if defined(opamp_neg__PC) || (CY_PSOC4_4200L) 
    void    opamp_neg_SetDriveMode(uint8 mode);
#endif
void    opamp_neg_SetInterruptMode(uint16 position, uint16 mode);
uint8   opamp_neg_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void opamp_neg_Sleep(void); 
void opamp_neg_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(opamp_neg__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define opamp_neg_DRIVE_MODE_BITS        (3)
    #define opamp_neg_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - opamp_neg_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the opamp_neg_SetDriveMode() function.
         *  @{
         */
        #define opamp_neg_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define opamp_neg_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define opamp_neg_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define opamp_neg_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define opamp_neg_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define opamp_neg_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define opamp_neg_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define opamp_neg_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define opamp_neg_MASK               opamp_neg__MASK
#define opamp_neg_SHIFT              opamp_neg__SHIFT
#define opamp_neg_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in opamp_neg_SetInterruptMode() function.
     *  @{
     */
        #define opamp_neg_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define opamp_neg_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define opamp_neg_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define opamp_neg_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(opamp_neg__SIO)
    #define opamp_neg_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(opamp_neg__PC) && (CY_PSOC4_4200L)
    #define opamp_neg_USBIO_ENABLE               ((uint32)0x80000000u)
    #define opamp_neg_USBIO_DISABLE              ((uint32)(~opamp_neg_USBIO_ENABLE))
    #define opamp_neg_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define opamp_neg_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define opamp_neg_USBIO_ENTER_SLEEP          ((uint32)((1u << opamp_neg_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << opamp_neg_USBIO_SUSPEND_DEL_SHIFT)))
    #define opamp_neg_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << opamp_neg_USBIO_SUSPEND_SHIFT)))
    #define opamp_neg_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << opamp_neg_USBIO_SUSPEND_DEL_SHIFT)))
    #define opamp_neg_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(opamp_neg__PC)
    /* Port Configuration */
    #define opamp_neg_PC                 (* (reg32 *) opamp_neg__PC)
#endif
/* Pin State */
#define opamp_neg_PS                     (* (reg32 *) opamp_neg__PS)
/* Data Register */
#define opamp_neg_DR                     (* (reg32 *) opamp_neg__DR)
/* Input Buffer Disable Override */
#define opamp_neg_INP_DIS                (* (reg32 *) opamp_neg__PC2)

/* Interrupt configuration Registers */
#define opamp_neg_INTCFG                 (* (reg32 *) opamp_neg__INTCFG)
#define opamp_neg_INTSTAT                (* (reg32 *) opamp_neg__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define opamp_neg_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(opamp_neg__SIO)
    #define opamp_neg_SIO_REG            (* (reg32 *) opamp_neg__SIO)
#endif /* (opamp_neg__SIO_CFG) */

/* USBIO registers */
#if !defined(opamp_neg__PC) && (CY_PSOC4_4200L)
    #define opamp_neg_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define opamp_neg_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define opamp_neg_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define opamp_neg_DRIVE_MODE_SHIFT       (0x00u)
#define opamp_neg_DRIVE_MODE_MASK        (0x07u << opamp_neg_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins opamp_neg_H */


/* [] END OF FILE */
