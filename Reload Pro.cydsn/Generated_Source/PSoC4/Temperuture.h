/*******************************************************************************
* File Name: Temperuture.h  
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

#if !defined(CY_PINS_Temperuture_H) /* Pins Temperuture_H */
#define CY_PINS_Temperuture_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Temperuture_aliases.h"


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
} Temperuture_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Temperuture_Read(void);
void    Temperuture_Write(uint8 value);
uint8   Temperuture_ReadDataReg(void);
#if defined(Temperuture__PC) || (CY_PSOC4_4200L) 
    void    Temperuture_SetDriveMode(uint8 mode);
#endif
void    Temperuture_SetInterruptMode(uint16 position, uint16 mode);
uint8   Temperuture_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Temperuture_Sleep(void); 
void Temperuture_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Temperuture__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Temperuture_DRIVE_MODE_BITS        (3)
    #define Temperuture_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Temperuture_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Temperuture_SetDriveMode() function.
         *  @{
         */
        #define Temperuture_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Temperuture_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Temperuture_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Temperuture_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Temperuture_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Temperuture_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Temperuture_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Temperuture_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Temperuture_MASK               Temperuture__MASK
#define Temperuture_SHIFT              Temperuture__SHIFT
#define Temperuture_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Temperuture_SetInterruptMode() function.
     *  @{
     */
        #define Temperuture_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Temperuture_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Temperuture_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Temperuture_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Temperuture__SIO)
    #define Temperuture_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Temperuture__PC) && (CY_PSOC4_4200L)
    #define Temperuture_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Temperuture_USBIO_DISABLE              ((uint32)(~Temperuture_USBIO_ENABLE))
    #define Temperuture_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Temperuture_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Temperuture_USBIO_ENTER_SLEEP          ((uint32)((1u << Temperuture_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Temperuture_USBIO_SUSPEND_DEL_SHIFT)))
    #define Temperuture_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Temperuture_USBIO_SUSPEND_SHIFT)))
    #define Temperuture_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Temperuture_USBIO_SUSPEND_DEL_SHIFT)))
    #define Temperuture_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Temperuture__PC)
    /* Port Configuration */
    #define Temperuture_PC                 (* (reg32 *) Temperuture__PC)
#endif
/* Pin State */
#define Temperuture_PS                     (* (reg32 *) Temperuture__PS)
/* Data Register */
#define Temperuture_DR                     (* (reg32 *) Temperuture__DR)
/* Input Buffer Disable Override */
#define Temperuture_INP_DIS                (* (reg32 *) Temperuture__PC2)

/* Interrupt configuration Registers */
#define Temperuture_INTCFG                 (* (reg32 *) Temperuture__INTCFG)
#define Temperuture_INTSTAT                (* (reg32 *) Temperuture__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Temperuture_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Temperuture__SIO)
    #define Temperuture_SIO_REG            (* (reg32 *) Temperuture__SIO)
#endif /* (Temperuture__SIO_CFG) */

/* USBIO registers */
#if !defined(Temperuture__PC) && (CY_PSOC4_4200L)
    #define Temperuture_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Temperuture_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Temperuture_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Temperuture_DRIVE_MODE_SHIFT       (0x00u)
#define Temperuture_DRIVE_MODE_MASK        (0x07u << Temperuture_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Temperuture_H */


/* [] END OF FILE */
