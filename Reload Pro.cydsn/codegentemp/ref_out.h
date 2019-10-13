/*******************************************************************************
* File Name: ref_out.h  
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

#if !defined(CY_PINS_ref_out_H) /* Pins ref_out_H */
#define CY_PINS_ref_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ref_out_aliases.h"


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
} ref_out_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ref_out_Read(void);
void    ref_out_Write(uint8 value);
uint8   ref_out_ReadDataReg(void);
#if defined(ref_out__PC) || (CY_PSOC4_4200L) 
    void    ref_out_SetDriveMode(uint8 mode);
#endif
void    ref_out_SetInterruptMode(uint16 position, uint16 mode);
uint8   ref_out_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ref_out_Sleep(void); 
void ref_out_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ref_out__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ref_out_DRIVE_MODE_BITS        (3)
    #define ref_out_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ref_out_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ref_out_SetDriveMode() function.
         *  @{
         */
        #define ref_out_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ref_out_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ref_out_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ref_out_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ref_out_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ref_out_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ref_out_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ref_out_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ref_out_MASK               ref_out__MASK
#define ref_out_SHIFT              ref_out__SHIFT
#define ref_out_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ref_out_SetInterruptMode() function.
     *  @{
     */
        #define ref_out_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ref_out_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ref_out_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ref_out_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ref_out__SIO)
    #define ref_out_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ref_out__PC) && (CY_PSOC4_4200L)
    #define ref_out_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ref_out_USBIO_DISABLE              ((uint32)(~ref_out_USBIO_ENABLE))
    #define ref_out_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ref_out_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ref_out_USBIO_ENTER_SLEEP          ((uint32)((1u << ref_out_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ref_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define ref_out_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ref_out_USBIO_SUSPEND_SHIFT)))
    #define ref_out_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ref_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define ref_out_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ref_out__PC)
    /* Port Configuration */
    #define ref_out_PC                 (* (reg32 *) ref_out__PC)
#endif
/* Pin State */
#define ref_out_PS                     (* (reg32 *) ref_out__PS)
/* Data Register */
#define ref_out_DR                     (* (reg32 *) ref_out__DR)
/* Input Buffer Disable Override */
#define ref_out_INP_DIS                (* (reg32 *) ref_out__PC2)

/* Interrupt configuration Registers */
#define ref_out_INTCFG                 (* (reg32 *) ref_out__INTCFG)
#define ref_out_INTSTAT                (* (reg32 *) ref_out__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ref_out_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ref_out__SIO)
    #define ref_out_SIO_REG            (* (reg32 *) ref_out__SIO)
#endif /* (ref_out__SIO_CFG) */

/* USBIO registers */
#if !defined(ref_out__PC) && (CY_PSOC4_4200L)
    #define ref_out_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ref_out_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ref_out_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ref_out_DRIVE_MODE_SHIFT       (0x00u)
#define ref_out_DRIVE_MODE_MASK        (0x07u << ref_out_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ref_out_H */


/* [] END OF FILE */
