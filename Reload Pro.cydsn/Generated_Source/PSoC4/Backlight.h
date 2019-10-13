/*******************************************************************************
* File Name: Backlight.h  
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

#if !defined(CY_PINS_Backlight_H) /* Pins Backlight_H */
#define CY_PINS_Backlight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Backlight_aliases.h"


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
} Backlight_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Backlight_Read(void);
void    Backlight_Write(uint8 value);
uint8   Backlight_ReadDataReg(void);
#if defined(Backlight__PC) || (CY_PSOC4_4200L) 
    void    Backlight_SetDriveMode(uint8 mode);
#endif
void    Backlight_SetInterruptMode(uint16 position, uint16 mode);
uint8   Backlight_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Backlight_Sleep(void); 
void Backlight_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Backlight__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Backlight_DRIVE_MODE_BITS        (3)
    #define Backlight_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Backlight_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Backlight_SetDriveMode() function.
         *  @{
         */
        #define Backlight_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Backlight_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Backlight_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Backlight_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Backlight_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Backlight_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Backlight_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Backlight_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Backlight_MASK               Backlight__MASK
#define Backlight_SHIFT              Backlight__SHIFT
#define Backlight_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Backlight_SetInterruptMode() function.
     *  @{
     */
        #define Backlight_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Backlight_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Backlight_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Backlight_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Backlight__SIO)
    #define Backlight_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Backlight__PC) && (CY_PSOC4_4200L)
    #define Backlight_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Backlight_USBIO_DISABLE              ((uint32)(~Backlight_USBIO_ENABLE))
    #define Backlight_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Backlight_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Backlight_USBIO_ENTER_SLEEP          ((uint32)((1u << Backlight_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Backlight_USBIO_SUSPEND_DEL_SHIFT)))
    #define Backlight_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Backlight_USBIO_SUSPEND_SHIFT)))
    #define Backlight_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Backlight_USBIO_SUSPEND_DEL_SHIFT)))
    #define Backlight_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Backlight__PC)
    /* Port Configuration */
    #define Backlight_PC                 (* (reg32 *) Backlight__PC)
#endif
/* Pin State */
#define Backlight_PS                     (* (reg32 *) Backlight__PS)
/* Data Register */
#define Backlight_DR                     (* (reg32 *) Backlight__DR)
/* Input Buffer Disable Override */
#define Backlight_INP_DIS                (* (reg32 *) Backlight__PC2)

/* Interrupt configuration Registers */
#define Backlight_INTCFG                 (* (reg32 *) Backlight__INTCFG)
#define Backlight_INTSTAT                (* (reg32 *) Backlight__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Backlight_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Backlight__SIO)
    #define Backlight_SIO_REG            (* (reg32 *) Backlight__SIO)
#endif /* (Backlight__SIO_CFG) */

/* USBIO registers */
#if !defined(Backlight__PC) && (CY_PSOC4_4200L)
    #define Backlight_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Backlight_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Backlight_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Backlight_DRIVE_MODE_SHIFT       (0x00u)
#define Backlight_DRIVE_MODE_MASK        (0x07u << Backlight_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Backlight_H */


/* [] END OF FILE */
