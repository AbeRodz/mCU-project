/*
 * API_debounce.c
 *
 *  Created on: Mar 21, 2024
 *      Author: rodz
 */



#include <MEF_LCD.h>

static debounceState_t button_state;

static bool_t long_press_detected = false;
static uint32_t button_press_time = 0;
static uint8_t num_presses = 0;

static delay_t debounce_delay;

static bool_t key_state = false;

static DisplayState_t display_state = DISPLAY_MENU;

static int32_t temp ,pressure,altitude;

void menu_init(void){
	LCD_SetCursorPos(0,0);
	LCD_send_txt((uint8_t *)"Push to cycle:");
	LCD_SetCursorPos(1,0);
	LCD_send_txt((uint8_t *)"Temp, Pres, Alt");
}

void update_display_state(void){
	//LCD_clear();
	switch (display_state) {
/*
	case DISPLAY_MENU:
		// Switch to the next display mode
		LCD_SetCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Push to cycle:");
		LCD_SetCursorPos(1,0);
		LCD_send_txt((uint8_t *)"Temp, Pres, Alt");
		break;*/
	case DISPLAY_TEMP:

		//LCD_SetCursorPos(0,0);
		//LCD_send_txt((uint8_t *)"Temp(C):");
		temp = MS5611_read_temp();
		LCD_update_value(0,8, temp);
		//HAL_Delay(500);

		break;

	case DISPLAY_TEMP_F:

		//LCD_SetCursorPos(0,0);
		//LCD_send_txt((uint8_t *)"Temp(F):");
		temp = MS5611_read_temp_fahrenheit();
		LCD_update_value(0,8, temp);
		//HAL_Delay(500);
		break;

	case DISPLAY_PRESS:

		//LCD_SetCursorPos(0,0);
		//LCD_send_txt((uint8_t *)"Pre(mbar):");
		pressure = MS5611_read_pressure();
		LCD_update_value(0,10, pressure);
		//HAL_Delay(500);
		break;

	case DISPLAY_ALT:

		//LCD_SetCursorPos(0,0);
		//LCD_send_txt((uint8_t *)"ALT(m):");
		altitude = MS5611_read_altitude();
		LCD_update_value(0,7, altitude);
		//HAL_Delay(200);
		break;

	default:
		break;
	}
}
void debounceFSM_init(void){
	button_state = BUTTON_UP;
	update_display_state();
}

void debounceFSM_update(void){
	delayInit(&debounce_delay, 50);

	switch (button_state){
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_FALLING;
			//button_press_time = HAL_GetTick();
		}
		break;


	case BUTTON_FALLING:
		delayRead(&debounce_delay);
		if (BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_DOWN;
			//key_state = true;
			buttonPressed();
		}else {
			button_state = BUTTON_UP;
		}
		break;

	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_RAISING;

		}
		/*else {
			// Check for long press detection
			if ((HAL_GetTick() - button_press_time) >= LONG_PRESS_THRESHOLD) {
				button_state = BUTTON_LONG_PRESS;
				long_press_detected = true;
			}
		}*/
		break;

	case BUTTON_RAISING:
		delayRead(&debounce_delay);
		if (!BSP_PB_GetState(BUTTON_USER)){
			button_state = BUTTON_UP;
			//if ((HAL_GetTick() - button_press_time) <= MULTIPLE_PRESS_THRESHOLD) {
			//	num_presses++;
			//} else {
			//	num_presses = 1; // Reset number of presses if too much time has passed
			//}
			//buttonReleased(); // Call buttonReleased() only when button is released

		}else {
			button_state = BUTTON_DOWN;
		}
		break;

	case BUTTON_LONG_PRESS:
		// Stay in this state until the button is released
		if (!BSP_PB_GetState(BUTTON_USER)) {
			button_state = BUTTON_UP;
			long_press_detected = false; // Reset long press detection flag
		}
		break;

	default:

		break;
	}
}

void buttonPressed(void){
	// Change the display mode when the button is pressed
	LCD_clear();
	switch (display_state) {

	case DISPLAY_MENU:
		// Switch to the next display mode

		LCD_SetCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Temp(C):");
		display_state = DISPLAY_TEMP;
		break;
	case DISPLAY_TEMP:
		LCD_SetCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Temp(F):");
		// Switch back to the initial display mode
		display_state = DISPLAY_TEMP_F;
		break;
	case DISPLAY_TEMP_F:
		// Switch back to the initial display mode
		LCD_SetCursorPos(0,0);
		LCD_send_txt((uint8_t *)"Pre(mbar):");

		display_state = DISPLAY_PRESS;
		break;
	case DISPLAY_PRESS:
		// Switch back to the initial display mode
		LCD_SetCursorPos(0,0);
		LCD_send_txt((uint8_t *)"ALT(m):");
		display_state = DISPLAY_ALT;
		break;
	case DISPLAY_ALT:
		// Switch back to the initial display mode
		menu_init();
		display_state = DISPLAY_MENU;
		break;
		// Add more cases for additional display modes
	default:

		break;
	}
}
void buttonReleased(void){
	if (long_press_detected) {
		// Execute actions for long press
		// For example, you can perform a specific action here
		// Reset any variables related to long press detection if needed
	} else {
		// Execute actions for short press or multiple presses
		if (num_presses > 1) {
			// Execute actions for multiple presses
			// For example, switch between different modes based on number of presses
		} else {
			// Execute actions for short press
			// For example, switch between different display modes
			buttonPressed(); // Call buttonPressed() only when a short press is detected
		}
	}
}

bool_t readKey(){

	if (key_state){
		key_state = false;
		return true;
	}else {
		return false;
	}
}


