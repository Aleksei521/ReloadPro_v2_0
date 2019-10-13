#include <defines.h>

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
