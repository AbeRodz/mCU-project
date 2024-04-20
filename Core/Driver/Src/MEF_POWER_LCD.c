/*
 * MEF_POWER_LCD.c
 *
 *  Created on: Apr 15, 2024
 *      Author: rodz
 */

#include "MEF_POWER_LCD.h"
#include "API_uart.h"


static PowerState_t power_state = POWER_STATE_ACTIVE;


static uint32_t active_start_time = 0;

/**
 * @brief Power state FSM controller, listens to the button event and the time event to update the power state of the LCD.
 * @note can subscribe any device to be controlled by the power FSM, just add it onto the power cases.
 */
void updatePowerState() {
	switch (power_state) {

	case POWER_STATE_ACTIVE:

		if (BSP_PB_GetState(BUTTON_USER)){
			active_start_time = HAL_GetTick();
		}

		if ((HAL_GetTick() - active_start_time) >= LOW_POWER_TIMEOUT){
			power_state = POWER_STATE_LOW_POWER;
			LCD_backlight_state(0);

		}

		break;

	case POWER_STATE_LOW_POWER:

		if (BSP_PB_GetState(BUTTON_USER)){
			power_state = POWER_STATE_ACTIVE;

			LCD_backlight_state(1);

			active_start_time = HAL_GetTick();
		}
		break;

	default:
		break;
	}
}


/**
 * @brief Retrives the current power state value from the FSM.
 * @retval int value representing the power state.
 */
int get_power_state(){
	if (power_state == POWER_STATE_ACTIVE){
		return 1;
	}
	return 0;
}



/**
 * @brief Checks the current power state of the LCD, if active updates a value given a column in the first row.
 * @note This function only prints on the LCD's active state.
 */
void power_print(int32_t value, uint8_t col){
	if (get_power_state()==1) {
		LCD_update_value(0,col, value);
		sendInt32OverUSART(value);
	}
}

