/*******************************************************************************
* File Name: tach.h  
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

#if !defined(CY_PINS_tach_H) /* Pins tach_H */
#define CY_PINS_tach_H

#include "cytypes.h"
#include "cyfitter.h"
#include "tach_aliases.h"


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
} tach_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   tach_Read(void);
void    tach_Write(uint8 value);
uint8   tach_ReadDataReg(void);
#if defined(tach__PC) || (CY_PSOC4_4200L) 
    void    tach_SetDriveMode(uint8 mode);
#endif
void    tach_SetInterruptMode(uint16 position, uint16 mode);
uint8   tach_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void tach_Sleep(void); 
void tach_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(tach__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define tach_DRIVE_MODE_BITS        (3)
    #define tach_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - tach_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the tach_SetDriveMode() function.
         *  @{
         */
        #define tach_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define tach_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define tach_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define tach_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define tach_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define tach_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define tach_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define tach_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define tach_MASK               tach__MASK
#define tach_SHIFT              tach__SHIFT
#define tach_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in tach_SetInterruptMode() function.
     *  @{
     */
        #define tach_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define tach_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define tach_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define tach_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(tach__SIO)
    #define tach_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(tach__PC) && (CY_PSOC4_4200L)
    #define tach_USBIO_ENABLE               ((uint32)0x80000000u)
    #define tach_USBIO_DISABLE              ((uint32)(~tach_USBIO_ENABLE))
    #define tach_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define tach_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define tach_USBIO_ENTER_SLEEP          ((uint32)((1u << tach_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << tach_USBIO_SUSPEND_DEL_SHIFT)))
    #define tach_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << tach_USBIO_SUSPEND_SHIFT)))
    #define tach_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << tach_USBIO_SUSPEND_DEL_SHIFT)))
    #define tach_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(tach__PC)
    /* Port Configuration */
    #define tach_PC                 (* (reg32 *) tach__PC)
#endif
/* Pin State */
#define tach_PS                     (* (reg32 *) tach__PS)
/* Data Register */
#define tach_DR                     (* (reg32 *) tach__DR)
/* Input Buffer Disable Override */
#define tach_INP_DIS                (* (reg32 *) tach__PC2)

/* Interrupt configuration Registers */
#define tach_INTCFG                 (* (reg32 *) tach__INTCFG)
#define tach_INTSTAT                (* (reg32 *) tach__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define tach_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(tach__SIO)
    #define tach_SIO_REG            (* (reg32 *) tach__SIO)
#endif /* (tach__SIO_CFG) */

/* USBIO registers */
#if !defined(tach__PC) && (CY_PSOC4_4200L)
    #define tach_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define tach_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define tach_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define tach_DRIVE_MODE_SHIFT       (0x00u)
#define tach_DRIVE_MODE_MASK        (0x07u << tach_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins tach_H */


/* [] END OF FILE */
