/*
 * API_debounce.c
 *
 *  Created on: Mar 21, 2024
 *      Author: rodz
 */



#include <MEF_LCD.h>
#include "MEF_POWER_LCD.h"

// private variables
static debounceState_t button_state;

static delay_t debounce_delay;

static DisplayState_t display_state = DISPLAY_MENU;

static int32_t temp ,pressure,altitude;

static DisplayState_t old_state ;

// implementations
/**
 * @brief Prints onto the LCD the main menu.
 */
void menu_init(void){
	LCD_setCursorPos(0,0);
	LCD_send_txt((uint8_t *)"Push to cycle:");
	LCD_setCursorPos(1,0);
	LCD_send_txt((uint8_t *)"Temp, Pres, Alt");
}


/**
 * @brief Checks the current power state of the LCD to if active, update a value given a column in the first row.
 * @note This function only prints on the LCD's active state.
 */
void update_display_state(void){

	switch (display_state) {

	case DISPLAY_TEMP:

		temp = MS5611_read_temp();
		power_print(temp, 8);
		break;

	case DISPLAY_TEMP_F:

		temp = MS5611_read_temp_fahrenheit();
		power_print(temp, 8);
		break;

	case DISPLAY_PRESS:

		pressure = MS5611_read_pressure();
		power_print(pressure, 10);
		break;

	case DISPLAY_ALT:

		altitude = MS5611_read_altitude();
		power_print(altitude, 7);
		break;

	case DISPLAY_STANDBY:
		break;

	default:
		break;
	}
}

/**
 * @brief Initializes the debounce FSM, and prompts the main menu.
 */
void debounceFSM_init(void){
	button_state = BUTTON_UP;
	menu_init();

}

/**
 * @brief debounce FSM controller, checks the current power state, and the button state to cycle states.
 */
void debounceFSM_update(void){
	delayInit(&debounce_delay, 50);
	updatePowerState();
	update_display_state();
	if (get_power_state()==0) {

		display_state = DISPLAY_STANDBY;

	}
	switch (button_state){
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_FALLING;

		}
		break;

	case BUTTON_FALLING:
		delayRead(&debounce_delay);
		if (BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_DOWN;

			buttonPressed();
		}else {
			button_state = BUTTON_UP;
		}
		break;

	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_RAISING;

		}

		break;

	case BUTTON_RAISING:
		delayRead(&debounce_delay);
		if (!BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_UP;


		}else {
			button_state = BUTTON_DOWN;
		}
		break;

	case BUTTON_LONG_PRESS:

		if (!BSP_PB_GetState(BUTTON_USER)) {
			button_state = BUTTON_UP;

		}
		break;

	default:

		break;
	}
}

/**
 * @brief triggers the displays state change evetn when pressing the button.
 */
void buttonPressed(void){

	switch (display_state) {

	case DISPLAY_MENU:

		LCD_clear();
		LCD_setCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Temp(C):");
		old_state = display_state;
		display_state = DISPLAY_TEMP;

		break;

	case DISPLAY_TEMP:
		LCD_clear();
		LCD_setCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Temp(F):");

		old_state = display_state;
		display_state = DISPLAY_TEMP_F;

		break;

	case DISPLAY_TEMP_F:
		LCD_clear();

		LCD_setCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Pre(mbar):");
		old_state = display_state;
		display_state = DISPLAY_PRESS;

		break;

	case DISPLAY_PRESS:
		LCD_clear();

		LCD_setCursorPos(0,0);
		LCD_send_txt((uint8_t *)"ALT(m):");
		old_state = display_state;
		display_state = DISPLAY_ALT;

		break;

	case DISPLAY_ALT:
		LCD_clear();
		menu_init();
		old_state = display_state;
		display_state = DISPLAY_MENU;

		break;

	case DISPLAY_STANDBY:
		LCD_clear();
		menu_init();
		old_state = display_state;
		display_state = DISPLAY_MENU;

		break;

	default:

		break;
	}
}


