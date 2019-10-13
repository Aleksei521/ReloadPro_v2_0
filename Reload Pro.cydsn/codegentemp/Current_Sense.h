/*******************************************************************************
* File Name: Current_Sense.h  
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

#if !defined(CY_PINS_Current_Sense_H) /* Pins Current_Sense_H */
#define CY_PINS_Current_Sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Current_Sense_aliases.h"


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
} Current_Sense_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Current_Sense_Read(void);
void    Current_Sense_Write(uint8 value);
uint8   Current_Sense_ReadDataReg(void);
#if defined(Current_Sense__PC) || (CY_PSOC4_4200L) 
    void    Current_Sense_SetDriveMode(uint8 mode);
#endif
void    Current_Sense_SetInterruptMode(uint16 position, uint16 mode);
uint8   Current_Sense_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Current_Sense_Sleep(void); 
void Current_Sense_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Current_Sense__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Current_Sense_DRIVE_MODE_BITS        (3)
    #define Current_Sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Current_Sense_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Current_Sense_SetDriveMode() function.
         *  @{
         */
        #define Current_Sense_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Current_Sense_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Current_Sense_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Current_Sense_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Current_Sense_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Current_Sense_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Current_Sense_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Current_Sense_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Current_Sense_MASK               Current_Sense__MASK
#define Current_Sense_SHIFT              Current_Sense__SHIFT
#define Current_Sense_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Current_Sense_SetInterruptMode() function.
     *  @{
     */
        #define Current_Sense_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Current_Sense_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Current_Sense_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Current_Sense_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Current_Sense__SIO)
    #define Current_Sense_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Current_Sense__PC) && (CY_PSOC4_4200L)
    #define Current_Sense_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Current_Sense_USBIO_DISABLE              ((uint32)(~Current_Sense_USBIO_ENABLE))
    #define Current_Sense_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Current_Sense_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Current_Sense_USBIO_ENTER_SLEEP          ((uint32)((1u << Current_Sense_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Current_Sense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Current_Sense_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Current_Sense_USBIO_SUSPEND_SHIFT)))
    #define Current_Sense_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Current_Sense_USBIO_SUSPEND_DEL_SHIFT)))
    #define Current_Sense_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Current_Sense__PC)
    /* Port Configuration */
    #define Current_Sense_PC                 (* (reg32 *) Current_Sense__PC)
#endif
/* Pin State */
#define Current_Sense_PS                     (* (reg32 *) Current_Sense__PS)
/* Data Register */
#define Current_Sense_DR                     (* (reg32 *) Current_Sense__DR)
/* Input Buffer Disable Override */
#define Current_Sense_INP_DIS                (* (reg32 *) Current_Sense__PC2)

/* Interrupt configuration Registers */
#define Current_Sense_INTCFG                 (* (reg32 *) Current_Sense__INTCFG)
#define Current_Sense_INTSTAT                (* (reg32 *) Current_Sense__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Current_Sense_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Current_Sense__SIO)
    #define Current_Sense_SIO_REG            (* (reg32 *) Current_Sense__SIO)
#endif /* (Current_Sense__SIO_CFG) */

/* USBIO registers */
#if !defined(Current_Sense__PC) && (CY_PSOC4_4200L)
    #define Current_Sense_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Current_Sense_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Current_Sense_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Current_Sense_DRIVE_MODE_SHIFT       (0x00u)
#define Current_Sense_DRIVE_MODE_MASK        (0x07u << Current_Sense_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Current_Sense_H */


/* [] END OF FILE */
