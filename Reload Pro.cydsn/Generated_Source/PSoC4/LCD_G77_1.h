/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <CyLib.h>

void LCD_G77_1_Start();
void LCD_G77_1_Setup();
void LCD_G77_1_SetCursorPosition(uint8 page, uint8 col);
void LCD_G77_1_SetContrast(uint8 contrast_level);
void LCD_G77_1_DrawText(uint8 start_page, uint8 start_col, const char *text, uint8 inverse);
void LCD_G77_1_DrawBigNumbers(uint8 start_page, uint8 start_col, const char *nums);
void LCD_G77_1_ClearAll();
void LCD_G77_1_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col, uint8 value);
/* [] END OF FILE */
