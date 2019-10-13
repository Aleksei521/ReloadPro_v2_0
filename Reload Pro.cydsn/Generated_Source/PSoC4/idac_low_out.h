/*******************************************************************************
* File Name: idac_low_out.h  
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

#if !defined(CY_PINS_idac_low_out_H) /* Pins idac_low_out_H */
#define CY_PINS_idac_low_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "idac_low_out_aliases.h"


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
} idac_low_out_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   idac_low_out_Read(void);
void    idac_low_out_Write(uint8 value);
uint8   idac_low_out_ReadDataReg(void);
#if defined(idac_low_out__PC) || (CY_PSOC4_4200L) 
    void    idac_low_out_SetDriveMode(uint8 mode);
#endif
void    idac_low_out_SetInterruptMode(uint16 position, uint16 mode);
uint8   idac_low_out_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void idac_low_out_Sleep(void); 
void idac_low_out_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(idac_low_out__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define idac_low_out_DRIVE_MODE_BITS        (3)
    #define idac_low_out_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - idac_low_out_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the idac_low_out_SetDriveMode() function.
         *  @{
         */
        #define idac_low_out_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define idac_low_out_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define idac_low_out_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define idac_low_out_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define idac_low_out_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define idac_low_out_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define idac_low_out_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define idac_low_out_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define idac_low_out_MASK               idac_low_out__MASK
#define idac_low_out_SHIFT              idac_low_out__SHIFT
#define idac_low_out_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in idac_low_out_SetInterruptMode() function.
     *  @{
     */
        #define idac_low_out_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define idac_low_out_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define idac_low_out_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define idac_low_out_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(idac_low_out__SIO)
    #define idac_low_out_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(idac_low_out__PC) && (CY_PSOC4_4200L)
    #define idac_low_out_USBIO_ENABLE               ((uint32)0x80000000u)
    #define idac_low_out_USBIO_DISABLE              ((uint32)(~idac_low_out_USBIO_ENABLE))
    #define idac_low_out_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define idac_low_out_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define idac_low_out_USBIO_ENTER_SLEEP          ((uint32)((1u << idac_low_out_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << idac_low_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define idac_low_out_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << idac_low_out_USBIO_SUSPEND_SHIFT)))
    #define idac_low_out_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << idac_low_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define idac_low_out_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(idac_low_out__PC)
    /* Port Configuration */
    #define idac_low_out_PC                 (* (reg32 *) idac_low_out__PC)
#endif
/* Pin State */
#define idac_low_out_PS                     (* (reg32 *) idac_low_out__PS)
/* Data Register */
#define idac_low_out_DR                     (* (reg32 *) idac_low_out__DR)
/* Input Buffer Disable Override */
#define idac_low_out_INP_DIS                (* (reg32 *) idac_low_out__PC2)

/* Interrupt configuration Registers */
#define idac_low_out_INTCFG                 (* (reg32 *) idac_low_out__INTCFG)
#define idac_low_out_INTSTAT                (* (reg32 *) idac_low_out__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define idac_low_out_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(idac_low_out__SIO)
    #define idac_low_out_SIO_REG            (* (reg32 *) idac_low_out__SIO)
#endif /* (idac_low_out__SIO_CFG) */

/* USBIO registers */
#if !defined(idac_low_out__PC) && (CY_PSOC4_4200L)
    #define idac_low_out_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define idac_low_out_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define idac_low_out_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define idac_low_out_DRIVE_MODE_SHIFT       (0x00u)
#define idac_low_out_DRIVE_MODE_MASK        (0x07u << idac_low_out_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins idac_low_out_H */


/* [] END OF FILE */
