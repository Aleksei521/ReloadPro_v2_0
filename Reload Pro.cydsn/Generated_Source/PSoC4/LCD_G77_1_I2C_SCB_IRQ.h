/*******************************************************************************
* File Name: LCD_G77_1_I2C_SCB_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_LCD_G77_1_I2C_SCB_IRQ_H)
#define CY_ISR_LCD_G77_1_I2C_SCB_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LCD_G77_1_I2C_SCB_IRQ_Start(void);
void LCD_G77_1_I2C_SCB_IRQ_StartEx(cyisraddress address);
void LCD_G77_1_I2C_SCB_IRQ_Stop(void);

CY_ISR_PROTO(LCD_G77_1_I2C_SCB_IRQ_Interrupt);

void LCD_G77_1_I2C_SCB_IRQ_SetVector(cyisraddress address);
cyisraddress LCD_G77_1_I2C_SCB_IRQ_GetVector(void);

void LCD_G77_1_I2C_SCB_IRQ_SetPriority(uint8 priority);
uint8 LCD_G77_1_I2C_SCB_IRQ_GetPriority(void);

void LCD_G77_1_I2C_SCB_IRQ_Enable(void);
uint8 LCD_G77_1_I2C_SCB_IRQ_GetState(void);
void LCD_G77_1_I2C_SCB_IRQ_Disable(void);

void LCD_G77_1_I2C_SCB_IRQ_SetPending(void);
void LCD_G77_1_I2C_SCB_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LCD_G77_1_I2C_SCB_IRQ ISR. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_VECTOR            ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_VECT)

/* Address of the LCD_G77_1_I2C_SCB_IRQ ISR priority. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_PRIOR             ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_PRIOR_REG)

/* Priority of the LCD_G77_1_I2C_SCB_IRQ interrupt. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_PRIOR_NUMBER      LCD_G77_1_I2C_SCB_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LCD_G77_1_I2C_SCB_IRQ interrupt. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_SET_EN            ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LCD_G77_1_I2C_SCB_IRQ interrupt. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_CLR_EN            ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LCD_G77_1_I2C_SCB_IRQ interrupt state to pending. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_SET_PD            ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LCD_G77_1_I2C_SCB_IRQ interrupt. */
#define LCD_G77_1_I2C_SCB_IRQ_INTC_CLR_PD            ((reg32 *) LCD_G77_1_I2C_SCB_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_LCD_G77_1_I2C_SCB_IRQ_H */


/* [] END OF FILE */
