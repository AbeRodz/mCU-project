/*
 * API_delay.c
 *
 *  Created on: Mar 14, 2024
 *      Author: rodz
 */


/* USER CODE END 0 */
#include "API_delay.h"
#include <stdlib.h>
#define DEFAULT_DELAY 100 // default delay constant in milliseconds
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
 * @brief Inits an array of leds to blink sequentially.
 * Function that initiates sequentially an array of leds.
 * @param delays Pointer to an array of defined delays.
 * @param duties Pointer to an array of duty cycles per led.
 * @param numLed length of the array of leds.
 */
void periodicBlinkInit(delay_t *delays,duty_cycle * duties, size_t numLed){


	for (uint8_t i = 0; i < numLed; i++){
		tick_t duration = (tick_t)(duties[i].duration)*(duties[i].dutyCycle);
		BSP_LED_Init(duties[i].led);
		delayInit(&delays[i], duration);
		uint32_t dutyCounter = duties[i].counter*2;
		duties[i].counter = dutyCounter;
	}

}

/**
 * @brief Performs blinking periodically and sequentially given an array of leds.
 * Function that blinks sequentially an array of leds.
 * @param delays Pointer to an array of defined delays.
 * @param duties Pointer to an array of duty cycles per led.
 * @param numLed length of the array of leds.
 * @param counter a counter of the number of times a led should blink.
 */
void periodicBlink(delay_t *delays,duty_cycle * duties, size_t numLed, uint32_t counter){
	for (uint8_t i = 0; i < numLed; i++){
		while (duties[i].counter>= counter && counter > 0){
			if (delayRead(&delays[i])){

				BSP_LED_Toggle(duties[i].led);
				duties[i].counter--;

			}
		}
	}
}

/**
 * @brief Performs blinking on demand given a leds.
 * Function that blinks sequentially an array of leds.
 * @param delays Pointer to an array of defined delays.
 * @param duties Pointer to an array of duty cycles per led.
 */
void blink(delay_t *delay,duty_cycle * duty){

	if (delayRead(delay)){

		BSP_LED_Toggle(duty->led);
	}
}


/**
 * @brief Inits a delay with a specified duration.
 * Function that initiates a delay.
 * @param delay Pointer to a defined delay struct.
 * @param duration in milliseconds.
 * @note if duration is 0 or a negative number, it defaults to DEFAULT_DELAY.
 */
void delayInit(delay_t *delay, tick_t duration){
	if (duration <= 0){
		duration = DEFAULT_DELAY;
	}
	delay->duration = duration;
	delay->running = false;
	delay->startTime = 0;

}

/**
 * @brief Checks if an specific delay has elapsed.
 * Function that checks the current status of a delay and updates its values.
 * @param delay Pointer to a defined delay struct.
 * @retval bool indicating running state.
 */
bool_t delayRead(delay_t *delay){

	tick_t currentTime = HAL_GetTick();
	bool isRunning = delay->running;

	if (isRunning && (currentTime - delay->startTime >= delay->duration)){
		delay->running = false;
		return true;
	}

	if (!isRunning) {
		delay->running = true;
		delay->startTime = currentTime;

	}
	return false;
}



