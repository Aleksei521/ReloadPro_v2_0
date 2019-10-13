#include <project.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "tasks.h"
#include "config.h"


state_t state;
//xTaskHandle adc_task;
xTaskHandle comms_task;
xTaskHandle ui_task;

//const uint8 EEsettings[EEPROM_PHYSICAL_SIZE] __ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u}; 
const uint8 EEsettings[EEPROM_PHYSICAL_SIZE] CY_SECTION(".cy_checksum_exclude") __ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u};
settings_t settings;

const settings_t default_settings = {
    .settings_version = 0x20,    
	.lcd_contrast = CONTRAST_DEF,
    .cooler_on_temperature=50,
    .cooler_on_adc_data=1507,
    .cooler_off_adc_data=1476,
    .display_settings = {
        .named = {
            .cc = {
		        .readouts = {READOUT_CURRENT_SETPOINT, READOUT_CURRENT_USAGE, READOUT_VOLTAGE},
	        },
        },
    },	
	.calibration_settings = {
		.dac_low_gain = DEFAULT_DAC_LOW_GAIN,
		.dac_high_gain = DEFAULT_DAC_HIGH_GAIN,
		.dac_offset = DEFAULT_DAC_OFFSET,
		.opamp_offset_trim = DEFAULT_OPAMP_OFFSET_TRIM,
		
		.adc_current_offset = DEFAULT_ADC_CURRENT_OFFSET,
		.adc_current_gain = DEFAULT_ADC_CURRENT_GAIN,
		
		.adc_voltage_offset = DEFAULT_ADC_VOLTAGE_OFFSET,
		.adc_voltage_gain = DEFAULT_ADC_VOLTAGE_GAIN,

		.voltage_correction_ratio = DEFAULT_VOLTAGE_CORRECTION_RATIO,
	},
};
void factory_reset() {
    EEPROM_Write(0,(void*)&default_settings, sizeof(settings_t));
    EEPROM_Read(0,(void*)&settings,sizeof(settings_t));
}
void prvHardwareSetup();

int main()
{
    uint8 res=0;
    uint32 ee_status;
    CyGlobalIntEnable;

#if USE_WATCHDOG
    // Enable watchdog timer for every 2 seconds
    CySysWdtWriteMode(0, CY_SYS_WDT_MODE_RESET);
    CySysWdtWriteMatch(0, 0xFFFF);
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
#endif
    EEPROM_Init((uint32)EEsettings);
    ee_status=EEPROM_Read(0,(void*)&settings,sizeof(settings_t));
    if(ee_status||(settings.settings_version < default_settings.settings_version)) 
    {
        factory_reset();
        res=1;
    }
    Backlight_Write(1);	
	disp_reset_Write(0);
	CyDelayUs(10);
	disp_reset_Write(1);
	CyDelayUs(10);
	Display_Start();
    Display_SetContrast(settings.lcd_contrast);
    if(res)
    {
        Display_Clear(0,0,7,127,0xFF);
        Display_DrawText(5,10,"!Factory!",1);
        Display_DrawText(3,18,"!Reset!",1);
        CyDelay(2000);
        Display_ClearAll();
    }
	IDAC_High_Start();
	IDAC_Low_Start();
    state.calibrating = 0;
    set_current(0);
	set_output_mode(OUTPUT_MODE_FEEDBACK);		
	start_adc();
    Opamp_Start();
    Opamp_REF_Start();
	setup();
    CoolerWarning_period_reg=200;
    CoolerWarning_bounce_reg=2;
	//Create the two tasks
	xTaskCreate(vTaskUI, (signed portCHAR *) "UI", 178, NULL, tskIDLE_PRIORITY + 2, &ui_task);
	xTaskCreate(vTaskComms, (signed portCHAR *) "UART", 180, NULL, tskIDLE_PRIORITY + 2, &comms_task);
	
	prvHardwareSetup();
	vTaskStartScheduler();
}

/* ---------------------------------------------------------------------------
 * FreeRTOS support and configuration functions
 * --------------------------------------------------------------------------- */

void prvHardwareSetup( void )
{
	/* Port layer functions that need to be copied into the vector table. */
	extern void xPortPendSVHandler( void );
	extern void xPortSysTickHandler( void );
	extern void vPortSVCHandler( void );
	extern cyisraddress CyRamVectors[];

	/* Install the OS Interrupt Handlers. */
	CyRamVectors[ 11 ] = ( cyisraddress ) vPortSVCHandler;
	CyRamVectors[ 14 ] = ( cyisraddress ) xPortPendSVHandler;
	CyRamVectors[ 15 ] = ( cyisraddress ) xPortSysTickHandler;
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* The stack space has been execeeded for a task, considering allocating more. */
	taskDISABLE_INTERRUPTS();
	for( ;; ) {
        Backlight_Write(0);
        CyDelay(500);
        Backlight_Write(1);
        CyDelay(500);
    }
}

void vApplicationMallocFailedHook( void )
{
	/* The heap space has been execeeded. */
	taskDISABLE_INTERRUPTS();
	for( ;; ){
        Backlight_Write(0);
        CyDelay(2000);
        Backlight_Write(1);
        CyDelay(2000);
    }
}

/* [] END OF FILE */
