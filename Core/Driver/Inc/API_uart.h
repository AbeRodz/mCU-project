/*
 * API_uart.h
 *
 *  Created on: Apr 13, 2024
 *      Author: rodz
 */

#ifndef DRIVER_INC_API_UART_H_
#define DRIVER_INC_API_UART_H_

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;


void sendInt32OverUSART(int32_t data);

void uart_send(uint8_t tx_buffer);
#endif /* DRIVER_INC_API_UART_H_ */
