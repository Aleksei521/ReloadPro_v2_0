/*******************************************************************************
* File Name: Display_I2C_sda.h  
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

#if !defined(CY_PINS_Display_I2C_sda_H) /* Pins Display_I2C_sda_H */
#define CY_PINS_Display_I2C_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Display_I2C_sda_aliases.h"


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
} Display_I2C_sda_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Display_I2C_sda_Read(void);
void    Display_I2C_sda_Write(uint8 value);
uint8   Display_I2C_sda_ReadDataReg(void);
#if defined(Display_I2C_sda__PC) || (CY_PSOC4_4200L) 
    void    Display_I2C_sda_SetDriveMode(uint8 mode);
#endif
void    Display_I2C_sda_SetInterruptMode(uint16 position, uint16 mode);
uint8   Display_I2C_sda_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Display_I2C_sda_Sleep(void); 
void Display_I2C_sda_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Display_I2C_sda__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Display_I2C_sda_DRIVE_MODE_BITS        (3)
    #define Display_I2C_sda_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Display_I2C_sda_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Display_I2C_sda_SetDriveMode() function.
         *  @{
         */
        #define Display_I2C_sda_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Display_I2C_sda_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Display_I2C_sda_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Display_I2C_sda_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Display_I2C_sda_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Display_I2C_sda_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Display_I2C_sda_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Display_I2C_sda_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Display_I2C_sda_MASK               Display_I2C_sda__MASK
#define Display_I2C_sda_SHIFT              Display_I2C_sda__SHIFT
#define Display_I2C_sda_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Display_I2C_sda_SetInterruptMode() function.
     *  @{
     */
        #define Display_I2C_sda_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Display_I2C_sda_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Display_I2C_sda_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Display_I2C_sda_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Display_I2C_sda__SIO)
    #define Display_I2C_sda_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Display_I2C_sda__PC) && (CY_PSOC4_4200L)
    #define Display_I2C_sda_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Display_I2C_sda_USBIO_DISABLE              ((uint32)(~Display_I2C_sda_USBIO_ENABLE))
    #define Display_I2C_sda_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Display_I2C_sda_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Display_I2C_sda_USBIO_ENTER_SLEEP          ((uint32)((1u << Display_I2C_sda_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Display_I2C_sda_USBIO_SUSPEND_DEL_SHIFT)))
    #define Display_I2C_sda_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Display_I2C_sda_USBIO_SUSPEND_SHIFT)))
    #define Display_I2C_sda_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Display_I2C_sda_USBIO_SUSPEND_DEL_SHIFT)))
    #define Display_I2C_sda_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Display_I2C_sda__PC)
    /* Port Configuration */
    #define Display_I2C_sda_PC                 (* (reg32 *) Display_I2C_sda__PC)
#endif
/* Pin State */
#define Display_I2C_sda_PS                     (* (reg32 *) Display_I2C_sda__PS)
/* Data Register */
#define Display_I2C_sda_DR                     (* (reg32 *) Display_I2C_sda__DR)
/* Input Buffer Disable Override */
#define Display_I2C_sda_INP_DIS                (* (reg32 *) Display_I2C_sda__PC2)

/* Interrupt configuration Registers */
#define Display_I2C_sda_INTCFG                 (* (reg32 *) Display_I2C_sda__INTCFG)
#define Display_I2C_sda_INTSTAT                (* (reg32 *) Display_I2C_sda__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Display_I2C_sda_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Display_I2C_sda__SIO)
    #define Display_I2C_sda_SIO_REG            (* (reg32 *) Display_I2C_sda__SIO)
#endif /* (Display_I2C_sda__SIO_CFG) */

/* USBIO registers */
#if !defined(Display_I2C_sda__PC) && (CY_PSOC4_4200L)
    #define Display_I2C_sda_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Display_I2C_sda_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Display_I2C_sda_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Display_I2C_sda_DRIVE_MODE_SHIFT       (0x00u)
#define Display_I2C_sda_DRIVE_MODE_MASK        (0x07u << Display_I2C_sda_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Display_I2C_sda_H */


/* [] END OF FILE */
