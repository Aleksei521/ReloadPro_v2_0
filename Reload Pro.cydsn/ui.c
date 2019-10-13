/* ========================================
 *
 * Copyright Arachnid Labs, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "comms.h"
#include "calibrate.h"
#include "tasks.h"
#include "Display_font.h"
#include "config.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

const uint16 termistor_tbl[166]={71,75,79,83,88,92,98,103,109,116,122,130,137,145,153,162,171,180,\
    190,200,210,221,232,243,254,266,278,291,304,318,331,345,360,375,390,406,422,439,455,473,490,\
    509,528,547,566,586,606,627,648,669,690,712,733,755,777,799,822,844,867,889,911,934,957,979,\
    1001,1024,1046,1068,1090,1112,1134,1155,1176,1197,1218,1238,1259,1278,1298,1317,1336,1355,\
    1373,1391,1409,1426,1443,1459,1476,1491,1507,1522,1537,1551,1565,1579,1592,1605,1618,1630,\
    1642,1654,1665,1676,1687,1697,1708,1717,1727,1736,1745,1754,1762,1771,1779,1786,1794,1801,1808,\
    1815,1822,1828,1834,1840,1846,1852,1857,1863,1868,1873,1877,1882,1887,1891,1895,1900,1904,1907,\
    1911,1915,1919,1922,1925,1928,1932,1935,1938,1941,1943,1946,1949,1952,1954,1957,1959,1961,1964,\
    1966,1968,1970,1972,1974,1976,1978,1980,1982};


static int8 get_temperature_calc(void);
static void show_temperature(uint8 page,uint8 col,int8 t);

xQueueHandle ui_queue;

typedef struct {
	void (*func)(char *);
	char *label;
} readout_function_impl;

typedef struct state_func_t {
	struct state_func_t (*func)(const void*);
	const void *arg;
	const int8 is_main_state;
} state_func;

typedef enum {
	VALUE_TYPE_CURRENT_RANGE,
} value_type;

typedef struct {
	const char *caption;
	const state_func new_state;
} menuitem;

typedef struct {
	const char *title;
	const menuitem items[];
} menudata;

typedef struct {
	const value_type type;
	const void *target;
	const int value;
} valueconfig;

typedef void (*void_func)();

static state_func cc_load(const void*);
static state_func menu(const void*);
static state_func ui_set_min_voltage(const void*);
static state_func ui_calibrate(const void*);
static state_func display_config(const void*);
static state_func set_contrast(const void *);
static state_func overlimit(const void*);
static state_func call_void_func(const void*);
static state_func upgrade(const void*);
static state_func set_cooler(const void *arg);
static void measure_Battery_ISR();

#define STATE_MAIN_MENU {menu, &main_menu, 0}/*Initally we start on this menu entry*/
#define STATE_TOOLS_MENU {menu,&tools_menu,0}/*Tools menu*/
/*Following are all the details for the menu items*/
#define STATE_MAIN                  {NULL, NULL, 0}
#define STATE_CC_LOAD               {cc_load, NULL, 1}
#define STATE_MIN_VOLTAGE           {ui_set_min_voltage, NULL, 0}
#define STATE_CALIBRATE             {ui_calibrate, NULL, 0}
#define STATE_CONFIGURE_CC_DISPLAY  {display_config, 0, 0}
#define STATE_SET_CONTRAST          {set_contrast, NULL, 0}
#define STATE_SET_COOLER            {set_cooler, NULL, 0}
#define STATE_LIMIT                 {overlimit, NULL, 0}
#define STATE_RESET_TOTALS          {call_void_func, (void_func)reset_running_totals, 0}
#define STATE_UPGRADE               {upgrade, NULL, 0}
#define STATE_BATTERY_ISR           {"Batt ISR", {call_void_func,measure_Battery_ISR , 0}}

const menudata set_readout_menu = {
	"SETTINGS",
	{
		{"SetCur", {NULL, (void*)READOUT_CURRENT_SETPOINT, 0}},
		{"ActualCur", {NULL, (void*)READOUT_CURRENT_USAGE, 0}},
		{"Voltage", {NULL, (void*)READOUT_VOLTAGE, 0}},
		{"Power", {NULL, (void*)READOUT_POWER, 0}},
		{"Resist", {NULL, (void*)READOUT_RESISTANCE, 0}},
		{"TotalCur", {NULL, (void*)READOUT_TOTAL_CURRENT, 0}},
		{"TotalPwr", {NULL, (void*)READOUT_TOTAL_POWER, 0}},
		{"None", {NULL, (void*)READOUT_NONE, 0}},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata choose_readout_menu = {
	"Readouts",
	{
		{"MainDisp", {NULL, (void*)1, 0}},
		{"UpDisp", {NULL, (void*)2, 0}},
		{"DownDisp", {NULL, (void*)3, 0}},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};

const menudata tools_menu = {
	NULL,
	{
		STATE_BATTERY_ISR,
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};


const menudata main_menu = {
	NULL,
	{
		{"C/C Load", STATE_CC_LOAD},
		{"Readouts", STATE_CONFIGURE_CC_DISPLAY},
        {"MinVolt", STATE_MIN_VOLTAGE},
		{"Reset", STATE_RESET_TOTALS},
        {"Tools",STATE_TOOLS_MENU},
		{"Contrast", STATE_SET_CONTRAST},
		{"Cooler", STATE_SET_COOLER},
		{"Calibrate", STATE_CALIBRATE},
		{"UpgrMode", STATE_UPGRADE},
        {"EXIT", STATE_MAIN},
		{NULL, {NULL, NULL, 0}},
	}
};



volatile portTickType long_button_press_tick_count = portMAX_DELAY;

void vApplicationTickHook( void )
{
	static ui_event event = {.type = UI_EVENT_BUTTONPRESS, .when = 0};
    static portTickType before = 0;

    int button_now = QuadButton_Read();
    if (button_now != event.int_arg)
    {
        before = event.when;
        event.when = xTaskGetTickCountFromISR();

    	event.int_arg = button_now;

        // it is suggested to have debounce timer of 5-30 ms in different sources, so going with conservetive 30 ms value
    	if(event.int_arg) {
            long_button_press_tick_count = portMAX_DELAY;
            if(event.when - before >= (30 * configTICK_RATE_HZ / 1000)) {
    		    xQueueSendToBackFromISR(ui_queue, &event, NULL);
            }
    	} else {
            long_button_press_tick_count = event.when + configTICK_RATE_HZ;
        }
    }
}

// Maps current state (index) to next state for a forward transition.
const int8 quadrature_states[] = {0x1, 0x3, 0x0, 0x2};

CY_ISR(quadrature_event_isr) {
	static ui_event event = {.type = UI_EVENT_UPDOWN, .when = 0, .int_arg = 0};
    static int8 last_levels = 3;
	static int8 count = 0;
    static portTickType before = 0;

	int levels = Quadrature_Read();
	Quadrature_ClearInterrupt();

	if(quadrature_states[last_levels] == levels) {
		count += 1;
		last_levels = levels;
	} else if(quadrature_states[levels] == last_levels) {
		count -= 1;
		last_levels = levels;
	}

	if(abs(count) >= 4) {
        before = event.when;
        event.when = xTaskGetTickCountFromISR();

        // calculate step size that is inversely proportional to the time that has passed since last click
        event.duration = event.when - before;
        if(event.duration < 1)
            event.duration = 1;

        event.int_arg = count / 4;
		xQueueSendToBackFromISR(ui_queue, &event, NULL);
		count = count % 4;
	}
}

static void format_number(int num, const char *suffix, char *out) {
	if(num < 0)
		num = 0;

	int magnitude = 1;
	while(num >= 1000000) {
		num /= 1000;
		magnitude++;
	}

	int whole = num / 1000, remainder = num % 1000;
	if(whole < 10) {
		// Format: x.xx
		sprintf(out, "%1d.%02d", whole, remainder / 10);
	} else if(whole < 100) {
		// Format: xx.x
		sprintf(out, "%02d.%1d", whole, remainder / 100);
	} else {
		// Format: xxx
		sprintf(out, "%03d", whole);
	}

	if(magnitude == 1) strcat(out, "m");
    strcat(out, suffix);
}

static void format_number_simple(int num, const char *suffix, char *out) {
	if(num < 0) num = 0;
	num /= 1000;
	int whole = num / 1000, remainder = num % 1000;
	sprintf(out, "%3d.%03d%s", whole, remainder, suffix);
}

static void adjust_current_setpoint(int delta, portTickType duration) {
    // Implement encoder acceleration
    int step = (((ENCODER_ACCEL_CONSTANT * configTICK_RATE_HZ) / 1000) / duration);
    if(step < 1)
        step = 1;
	set_current(state.current_setpoint + delta * step * CURRENT_STEP);
    uart_printf("set %d\r\n", state.current_setpoint / 1000);
}

static void next_event(ui_event *event) {
	static portTickType last_tick = 0;
    static uint8 long_press_sent = 0;

    portTickType now = xTaskGetTickCount();

    if(now > long_button_press_tick_count && !long_press_sent) {
        event->type = UI_EVENT_LONG_BUTTONPRESS;
        event->when = now;
        event->int_arg = 0;
        long_press_sent = 1;
    } else if(now - last_tick >  configTICK_RATE_HZ / UI_TASK_FREQUENCY
        || !xQueueReceive(ui_queue, event, configTICK_RATE_HZ / UI_TASK_FREQUENCY - (now - last_tick))) {
		event->type = UI_EVENT_TICK;
		event->when = now;
		last_tick = now;
#ifdef USE_WATCHDOG
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
#endif
	} else if(event->type == UI_EVENT_BOOTLOAD) {
        // Bootloading overrides everything
        upgrade(NULL); // Never returns
    } else if(event->type == UI_EVENT_BUTTONPRESS && long_press_sent) {
        long_press_sent = 0;
		event->type = UI_EVENT_TICK;
		event->when = now;
		last_tick = now;
#ifdef USE_WATCHDOG
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
#endif
    }
}

static void draw_menu(const menudata *menu, int selected) {
	int start_row = 7;
	int height = 4;

	if(menu->title) {
		int8 padding = (127 - strlen(menu->title) * 12) / 2;
		Display_Clear(6, 2, 7, padding + 1, 0xFF);
		Display_DrawText(7, padding + 1, menu->title, 1);
		Display_Clear(6, 127 - padding - 1, 7, 127, 0xFF);
		start_row-=2;
		height--;
	}

	Display_DrawText(start_row, 115, ((selected / height) > 0)?FONT_GLYPH_UARR:" ", 0);

	// Find the block of items the selected element is in
	const menuitem *current = &menu->items[selected - selected % height];
	selected %= height;

	for(int i = 0; i < height; i++) {
		if(current->caption != NULL) {
			Display_DrawText(start_row-i*2, 2, current->caption, i == selected);
			Display_Clear(start_row-i*2-1, strlen(current->caption) * 12 + 1,  start_row -i*2, 114, (i == selected)*255);
			current++;
		} else {
			Display_Clear(start_row-i*2-1, 0, start_row -i*2, 127, 0);
		}
	}

	if(current->caption != NULL) {
		Display_DrawText(1, 115, FONT_GLYPH_DARR, 0);
	} else {
		Display_DrawText(1, 115, " ", 0);
	}
}

void print_nothing(char *buf) {
	strcpy(buf, "      ");
}

void print_setpoint(char *buf) {
	format_number(get_current_setpoint(), "A", buf);
}

void print_current_usage(char *buf) {
	format_number(get_current_usage(), "A", buf);
}

void print_voltage(char *buf) {
	format_number(get_voltage(), "V", buf);
}

void print_power(char *buf) {
	int power = (get_current_usage() / 1000) * (get_voltage() / 1000);
	format_number(power, "W", buf);
}

void print_resistance(char *buf) {
	int current = get_current_usage();
	if(current > 0) {
		format_number(((get_voltage() * 10) / (current / 100000)), FONT_GLYPH_OHM, buf);
	} else {
		strcpy(buf, "----" FONT_GLYPH_OHM);
	}
}


void print_amp_hours(char *buf) {
	format_number(get_microamp_hours(), "Ah", buf);
}

void print_watt_hours(char *buf) {
	format_number(get_microwatt_hours(), "Wh", buf);
}

const readout_function_impl readout_functions[] = {
	{print_nothing, ""},
	{print_setpoint, "SET"},
	{print_current_usage, "ACT"},
	{print_voltage, ""},
	{print_power, ""},
	{print_resistance, ""},
	{print_amp_hours, ""},
	{print_watt_hours, ""},
	{print_nothing, ""}
};

static void draw_status(const display_config_t *config, uint8 force_current_setpoint_readout) {
	char buf[8];
	// Draw the main info
	const readout_function_impl *readout = &readout_functions[force_current_setpoint_readout?READOUT_CURRENT_SETPOINT:config->readouts[0]];
	if(readout->func != print_nothing) {
		readout->func(buf);
    	Display_Clear(4, 72, 7, 77, 0);
		Display_Clear(4, 77, 5, 114, 0);
		Display_DrawBigNumbers(7, 0, buf);
	} else {
		Display_Clear(4, 0, 7, 77, 0);
		Display_Clear(4, 77, 5, 114, 0);
	}

	// Draw the type in the top right
	uint8 labelsize = strlen(readout->label) * 12;
	Display_DrawText(7, 127 - labelsize, readout->label, 1);
	if(labelsize < 36) Display_Clear(6, 91, 7, 127 - labelsize, 0);

    // Draw the state in the middle right
    if(get_output_mode() == OUTPUT_MODE_OFF) {
    	Display_DrawText(1, 91, "OFF", 1);
    } else {
        Display_Clear(0, 91, 1, 127, 0);
    }

	// Draw the two smaller displays
	for(int i = 0; i < 2; i++) {
		readout = &readout_functions[config->readouts[i + 1]];
		readout->func(buf);
		Display_Clear(2-i*2,48,3-i*2,79,0);
		Display_DrawText(3-i*2, 0, buf, 0);
	}
    //COOLER
    if(get_cooler_state()) 
    {   if(CoolerStatusReg_Read()&1)
            Display_DrawText(5, 115,FONT_GLYPH_GOOD_COOLER, 0);
        else
            Display_DrawText(5, 115,FONT_GLYPH_BAD_COOLER, 0);
    }
    else Display_Clear(4,115,5,127,0);
    show_temperature(3,79,get_temperature_calc());
}

static int8 get_temperature_calc(void)
{
    uint8 low_i=0;
    uint8 high_i=TEMPERATURE_MAX-TEMPERATURE_MIN;
    uint8 median_i=high_i>>1;
    uint16 term=get_termistor();
    do
    {
        median_i+=low_i;
        if(term>termistor_tbl[median_i]) low_i=median_i;
        else 
        {
            high_i=median_i;
            if(term==termistor_tbl[median_i]) break;
        }
        median_i=(high_i-low_i)>>1;
    }while(median_i);
    return (int16)high_i+TEMPERATURE_MIN;
}

void show_temperature(uint8 page,uint8 col,int8 t)
{
    char out[8];
    sprintf(out,"%3d",t);
    strcat(out,FONT_GLYPH_CELSIUS);
    //Display_Clear(page-1,col,page,col+48,0);
    Display_DrawText(page, col,out, 0);
}

static state_func display_config(const void *arg) {
	const display_config_t *config = &settings.display_settings.numbered[(int)arg];

	state_func display = menu(&choose_readout_menu);
	if(display.arg == NULL)
		return display;

	state_func readout = menu(&set_readout_menu);
	if(readout.arg == NULL)
		return readout;

    memcpy((uint8*)&(config->readouts[(int)display.arg - 1]),(uint8*)&((readout_function){(readout_function)readout.arg}),sizeof(readout_function));
	EEPROM_Write(0,(void*)&settings,sizeof(settings_t));

	return (state_func)STATE_MAIN;
}

//Delay and resets the watchdog every second
static void delayWithWatchDog(uint8_t seconds)
{
    CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
     for(uint8_t i=0;i<seconds;i++)
    {
        CyDelay(1000);
        #if USE_WATCHDOG
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
        #endif
    }
}
// Handles measuring the battery ISR with two current steps
static void measure_Battery_ISR()
{
    Display_ClearAll();
    Display_DrawText(7, 0, "BATT TEST", 1);
    //This is based roughly on what i can find of the  IEC 61951-1:2005 online
    //We use a current of 1A for testing.
    //First we measure light load
    Display_DrawText(5, 0, "L Load RUN", 0);
    set_current(100000);//100mA
    delayWithWatchDog(10);//light load for 10 seconds
    uint32_t halfLoadVoltage = get_voltage()*10; //measure in the middle (in 10x vuV)
    Display_DrawText(5, 76, "PASS", 1);
    Display_DrawText(3, 0, "F Load RUN", 0);
    set_current(1000000);//1A
    delayWithWatchDog(3);//full load for 3 seconds
    uint32_t fullLoadVoltage = get_voltage()*10;
    set_current(0);//stop pulling current
    //Test done
    //Compute results
    //Ohms = V/A => We compute two values using the low current
    //Using Rdc = (V1-V2)/(I2-I1)
    int Rdc = (halfLoadVoltage-fullLoadVoltage)/(9);
    //would be divide by 900*100, but we want to shift into milli ohms by 1000*1000
    //so we move the divisor by 100 and shift the top by 10 previously
    //Basically we avoid doing the divide as we need to multiple to get the answer scaled correctly
    //So we basically just remove 1000 from that multiple ^ and then the other part is avoid as we are outputing milli ohms instead of ohms
    //So we want an answer that is 10^3 larger than 'correct'
    Display_DrawText(3, 76, "PASS", 1);
    char buf[16];
    format_number(Rdc, FONT_GLYPH_OHM " " FONT_GLYPH_ENTER "Back", buf);//draw it in with the right symbol
    Display_DrawText(1, 0, buf, 0);
    //wait for user to acknowledge
    ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
	}
     //were done :)
}

static state_func call_void_func(const void *arg) {
	((void_func)arg)();
	return (state_func)STATE_MAIN;
}
//Set the LCD contrast
static state_func set_contrast(const void *arg) {
	Display_ClearAll();
	Display_Clear(6, 2, 7, 127, 0xFF);
	Display_DrawText(7, 16, "Contrast", 1);
	Display_DrawText(1, 28, FONT_GLYPH_ENTER ": Done", 0);

	// Left and right ends of the bar
    Display_DrawText(4,20,FONT_GLYPH_MENU_LARR,0);
    Display_DrawText(4,96,FONT_GLYPH_MENU_RARR,0);

    int contrast = settings.lcd_contrast;
	ui_event event;
	while(1) {
		Display_Clear(3, 32, 4,contrast - CONTRAST_MIN+32, 0xFF);
        if(contrast!=CONTRAST_MAX)
		    Display_Clear(3, contrast - CONTRAST_MIN+32+1, 4, 95, 0x81);

		next_event(&event);
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			contrast += event.int_arg;
			if(contrast > CONTRAST_MAX) {
				contrast = CONTRAST_MAX;
			} else if(contrast < CONTRAST_MIN) {
				contrast = CONTRAST_MIN;
			}
			Display_SetContrast(contrast);
			break;
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1) {
                settings.lcd_contrast=contrast;
				EEPROM_Write(0,(void*)&settings, sizeof(settings_t));
				return (state_func)STATE_MAIN;
			}
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
	}
}
static state_func set_cooler(const void *arg) {
	Display_ClearAll();
	Display_Clear(6, 2, 7, 127, 0xFF);
	Display_DrawText(7, 28, "Cooler", 1);
	Display_DrawText(1, 28, FONT_GLYPH_ENTER ": Done", 0);


    int16 cooler_tmp = settings.cooler_on_temperature;
    int16 cooler_tmp_show=-32767;
	ui_event event;
    Display_DrawText(5, 16, "SET TEMP", 0);
	while(1) {
        if(cooler_tmp!=cooler_tmp_show)
        {
            cooler_tmp_show=cooler_tmp;
            show_temperature(3,30,cooler_tmp);
        }

		next_event(&event);
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			cooler_tmp += event.int_arg;
			if(cooler_tmp > TEMPERATURE_MAX) {
				cooler_tmp = TEMPERATURE_MAX;
			} else if(cooler_tmp < TEMPERATURE_MIN) {
				cooler_tmp = TEMPERATURE_MIN;
			}
			break;
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1) {
                settings.cooler_on_temperature=cooler_tmp;
                settings.cooler_on_adc_data=termistor_tbl[cooler_tmp+40];
                settings.cooler_off_adc_data=termistor_tbl[cooler_tmp+40-COOLER_OFF_DELTA];
				EEPROM_Write(0,(void*)&settings, sizeof(settings_t));
				return (state_func)STATE_MAIN;
			}
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
	}
}

static state_func ui_set_min_voltage(const void *arg) {
    Display_ClearAll();
	//Display_Clear(5, 2, 7, 127, 0xFF);
	Display_DrawText(7, 0, "MinVoltage", 1);

    ui_event event;
    uint8_t on = state.lower_voltage_limit != -1;
    int vlim = on?state.lower_voltage_limit:get_voltage();
    vlim -= vlim % 100000;
    uint8_t stage = 0;
    char buf[8];

    while(stage == 0) {
        Display_DrawText(4, 17, "ON", on);
        Display_DrawText(4, 77, "OFF", !on);
        format_number(vlim, "V", buf);
        Display_DrawText(1, 40, buf, 0);

        next_event(&event);
        switch(event.type) {
        case UI_EVENT_UPDOWN:
            on ^= event.int_arg & 1;
            break;
        case UI_EVENT_BUTTONPRESS:
            if(event.int_arg != 1)
                break;
            if(on) {
                stage = 1;
            } else {
                state.lower_voltage_limit = -1;
                return (state_func)STATE_MAIN;
            }
            break;
        case UI_EVENT_LIMIT:
            return (state_func){overlimit, (void *)event.int_arg, 0};
        default:
            break;
        }
    }

    while(1) {
        format_number(vlim, "V", buf);
	    Display_Clear(0, 80, 1, 114, 0);
        Display_DrawText(1, 40, buf, 1);

        next_event(&event);
        switch(event.type) {
        case UI_EVENT_UPDOWN:
            vlim += 100000 * event.int_arg;
            if(vlim<0) vlim=0;
            break;
        case UI_EVENT_BUTTONPRESS:
            if(event.int_arg != 1)
                break;
            state.lower_voltage_limit = vlim;
            return (state_func)STATE_MAIN;
        case UI_EVENT_LIMIT:
            return (state_func){overlimit, (void *)event.int_arg, 0};
        default:
            break;
        }
    }
}

static state_func overlimit(const void *arg) {
	Display_Clear(0, 0, 7, 127, 0xFF);
    switch((limit_type)arg) {
    case LIMIT_TYPE_OVERTEMP:
    	Display_DrawText(5, 0, "!OVERTEMP!", 1);
        break;
    case LIMIT_TYPE_UNDERVOLT:
        Display_DrawText(5, 0, "!UNDERVOLT!", 1);
        break;
    }
	Display_DrawText(1, 16, FONT_GLYPH_ENTER ":Reset", 1);

	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);
		if(get_output_mode() == OUTPUT_MODE_FEEDBACK)
			return (state_func)STATE_MAIN;
	}

	set_current(0);
	set_output_mode(OUTPUT_MODE_FEEDBACK);
	return (state_func)STATE_MAIN;
    CyDelay(1000);
}

static state_func menu(const void *arg) {
	const menudata *menu = (const menudata *)arg;

	Display_ClearAll();
	int selected = 0;
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		draw_menu(menu, selected);
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_UPDOWN:
			if(event.int_arg < 0) {
				// Move up the menu
				if(selected + event.int_arg >= 0) {
					selected += event.int_arg;
				} else {
					selected = 0;
				}
			} else {
				// Move down the menu (but not past the end)
				for(int i = 0; i < event.int_arg; i++) {
					if(menu->items[selected + 1].caption == NULL)
						break;
					selected++;
				}
			}
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
	}
    
	return menu->items[selected].new_state;
}


static state_func cc_load(const void *arg) {
	static portTickType last_adjust_current_setpoint = 0;

	Display_ClearAll();

	ui_event event;
	while(1) {
		next_event(&event);
		switch(event.type) {
		case UI_EVENT_BUTTONPRESS:
			if(event.int_arg == 1)
				return (state_func)STATE_MAIN_MENU;
            break;
        case UI_EVENT_LONG_BUTTONPRESS:
            if(get_output_mode() != OUTPUT_MODE_FEEDBACK) {
                set_output_mode(OUTPUT_MODE_FEEDBACK);
            } else {
                set_output_mode(OUTPUT_MODE_OFF);
            }
            break;
		case UI_EVENT_UPDOWN:
			last_adjust_current_setpoint = xTaskGetTickCount();
			adjust_current_setpoint(event.int_arg, event.duration);
			break;
		case UI_EVENT_LIMIT:
			return (state_func){overlimit, (void *)event.int_arg, 0};
		default:
			break;
		}
		draw_status(&settings.display_settings.named.cc, (xTaskGetTickCount() - last_adjust_current_setpoint) < configTICK_RATE_HZ);
		//CyDelay(200);
	}
}

#define CALIBRATION_CURRENT 2000000

// Calibrates the ADC voltage and current offsets.
// Run with nothing attached to the terminals.
static void ui_calibrate_offsets(settings_t *new_settings) {
    state.calibrating = 1;

    IDAC_Low_SetValue(0);
    IDAC_High_SetValue(0);

	Display_DrawText(5, 26, "Remove", 0);
	Display_DrawText(3, 32, "Leads", 0);
	Display_DrawText(1, 26, FONT_GLYPH_ENTER ": Next", 0);

	// Wait for a button press
	ui_event event;
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1)
		next_event(&event);

	calibrate_offsets(new_settings);
    state.calibrating = 0;
}

// Calibrate the ADC voltage gain.
// Run with a known voltage across the terminals
static void ui_calibrate_voltage(settings_t *new_settings) {
    state.calibrating = 1;

    IDAC_Low_SetValue(0);
    IDAC_High_SetValue(0);

	Display_DrawText(5, 20, "Adj Volt", 0);

	ui_event event;
	char buf[16];
	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);

		int voltage = (get_raw_voltage() - new_settings->calibration_settings.adc_voltage_offset) * new_settings->calibration_settings.adc_voltage_gain;
		format_number_simple(voltage, "V", buf);
		strcat(buf, " ");
		Display_DrawText(3, 14, buf, 0);

		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->calibration_settings.adc_voltage_gain += event.int_arg;
			break;
		default:
			break;
		}
	}
    state.calibrating = 0;
}

static void ui_calibrate_current(settings_t *new_settings) {
    state.calibrating = 1;

    IDAC_Low_SetValue(0);
    IDAC_High_SetValue((CALIBRATION_CURRENT - new_settings->calibration_settings.dac_offset) / new_settings->calibration_settings.dac_high_gain);

    Display_Clear(0, 0, 5, 127, 0);
	Display_DrawText(5, 20, "Adj Cur", 0);
	Display_DrawText(1, 26, FONT_GLYPH_ENTER ": Next", 0);

	ui_event event;
	char buf[16];
	int current;

	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);

		current = (get_raw_current_usage() - new_settings->calibration_settings.adc_current_offset) * new_settings->calibration_settings.adc_current_gain;
		format_number_simple(current, "A", buf);
		strcat(buf, " ");
		Display_DrawText(3, 14, buf, 0);

		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->calibration_settings.adc_current_gain += event.int_arg;
			break;
		default:
			break;
		}
	}
    state.calibrating = 0;
}

static void ui_calibrate_voltage_correction(settings_t *new_settings) {
	state.calibrating = 1;

	IDAC_Low_SetValue(0);
	IDAC_High_SetValue((CALIBRATION_CURRENT - new_settings->calibration_settings.dac_offset) / new_settings->calibration_settings.dac_high_gain);

	Display_Clear(0, 0, 5, 127, 0);
	Display_DrawText(5, 20, "Adj Volt", 0);
	Display_DrawText(1, 26, FONT_GLYPH_ENTER ": Next", 0);

	ui_event event;
	char buf[16];
	int current, voltage;

	event.type = UI_EVENT_NONE;
	while(event.type != UI_EVENT_BUTTONPRESS || event.int_arg != 1) {
		next_event(&event);

		current = (get_raw_current_usage() - new_settings->calibration_settings.adc_current_offset) * new_settings->calibration_settings.adc_current_gain;
		voltage = (get_raw_voltage() - new_settings->calibration_settings.adc_voltage_offset) * new_settings->calibration_settings.adc_voltage_gain;
		voltage += (current / 1024) * new_settings->calibration_settings.voltage_correction_ratio;
		format_number_simple(voltage, "V", buf);
		strcat(buf, " ");
		Display_DrawText(3, 14, buf, 0);

		switch(event.type) {
		case UI_EVENT_UPDOWN:
			new_settings->calibration_settings.voltage_correction_ratio += event.int_arg;
			break;
		default:
			break;
		}
	}
	state.calibrating = 0;
}

// Calibrates the opamp and current DAC offsets.
// Run with a voltage source attached

void ui_calibration_progress(int current, int all) {
	Display_Clear(0, 2, 1, 128 * current / all, 0xFF);
}

static void ui_calibrate_dacs(settings_t *new_settings) {
	Display_Clear(0, 0, 5, 127, 0);
	Display_DrawText(4, 40, "Wait", 0);

    // Draw a progress bar
    Display_Clear(0, 0, 1, 1, 0xFF);
	Display_Clear(0, 126, 1, 127, 0xFF);
    Display_Clear(0, 2, 1, 125, 0x81);
    calibrate_opamp_offset_trim(new_settings, CALIBRATION_CURRENT,ui_calibration_progress);
	calibrate_dacs(new_settings, CALIBRATION_CURRENT);
}

static state_func ui_calibrate(const void *arg) {
	set_current(0);
	set_output_mode(OUTPUT_MODE_FEEDBACK);

	settings_t new_settings;
	memcpy(&new_settings, &settings, sizeof(settings_t));
	memcpy(&new_settings.calibration_settings, &default_settings.calibration_settings, sizeof(calibration_settings_t));

	Display_ClearAll();
	Display_DrawText(7, 8, "CALIBRATE", 1);

	ui_calibrate_offsets(&new_settings);
	ui_calibrate_voltage(&new_settings);
	ui_calibrate_current(&new_settings);
	ui_calibrate_voltage_correction(&new_settings);
	ui_calibrate_dacs(&new_settings);
    memcpy((uint8*)&settings,(uint8*)&new_settings, sizeof(settings_t));
	EEPROM_Write(0,(uint8*)&settings, sizeof(settings_t));

	return (state_func){NULL, NULL, 0};
}

static state_func upgrade(const void *arg) {
#ifdef Bootloadable_START_BTLDR
    Display_ClearAll();
    Display_DrawText(7, 10, "!UPGRADE!", 1);
    Display_DrawText(5, 20, "READY TO", 0);
    Display_DrawText(3, 20, "FIRMWARE", 0);
    Display_DrawText(1, 20, "DOWNLOAD", 0);
    Bootloadable_Load();  // Never returns...
#endif
    return (state_func){NULL, NULL, 0}; // ...yet, we should make compiler happy
}

void vTaskUI( void *pvParameters ) {
	ui_queue = xQueueCreate(2, sizeof(ui_event));

	QuadratureISR_StartEx(quadrature_event_isr);

	state_func main_state = STATE_CC_LOAD;
	state_func state = STATE_CC_LOAD;

	while(1) {
		state_func new_state = state.func(state.arg);
		if(new_state.func == NULL) {
			memcpy(&state, &main_state, sizeof(state_func));
		} else {
			memcpy(&state, &new_state, sizeof(state_func));
		}

		if(state.is_main_state) {
			memcpy(&main_state, &state, sizeof(state_func));
		}
	}
}
/* [] END OF FILE */
