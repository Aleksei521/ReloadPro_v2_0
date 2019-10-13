/*******************************************************************************
* File Name: disp_mosi.h  
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

#if !defined(CY_PINS_disp_mosi_H) /* Pins disp_mosi_H */
#define CY_PINS_disp_mosi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "disp_mosi_aliases.h"


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
} disp_mosi_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   disp_mosi_Read(void);
void    disp_mosi_Write(uint8 value);
uint8   disp_mosi_ReadDataReg(void);
#if defined(disp_mosi__PC) || (CY_PSOC4_4200L) 
    void    disp_mosi_SetDriveMode(uint8 mode);
#endif
void    disp_mosi_SetInterruptMode(uint16 position, uint16 mode);
uint8   disp_mosi_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void disp_mosi_Sleep(void); 
void disp_mosi_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(disp_mosi__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define disp_mosi_DRIVE_MODE_BITS        (3)
    #define disp_mosi_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - disp_mosi_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the disp_mosi_SetDriveMode() function.
         *  @{
         */
        #define disp_mosi_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define disp_mosi_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define disp_mosi_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define disp_mosi_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define disp_mosi_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define disp_mosi_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define disp_mosi_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define disp_mosi_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define disp_mosi_MASK               disp_mosi__MASK
#define disp_mosi_SHIFT              disp_mosi__SHIFT
#define disp_mosi_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in disp_mosi_SetInterruptMode() function.
     *  @{
     */
        #define disp_mosi_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define disp_mosi_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define disp_mosi_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define disp_mosi_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(disp_mosi__SIO)
    #define disp_mosi_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(disp_mosi__PC) && (CY_PSOC4_4200L)
    #define disp_mosi_USBIO_ENABLE               ((uint32)0x80000000u)
    #define disp_mosi_USBIO_DISABLE              ((uint32)(~disp_mosi_USBIO_ENABLE))
    #define disp_mosi_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define disp_mosi_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define disp_mosi_USBIO_ENTER_SLEEP          ((uint32)((1u << disp_mosi_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << disp_mosi_USBIO_SUSPEND_DEL_SHIFT)))
    #define disp_mosi_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << disp_mosi_USBIO_SUSPEND_SHIFT)))
    #define disp_mosi_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << disp_mosi_USBIO_SUSPEND_DEL_SHIFT)))
    #define disp_mosi_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(disp_mosi__PC)
    /* Port Configuration */
    #define disp_mosi_PC                 (* (reg32 *) disp_mosi__PC)
#endif
/* Pin State */
#define disp_mosi_PS                     (* (reg32 *) disp_mosi__PS)
/* Data Register */
#define disp_mosi_DR                     (* (reg32 *) disp_mosi__DR)
/* Input Buffer Disable Override */
#define disp_mosi_INP_DIS                (* (reg32 *) disp_mosi__PC2)

/* Interrupt configuration Registers */
#define disp_mosi_INTCFG                 (* (reg32 *) disp_mosi__INTCFG)
#define disp_mosi_INTSTAT                (* (reg32 *) disp_mosi__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define disp_mosi_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(disp_mosi__SIO)
    #define disp_mosi_SIO_REG            (* (reg32 *) disp_mosi__SIO)
#endif /* (disp_mosi__SIO_CFG) */

/* USBIO registers */
#if !defined(disp_mosi__PC) && (CY_PSOC4_4200L)
    #define disp_mosi_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define disp_mosi_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define disp_mosi_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define disp_mosi_DRIVE_MODE_SHIFT       (0x00u)
#define disp_mosi_DRIVE_MODE_MASK        (0x07u << disp_mosi_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins disp_mosi_H */


/* [] END OF FILE */