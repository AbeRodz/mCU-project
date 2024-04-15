/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : API/Inc/API_delay.h
  * @brief          : Header for API_delay.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DELAY_H
#define __API_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
#include <stdbool.h>


/* Exported types ------------------------------------------------------------*/

typedef uint32_t tick_t;
typedef bool bool_t;


typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

typedef struct{
	tick_t duration;
	float dutyCycle;
	uint16_t led;
	uint32_t counter;
}duty_cycle;


void Error_Handler(void);
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
void periodicBlinkInit(delay_t *delays,duty_cycle * duties, size_t numLed);
void periodicBlink(delay_t *delays,duty_cycle * duties, size_t numLed, uint32_t counter);
void blink(delay_t *delay,duty_cycle * duty);


#ifdef __cplusplus
}
#endif

#endif /* __API_dELAY_H */
