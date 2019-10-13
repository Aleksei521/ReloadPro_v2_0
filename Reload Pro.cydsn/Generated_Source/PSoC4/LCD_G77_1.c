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
#include "LCD_G77_1.h"
#include "LCD_G77_1_font.h"
#include "LCD_G77_1_I2C.h"
#include <stdbool.h>
#include <CyLib.h>

#define CMD_WRITE_DATA_UNO  	0xC0
#define CMD_WRITE_DATA_MULTI  	0x40
#define CMD_WRITE_CMD_UNO     	0x80
#define CMD_WRITE_CMD_MULTI  	0x00
#define CMD_GOTO_DEFPAGE		0x01//PAGE 7
//COMMAND PAGE 7
#define CMD_GOTO_PAGE		    0x08
#define CMD_DISPLAY_OFF			0x14
#define CMD_DISPLAY_ON_HADR		0x10
#define CMD_DISPLAY_ON_VADR		0x12
#define CMD_SET_RAMPAGE0		0x20
#define CMD_SET_RAMPAGE1		0x24
#define CMD_SET_Y_ADR    		0x40
#define CMD_SET_X_ADR    		0x80
//COMMAND PAGE 6
#define CMD_DISPLAY_CTRL        0x04
#define DISP_BLANK      0x0
#define DISP_NORMAL     0x1
#define DISP_ALL_SEG_ON 0x2
#define DISP_INVERSE    0x3
#define CMD_SET_MIRROR_XY       0x08
#define SET_MIRROR_X    0x04
#define SET_MIRROR_Y    0x02
#define CMD_SET_BIAS            0x10
#define BIAS_1_11       0x0
#define BIAS_1_10       0x1
#define BIAS_1_9        0x2
#define BIAS_1_8        0x3
#define BIAS_1_7        0x4
#define BIAS_1_6        0x5
#define BIAS_1_5        0x6
#define BIAS_1_4        0x7
#define CMD_SET_LARGE_DISPLAY   0x24
#define CMD_SET_NORMAL_DISPLAY  0x20
#define CMD_SET_MUX_RATE        0x80
#define RATE_1_17       0x0
#define RATE_1_26       0x1
#define RATE_1_34       0x2
#define RATE_1_49       0x3
#define RATE_1_65       0x4
//COMMAND PAGE 5
#define CMD_HV_CONTROL          0x04
#define HV_ENABLE       0x1
#define HV_RANGE_HIGH   0x2
#define CMD_HV_MULTIPLAYER      0x08
#define HV_MUL_2        0x0
#define HV_MUL_3        0x1
#define HV_MUL_4        0x2
#define HV_MUL_5        0x3
#define CMD_SET_TC              0x10
#define TC_0            0x0
#define TC_0_44         0x1
#define TC_1_10         0x2
#define TC_1_45         0x3
#define TC_1_91         0x4
#define TC_2_15         0x5
#define TC_2_32         0x6
#define TC_2_74         0x7
#define CMD_SET_VLCD            0x80
//COMMAND PAGE 3
#define CMD_STATE_CTRL          0x04
#define DISP_OFF        0x2
#define VDD_AS_VLCD     0x1
#define CMD_SET_OSC             0x08
#define EXTERNAL_OSC    0x2
#define CMD_COG                 0x40
#define SET_BRS         0x08
#define SET_TRS         0x10

#define DEFAULT_CONTRAST_LEVEL		0xE4
#define LCD_G77_1SLAVE_ADR 0x78

const unsigned char ini_array[]={
    CMD_WRITE_CMD_MULTI,
    CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    CMD_DISPLAY_ON_HADR,   //бит2 - PD, 0-контроллер включен, 1- выключен
    CMD_GOTO_PAGE|6,    //Переключаемся на страницу "110"
    CMD_SET_BIAS|BIAS_1_9,   //Set Bias, Младшие три бита устанавливают bias, "010" - bias "1/9"
    CMD_SET_LARGE_DISPLAY,   //Бит2 - IB, IB-0-low current for small LCD, IB-1-high current
    CMD_DISPLAY_CTRL|DISP_NORMAL,      //Display mode. Бит0-E,Бит1-D,Бит2-всегда=1
    CMD_SET_MUX_RATE|RATE_1_65,   //SET multiplex rate- младшие три бита, "100" - 1/65
    CMD_SET_MIRROR_XY,    //Бит1-MY, БИТ2 -MX, 0 - нет отражения, 1- отражение
    CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    CMD_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    CMD_HV_MULTIPLAYER|HV_MUL_2,      //Выбираем режим умножения, младшие два бита 00- *2Vdd
    CMD_SET_TC|TC_2_74,   //Устанавливаем температурный коэффицент - 7, младшие три бита
    CMD_SET_VLCD|0x64,   //Устанавливаем Vlcd - младшие 7 бит
    CMD_HV_CONTROL|HV_ENABLE,      //бит1-PRS, 0-нижний диапазон,1-верхний, 
            //бит0-HVE 0-высоковольтный генератор выключен,1-включён
    COMMAND_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    COMMAND_GOTO_PAGE|3,    //Переключаемся на страницу "011"
    CMD_COG,   //Бит4-TRS, бит3-BRS, 0-swap выключен,1-включён
    CMD_SET_OSC,      //Бит1-EC, 1- Внутренний генератор выключен, 0-включён
    CMD_STATE_CTRL,      //Бит1-DOF, 1-all blocks - off,0-on,бит0-DM, если HVE-1, не имеет значения
    COMMAND_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    COMMAND_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    CMD_HV_MULTIPLAYER|HV_MUL_3,      //Выбираем режим умножения, младшие два бита 00- *3Vdd
    COMMAND_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    COMMAND_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    CMD_HV_MULTIPLAYER|HV_MUL_4,    //Выбираем режим умножения, младшие два бита 00- *4Vdd
    COMMAND_GOTO_DEFPAGE       //Переключаемся на страницу "111"
    };

//#define VLCD_norm   0xE4
//#define VLCD_max   0xFF
//#define VLCD_min   0xD7


static void send_commands(uint8 commands[], int len) {

    (void) LCD_G77_1_I2C_I2CMasterClearStatus();
    
    /* Start I2C write and check status*/
    if(LCD_G77_1_I2C_I2C_MSTR_NO_ERROR == LCD_G77_1_I2C_I2CMasterWriteBuf(LCD_G77_1SLAVE_ADR,
                                    commands, len,
                                    LCD_G77_1_I2C_I2C_MODE_COMPLETE_XFER))
    {
        /*If I2C write started without errors, 
        / wait until I2C Master completes write transfer 
        */
        while (0u == (LCD_G77_1_I2C_I2CMasterStatus() & LCD_G77_1_I2C_I2C_MSTAT_WR_CMPLT))
        {
            /* Wait */
        }
}

static void configure_grays() {
	send_commands((uint8[]) {
		COMMAND_SET_MODE, MODE_EXT,
	}, 2);
	for(int i = 0; i < 64; i += 4) {
		uint8 gray = (i * 0x2D) / 60;
		send_commands((uint8[]) {
			COMMAND_EXT_SET_GRAY_LEVEL | i,
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 1),
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 2),
			gray,
			COMMAND_EXT_SET_GRAY_LEVEL | (i + 3),
			gray
		}, 8);
	}
	send_commands((uint8[]) {
		COMMAND_SET_MODE, MODE_NORMAL
	}, 2);
}


void LCD_G77_1_Setup() {
	send_commands((uint8[])inin_array,sizeof(ini_array));
	LCD_G77_1_SetContrast(DEFAULT_CONTRAST_LEVEL);
}

void LCD_G77_1_Start() {
	LCD_G77_1_I2C_Start();
	LCD_G77_1_Setup();
}

void LCD_G77_1_SetCursorPosition(uint8 page, uint8 col) {
	send_commands((uint8[]) {
        CMD_WRITE_CMD_MULTI,
        CMD_GOTO_DEFPAGE,
		CMD_SET_Y_ADR | (page & 0xF),
		CMD_SET_X_ADR | (col & 0x7F)
	}, 4);
}

void LCD_G77_1_SetContrast(uint8 contrast_level) {
	send_commands((uint8[]) {
        CMD_WRITE_CMD_MULTI,
        CMD_GOTO_DEFPAGE,
        CMD_GOTO_PAGE|5,
		CMD_SET_VLCD| (contrast_level & 0x7F)}, 4);
}

stat//ic void draw_text_slice(char c, uint8 row, uint8 inverse) {
	write_pixels_begin(FONT_GLYPH_COLUMNS * 4);
	for(int8 i = 0; i < FONT_GLYPH_COLUMNS; i++) {
		char col = glyphs[c - FONT_GLYPH_OFFSET][row][i];
		if(inverse)
			col = ~col;
		uint8 pixels[4] = {col, col, col, col};
		//LCD_G77_1_SPI_PutArray(pixels, 4);
	}
}

void LCD_G77_1_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col, uint8 value) {
	for(uint8 row = start_row; row < end_row; row++) {
		LCD_G77_1_SetCursorPosition(row, start_col);
		for(uint8 col = start_col; col < end_col; col++) {
			//LCD_G77_1_WritePixels((uint8[]){value, value, value, value}, 4);
		}
	}
}

void LCD_G77_1_ClearAll() {
	//LCD_G77_1_Clear(0, 0, 8, 160, 0);
}

void LCD_G77_1_DrawText(uint8 start_page, uint8 start_col, const char *text, uint8 inverse) {
	for(uint8 row = 0; row < 2; row++) {
		LCD_G77_1_SetCursorPosition(start_page + row, start_col);
		for(const char *c = text; *c != '\0'; c++) {
			//draw_text_slice(*c, row, inverse);
		}
	}
}

void LCD_G77_1_DrawBigNumbers(uint8 start_page, uint8 start_col, const char *nums) {
	// Big numbers are 3 glyphs tall
	for(uint8 vglyph = 0; vglyph < 3; vglyph++) {
		for(uint8 row = 0; row < 2; row++) {
			LCD_G77_1_SetCursorPosition(start_page + vglyph * 2 + row, start_col);
			// Big numbers are 3 glyphs wide
			for(const char *c = nums; *c != '\0'; c++) {
				for(uint8 hglyph = 0; hglyph < 3; hglyph++) {
					if(*c >= '0' && *c <= '9') {
						// Determine glyph based on provided number, which glyph we're drawing vertically,
						// and which glyph we're drawing horizontally
						uint8 glyphnum = FONT_BIGDIGIT_OFFSET
										 + (*c - '0') * 3
										 + FONT_BIGDIGIT_ROW_WIDTH * vglyph
										 + hglyph;
						//draw_text_slice(glyphnum, row, 0);
					} else  {
						hglyph = 2; // Other glyphs are only 1 glyph wide
						if(vglyph == 2) {
							draw_text_slice((*c == '.')?GLYPH_CHAR(FONT_GLYPH_BIGPERIOD):*c, row, 0);
						} else if(*c == '.') {
							//draw_text_slice(' ', row, 0);
						}
					}
				}
			}
		}
	}
}

/* [] END OF FILE */
