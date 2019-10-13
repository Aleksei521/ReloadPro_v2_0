/*******************************************************************************
* File Name: Opamp_Out.h  
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

#if !defined(CY_PINS_Opamp_Out_H) /* Pins Opamp_Out_H */
#define CY_PINS_Opamp_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Opamp_Out_aliases.h"


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
} Opamp_Out_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Opamp_Out_Read(void);
void    Opamp_Out_Write(uint8 value);
uint8   Opamp_Out_ReadDataReg(void);
#if defined(Opamp_Out__PC) || (CY_PSOC4_4200L) 
    void    Opamp_Out_SetDriveMode(uint8 mode);
#endif
void    Opamp_Out_SetInterruptMode(uint16 position, uint16 mode);
uint8   Opamp_Out_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Opamp_Out_Sleep(void); 
void Opamp_Out_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Opamp_Out__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Opamp_Out_DRIVE_MODE_BITS        (3)
    #define Opamp_Out_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Opamp_Out_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Opamp_Out_SetDriveMode() function.
         *  @{
         */
        #define Opamp_Out_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Opamp_Out_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Opamp_Out_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Opamp_Out_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Opamp_Out_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Opamp_Out_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Opamp_Out_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Opamp_Out_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Opamp_Out_MASK               Opamp_Out__MASK
#define Opamp_Out_SHIFT              Opamp_Out__SHIFT
#define Opamp_Out_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Opamp_Out_SetInterruptMode() function.
     *  @{
     */
        #define Opamp_Out_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Opamp_Out_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Opamp_Out_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Opamp_Out_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Opamp_Out__SIO)
    #define Opamp_Out_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Opamp_Out__PC) && (CY_PSOC4_4200L)
    #define Opamp_Out_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Opamp_Out_USBIO_DISABLE              ((uint32)(~Opamp_Out_USBIO_ENABLE))
    #define Opamp_Out_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Opamp_Out_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Opamp_Out_USBIO_ENTER_SLEEP          ((uint32)((1u << Opamp_Out_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Opamp_Out_USBIO_SUSPEND_DEL_SHIFT)))
    #define Opamp_Out_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Opamp_Out_USBIO_SUSPEND_SHIFT)))
    #define Opamp_Out_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Opamp_Out_USBIO_SUSPEND_DEL_SHIFT)))
    #define Opamp_Out_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Opamp_Out__PC)
    /* Port Configuration */
    #define Opamp_Out_PC                 (* (reg32 *) Opamp_Out__PC)
#endif
/* Pin State */
#define Opamp_Out_PS                     (* (reg32 *) Opamp_Out__PS)
/* Data Register */
#define Opamp_Out_DR                     (* (reg32 *) Opamp_Out__DR)
/* Input Buffer Disable Override */
#define Opamp_Out_INP_DIS                (* (reg32 *) Opamp_Out__PC2)

/* Interrupt configuration Registers */
#define Opamp_Out_INTCFG                 (* (reg32 *) Opamp_Out__INTCFG)
#define Opamp_Out_INTSTAT                (* (reg32 *) Opamp_Out__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Opamp_Out_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Opamp_Out__SIO)
    #define Opamp_Out_SIO_REG            (* (reg32 *) Opamp_Out__SIO)
#endif /* (Opamp_Out__SIO_CFG) */

/* USBIO registers */
#if !defined(Opamp_Out__PC) && (CY_PSOC4_4200L)
    #define Opamp_Out_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Opamp_Out_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Opamp_Out_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Opamp_Out_DRIVE_MODE_SHIFT       (0x00u)
#define Opamp_Out_DRIVE_MODE_MASK        (0x07u << Opamp_Out_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Opamp_Out_H */


/* [] END OF FILE */
