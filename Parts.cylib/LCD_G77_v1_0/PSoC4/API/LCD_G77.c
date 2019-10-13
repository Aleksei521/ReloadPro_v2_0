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
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_font.h"
#include "`$INSTANCE_NAME``[I2C]`I2C.h"
#include <stdbool.h>
#include <CyLib.h>

static void write_data(uint8* data,int16 len,uint8 inverse);
static void write_cmd(uint8* data,int16 len);
static void write_fill(uint8 data,int16 len);

#define CMD_WRITE_DATA_UNO  	0xC0
#define CMD_WRITE_DATA_MULTI  	0x40
#define CMD_WRITE_CMD_UNO     	0x80
#define CMD_WRITE_CMD_MULTI  	0x00
#define CMD_GOTO_DEFPAGE		0x01//PAGE 7
//COMMAND PAGE 7
#define CMD_GOTO_PAGE		    0x08
#define CMD_FUNC_SET            0x10
#define FUNC_POWER_DOWN 0x04
#define FUNC_HADR		0x02
#define CMD_SET_RAMPAGE0		0x20
#define CMD_SET_RAMPAGE1		0x24
#define CMD_SET_Y_ADR    		0x40
#define CMD_SET_X_ADR    		0x80
//COMMAND PAGE 6
#define CMD_DISPLAY_CTRL        0x04
#define DISP_BLANK      0x0
#define DISP_ALL_SEG_ON 0x1
#define DISP_NORMAL     0x2
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
#define DM              0x1
#define CMD_SET_OSC             0x08
#define EXTERNAL_OSC    0x2
#define CMD_COG                 0x40
#define SET_BRS         0x08
#define SET_TRS         0x10

#define DEFAULT_CONTRAST_LEVEL		0x60
#define `$INSTANCE_NAME`SLAVE_ADR 0x78
#define `$INSTANCE_NAME`TIMEOUT 2
#define `$INSTANCE_NAME`MAX_PAGE 8
#define `$INSTANCE_NAME`MAX_COL 128

const uint8 ini_array[]={
    CMD_WRITE_CMD_MULTI,
    CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    CMD_FUNC_SET,   //бит2 - PD, 0-контроллер включен, 1- выключен
    CMD_SET_RAMPAGE0,
    CMD_GOTO_PAGE|3,    //Переключаемся на страницу "011"
    CMD_COG,   //Бит4-TRS, бит3-BRS, 0-swap выключен,1-включён
    CMD_SET_OSC,      //Бит1-EC, 1- Внутренний генератор выключен, 0-включён
    CMD_STATE_CTRL|DM,      //Бит1-DOF, 1-all blocks - off,0-on,бит0-DM, если HVE-1, не имеет значения
    CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    CMD_GOTO_PAGE|6,    //Переключаемся на страницу "110"
    CMD_SET_BIAS|BIAS_1_9,   //Set Bias, Младшие три бита устанавливают bias, "010" - bias "1/9"
    CMD_SET_MUX_RATE|RATE_1_65,   //SET multiplex rate- младшие три бита, "100" - 1/65
    CMD_SET_NORMAL_DISPLAY,   //Бит2 - IB, IB-0-low current for small LCD, IB-1-high current
    CMD_DISPLAY_CTRL|DISP_NORMAL,      //Display mode. Бит0-E,Бит1-D,Бит2-всегда=1
    CMD_SET_MIRROR_XY,    //Бит1-MY, БИТ2 -MX, 0 - нет отражения, 1- отражение
    CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    CMD_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    CMD_HV_MULTIPLAYER|HV_MUL_2,      //Выбираем режим умножения, младшие два бита 00- *2Vdd
    CMD_SET_TC|TC_1_10,   //Устанавливаем температурный коэффицент - 7, младшие три бита
    CMD_SET_VLCD|0x60,   //Устанавливаем Vlcd - младшие 7 бит
    CMD_HV_CONTROL|HV_ENABLE,      //бит1-PRS, 0-нижний диапазон,1-верхний, 
            //бит0-HVE 0-высоковольтный генератор выключен,1-включён
    //CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    //CMD_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    //CMD_HV_MULTIPLAYER|HV_MUL_3,      //Выбираем режим умножения, младшие два бита 00- *3Vdd
    //CMD_GOTO_DEFPAGE,      //Переключаемся на страницу "111"
    //CMD_GOTO_PAGE|5,    //Переключаемся на страницу "101"
    //CMD_HV_MULTIPLAYER|HV_MUL_4,    //Выбираем режим умножения, младшие два бита 00- *4Vdd
    CMD_GOTO_DEFPAGE       //Переключаемся на страницу "111"
    };

//#define VLCD_norm   0xE4
//#define VLCD_max   0xFF
//#define VLCD_min   0xD7

enum e_i2c_state{START,DATA,STOP};
enum e_i2c_mode{WRITE_DATA,WRITE_CMD,FILL};
struct
{
    volatile uint8  inverse;
    volatile uint8* ptr_data;
    volatile int16 len_data;
    volatile uint8 cmd[5];
    volatile uint8 fill;
    enum e_i2c_state volatile i2c_state;
    enum e_i2c_mode volatile i2c_mode;
    } `$INSTANCE_NAME`isr_struct;

CY_ISR_PROTO(`$INSTANCE_NAME``[I2C]`I2C_ISR);
CY_ISR(`$INSTANCE_NAME``[I2C]`I2C_ISR) 
{
    uint32 isr_status;
    isr_status=`$INSTANCE_NAME``[I2C]`GetMasterInterruptSource();
    if(`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_ACK&isr_status)
    {
        switch(`$INSTANCE_NAME`isr_struct.i2c_mode)
        {
            case FILL:
            case WRITE_DATA:
                switch(`$INSTANCE_NAME`isr_struct.i2c_state)
                {
                    case START:
                        `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG =`$INSTANCE_NAME`isr_struct.cmd[0];
                        `$INSTANCE_NAME`isr_struct.i2c_state=DATA;
                        break;
                    case DATA:
                        if(`$INSTANCE_NAME`isr_struct.len_data>0)
                        {   
                            if(`$INSTANCE_NAME`isr_struct.i2c_mode==WRITE_DATA)
                            {
                                if(`$INSTANCE_NAME`isr_struct.inverse) `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = ~(*`$INSTANCE_NAME`isr_struct.ptr_data);
                                else `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = *`$INSTANCE_NAME`isr_struct.ptr_data;
                                `$INSTANCE_NAME`isr_struct.ptr_data++;
                            }
                            else
                            {
                                `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = `$INSTANCE_NAME`isr_struct.fill;
                            }
                            `$INSTANCE_NAME`isr_struct.len_data--;
                        }
                        else `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_STOP;
                        break;
                    case STOP: break;
                }
                break;
            case WRITE_CMD:
                switch(`$INSTANCE_NAME`isr_struct.i2c_state)
                {
                    case START:
                    case DATA:
                        if(`$INSTANCE_NAME`isr_struct.len_data>0)
                        {
                            `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = *`$INSTANCE_NAME`isr_struct.ptr_data;
                            `$INSTANCE_NAME`isr_struct.ptr_data++;
                            `$INSTANCE_NAME`isr_struct.len_data--;
                            `$INSTANCE_NAME`isr_struct.i2c_state=DATA;
                        }
                        else `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_STOP;
                        break;
                    case STOP: break;
                }
                break;
        }
    }
    else 
    {
        if(`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_STOP&isr_status) `$INSTANCE_NAME`isr_struct.i2c_state=STOP;
        else  `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_STOP;
    }
    `$INSTANCE_NAME``[I2C]`ClearMasterInterruptSource(isr_status);
}

static void write_cmd(uint8* data,int16 len)
{
    if(len>0)
    {
        `$INSTANCE_NAME`isr_struct.ptr_data=data;
        `$INSTANCE_NAME`isr_struct.len_data=len;
        `$INSTANCE_NAME`isr_struct.i2c_state=START;
        `$INSTANCE_NAME`isr_struct.i2c_mode=WRITE_CMD;
        `$INSTANCE_NAME``[I2C]`I2CMasterClearStatus();
        `$INSTANCE_NAME``[I2C]`I2CMasterClearWriteBuf();
        `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = `$INSTANCE_NAME`SLAVE_ADR;
        `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_START;
        while(`$INSTANCE_NAME`isr_struct.i2c_state!=STOP);
    }
}
static void write_data(uint8* data,int16 len,uint8 inverse)
{
    if(len>0)
    {
        `$INSTANCE_NAME`isr_struct.inverse=inverse;
        `$INSTANCE_NAME`isr_struct.ptr_data=data;
        `$INSTANCE_NAME`isr_struct.len_data=len;
        if(len>1) `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_DATA_MULTI;
        else `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_DATA_UNO;
        `$INSTANCE_NAME`isr_struct.i2c_state=START;
        `$INSTANCE_NAME`isr_struct.i2c_mode=WRITE_DATA;
        `$INSTANCE_NAME``[I2C]`I2CMasterClearStatus();
        `$INSTANCE_NAME``[I2C]`I2CMasterClearWriteBuf();
        `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = `$INSTANCE_NAME`SLAVE_ADR;
        `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_START;
        while(`$INSTANCE_NAME`isr_struct.i2c_state!=STOP);
    }
}
static void write_fill(uint8 data,int16 len)
{
    if(len>0)
    {
        `$INSTANCE_NAME`isr_struct.len_data=len;
        if(len>1) `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_DATA_MULTI;
        else `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_DATA_UNO;
        `$INSTANCE_NAME`isr_struct.i2c_state=START;
        `$INSTANCE_NAME`isr_struct.fill=data;
        `$INSTANCE_NAME`isr_struct.i2c_mode=FILL;
        `$INSTANCE_NAME``[I2C]`I2CMasterClearStatus();
        `$INSTANCE_NAME``[I2C]`I2CMasterClearWriteBuf();
        `$INSTANCE_NAME``[I2C]`TX_FIFO_WR_REG = `$INSTANCE_NAME`SLAVE_ADR;
        `$INSTANCE_NAME``[I2C]`I2C_MASTER_GENERATE_START;
        while(`$INSTANCE_NAME`isr_struct.i2c_state!=STOP);
    }
}


void `$INSTANCE_NAME`_Setup() {
    `$INSTANCE_NAME`isr_struct.i2c_state=STOP;
	write_cmd((uint8*)ini_array,sizeof(ini_array));
}

void `$INSTANCE_NAME`_Start() {
    `$INSTANCE_NAME``[I2C]`SetCustomInterruptHandler(&`$INSTANCE_NAME``[I2C]`I2C_ISR);
	`$INSTANCE_NAME``[I2C]`Start();
    `$INSTANCE_NAME``[I2C]`SetMasterInterruptMode(`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_STOP|`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_ACK|`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_NACK|`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_ARB_LOST|`$INSTANCE_NAME``[I2C]`INTR_MASTER_I2C_BUS_ERROR);
	`$INSTANCE_NAME`_Setup();
    `$INSTANCE_NAME`_ClearAll();
}

void `$INSTANCE_NAME`_SetCursorPosition(uint8 page, uint8 col) {
    `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_CMD_MULTI;
    `$INSTANCE_NAME`isr_struct.cmd[1]=CMD_GOTO_DEFPAGE;
    `$INSTANCE_NAME`isr_struct.cmd[2]=CMD_SET_Y_ADR | (page & 0xF);
    `$INSTANCE_NAME`isr_struct.cmd[3]=CMD_SET_RAMPAGE0;
    `$INSTANCE_NAME`isr_struct.cmd[4]=CMD_SET_X_ADR | (col & 0x7F);
    write_cmd((uint8*)&(`$INSTANCE_NAME`isr_struct.cmd[0]),5);
}

void `$INSTANCE_NAME`_SetContrast(uint8 contrast_level) {
    `$INSTANCE_NAME`isr_struct.cmd[0]=CMD_WRITE_CMD_MULTI;
    `$INSTANCE_NAME`isr_struct.cmd[1]=CMD_GOTO_DEFPAGE;
    `$INSTANCE_NAME`isr_struct.cmd[2]=CMD_GOTO_PAGE|5;
    `$INSTANCE_NAME`isr_struct.cmd[3]=CMD_SET_VLCD| (contrast_level & 0x7F);
    write_cmd((uint8*)&(`$INSTANCE_NAME`isr_struct.cmd[0]),4);
}

void `$INSTANCE_NAME`_Clear(uint8 start_row, uint8 start_col, uint8 end_row, uint8 end_col, uint8 value) {
    for(uint8 row = start_row; row <=end_row; row++) {
	    `$INSTANCE_NAME`_SetCursorPosition(row, start_col);
        write_fill(value,end_col-start_col+1);
	    }
}

void `$INSTANCE_NAME`_ClearAll() {
    	for(uint8 row = 0; row < `$INSTANCE_NAME`MAX_PAGE; row++) {
            `$INSTANCE_NAME`_SetCursorPosition(row, 0);
            write_fill(0, `$INSTANCE_NAME`MAX_COL);
            }
}

void `$INSTANCE_NAME`_DrawText(uint8 start_page, uint8 start_col, const char *text, uint8 inverse) {
    uint8 col_tmp;
    uint16 len;
    if(start_col<128)
    {
	    for(uint8 row = 0; row < 2; row++) {
            col_tmp=start_col;
    	    `$INSTANCE_NAME`_SetCursorPosition(start_page - row, start_col);
	        for(const char *c = text; *c != '\0'; c++) {
                if(*c!='.')
                {
                    if((col_tmp+FONT_GLYPH_COLUMNS)>127) len=128-col_tmp;
                    else len=FONT_GLYPH_COLUMNS;
                    write_data((uint8*)&glyphs[*c - FONT_GLYPH_OFFSET][row][0],len,inverse);
                    col_tmp+=len;
                }
                else
                {
                    if((col_tmp+4)>127) len=128-col_tmp;
                    else len=4;
                    write_data((uint8*)&glyphs[*c - FONT_GLYPH_OFFSET][row][4],len,inverse);
                    col_tmp+=len;
                }
                if(col_tmp>127) break;
	        }
        }
    }
}

void `$INSTANCE_NAME`_DrawBigNumbers(uint8 start_page, uint8 start_col, const char *nums) 
{
    for(uint8 page = 0; page < 4; page++) 
    {
        `$INSTANCE_NAME`_SetCursorPosition(start_page - page, start_col);
		for(const char *c = nums; *c != '\0'; c++)
        {
    		if(*c >= '0' && *c <= '9')
            {
                 write_data((uint8*)&big_glyphs[*c - '0'][FONT_BIGDIGIT_WIDTH*page],FONT_BIGDIGIT_WIDTH,0);
    		} 
            else
            {
                if(*c == '.')
                {
                    if(page==3)  write_data((uint8*)&big_period[0],5,0);
                    else  write_fill(0,5);
                }
                else
                {
                    if(page>=2)
                    {
                        write_data((uint8*)&glyphs[*c - FONT_GLYPH_OFFSET][page-2][0],FONT_GLYPH_COLUMNS,0);
                    }
                }
            }
        }
    }
}

/* [] END OF FILE */
