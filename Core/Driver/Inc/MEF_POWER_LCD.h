/*
 * MEF_POWER_LCD.h
 *
 *  Created on: Apr 15, 2024
 *      Author: rodz
 */

#ifndef DRIVER_INC_MEF_POWER_LCD_H_
#define DRIVER_INC_MEF_POWER_LCD_H_

#include "API_lcd.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

#define LOW_POWER_TIMEOUT 5000 // Default power timeout

typedef enum {
    POWER_STATE_ACTIVE,
    POWER_STATE_LOW_POWER,
} PowerState_t;


void updatePowerState();
int get_power_state();

void power_print(int32_t value, uint8_t col);
#endif /* DRIVER_INC_MEF_POWER_LCD_H_ */
