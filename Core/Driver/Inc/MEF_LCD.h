/*
 * API_debounce.h
 *
 *  Created on: Mar 21, 2024
 *      Author: rodz
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "API_delay.h"
#include "API_lcd.h"
#include "MS5611.h"

#define LONG_PRESS_THRESHOLD 1000
#define MULTIPLE_PRESS_THRESHOLD 500

typedef enum {
    DISPLAY_MENU, // Menu
    DISPLAY_TEMP, // temp
	DISPLAY_TEMP_F, // TEMP F
	DISPLAY_PRESS, // PRESSURE
	DISPLAY_ALT, // ALTITUDE
	DISPLAY_STANDBY,
} DisplayState_t;

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
BUTTON_LONG_PRESS
} debounceState_t;

void menu_init(void);
void update_display_state();

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe encender el LED
void buttonReleased();		// debe apagar el LED


#endif /* API_INC_API_DEBOUNCE_H_ */
