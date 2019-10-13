/*******************************************************************************
* File Name: IDAC_High.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the IDAC_P4
*  component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC_IDAC_High_H)
#define CY_IDAC_IDAC_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Internal Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} IDAC_High_BACKUP_STRUCT;


extern uint32 IDAC_High_initVar;

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* IDAC polarity setting constants */
#define IDAC_High__SOURCE 0
#define IDAC_High__SINK 1


/* IDAC range setting constants */
#define IDAC_High__LOWRANGE 0
#define IDAC_High__HIGHRANGE 1


/* IDAC polarity setting definitions */
#define IDAC_High_MODE_SOURCE    (IDAC_High__SOURCE)
#define IDAC_High_MODE_SINK      (IDAC_High__SINK)

/* IDAC RANGE setting definitions */
#define IDAC_High_MODE_LOWRANGE  (IDAC_High__LOWRANGE)
#define IDAC_High_MODE_HIGHRANGE (IDAC_High__HIGHRANGE)

/***************************************
*   Conditional Compilation Parameters
****************************************/

#define IDAC_High_IDAC_RESOLUTION    (8u)
#define IDAC_High_IDAC_RANGE         (0u)
#define IDAC_High_IDAC_POLARITY      (0u)


/***************************************
*    Initial Parameter Constants
***************************************/
#define IDAC_High_IDAC_INIT_VALUE    (120u)




/***************************************
*        Function Prototypes
***************************************/

void IDAC_High_Init(void);
void IDAC_High_Enable(void);
void IDAC_High_Start(void);
void IDAC_High_Stop(void);
void IDAC_High_SetValue(uint32  value);
void IDAC_High_SaveConfig(void);
void IDAC_High_Sleep(void);
void IDAC_High_RestoreConfig(void);
void IDAC_High_Wakeup(void);


/***************************************
*            API Constants
***************************************/

#define IDAC_High_IDAC_EN_MODE           (3u)
#define IDAC_High_IDAC_CSD_EN            (1u)
#define IDAC_High_IDAC_CSD_EN_POSITION   (31u)

#define IDAC_High_IDAC_VALUE_POSITION    (IDAC_High_cy_psoc4_idac__CSD_IDAC_SHIFT)

#define IDAC_High_IDAC_MODE_SHIFT        (8u)
#define IDAC_High_IDAC_MODE_POSITION     ((uint32)IDAC_High_cy_psoc4_idac__CSD_IDAC_SHIFT +\
                                                 IDAC_High_IDAC_MODE_SHIFT)

#define IDAC_High_IDAC_RANGE_SHIFT       (10u)
#define IDAC_High_IDAC_RANGE_POSITION    ((uint32)IDAC_High_cy_psoc4_idac__CSD_IDAC_SHIFT +\
                                                 IDAC_High_IDAC_RANGE_SHIFT)

#define IDAC_High_IDAC_POLARITY_POSITION ((uint32)IDAC_High_cy_psoc4_idac__POLARITY_SHIFT)

#define IDAC_High_IDAC_TRIM1_POSITION    ((uint32)IDAC_High_cy_psoc4_idac__CSD_TRIM1_SHIFT)
#define IDAC_High_IDAC_TRIM2_POSITION    ((uint32)IDAC_High_cy_psoc4_idac__CSD_TRIM2_SHIFT)

#define IDAC_High_IDAC_CDS_EN_MASK       (0x80000000u)

#if(IDAC_High_IDAC_RESOLUTION == 8u)
  #define IDAC_High_IDAC_VALUE_MASK      (0xFFu)
#else
  #define IDAC_High_IDAC_VALUE_MASK      (0x7Fu)
#endif /* (IDAC_High_IDAC_RESOLUTION == 8u) */

#define IDAC_High_IDAC_MODE_MASK         (3u)
#define IDAC_High_IDAC_RANGE_MASK        (1u)
#define IDAC_High_IDAC_POLARITY_MASK     (1u)

#define IDAC_High_CSD_IDAC_TRIM1_MASK    (0x0000000FuL << IDAC_High_IDAC_TRIM1_POSITION)
#define IDAC_High_CSD_IDAC_TRIM2_MASK    (0x0000000FuL << IDAC_High_IDAC_TRIM2_POSITION)


/***************************************
*        Registers
***************************************/

#define IDAC_High_IDAC_CONTROL_REG    (*(reg32 *)IDAC_High_cy_psoc4_idac__CSD_IDAC)
#define IDAC_High_IDAC_CONTROL_PTR    ( (reg32 *)IDAC_High_cy_psoc4_idac__CSD_IDAC)

#define IDAC_High_IDAC_POLARITY_CONTROL_REG    (*(reg32 *)IDAC_High_cy_psoc4_idac__CONTROL)
#define IDAC_High_IDAC_POLARITY_CONTROL_PTR    ( (reg32 *)IDAC_High_cy_psoc4_idac__CONTROL)

#define IDAC_High_CSD_TRIM1_REG       (*(reg32 *)IDAC_High_cy_psoc4_idac__CSD_TRIM1)
#define IDAC_High_CSD_TRIM1_PTR       ( (reg32 *)IDAC_High_cy_psoc4_idac__CSD_TRIM1)

#define IDAC_High_CSD_TRIM2_REG       (*(reg32 *)IDAC_High_cy_psoc4_idac__CSD_TRIM2)
#define IDAC_High_CSD_TRIM2_PTR       ( (reg32 *)IDAC_High_cy_psoc4_idac__CSD_TRIM2)

#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    #if(IDAC_High_cy_psoc4_idac__IDAC_NUMBER > 2u)
        #define IDAC_High_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD1_TRIM1_HVIDAC)
        #define IDAC_High_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD1_TRIM1_HVIDAC)
        
        #define IDAC_High_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD1_TRIM2_HVIDAC)
        #define IDAC_High_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD1_TRIM2_HVIDAC)
    #else
        #define IDAC_High_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
        #define IDAC_High_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
        
        #define IDAC_High_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
        #define IDAC_High_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
    #endif /* (IDAC_High_cy_psoc4_idac__IDAC_NUMBER > 2u) */
#else
    #define IDAC_High_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
    #define IDAC_High_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
    
    #define IDAC_High_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
    #define IDAC_High_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */

#endif /* CY_IDAC_IDAC_High_H */

/* [] END OF FILE */
