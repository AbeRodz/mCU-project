/*
 * API_uart.c
 *
 *  Created on: Apr 13, 2024
 *      Author: rodz
 */

#include "API_uart.h"
#include "string.h"
#include "stdio.h"

/**
 * @brief Sends int32 type data via uart.
 */
void sendInt32OverUSART(int32_t data) {

    char str[100];

    int size_len = sprintf(str, "data: %ld \t", (long)data);

    HAL_UART_Transmit(&huart3, (uint8_t *)str, size_len, HAL_MAX_DELAY);
}

/**
 * @brief sends buffer data via uart.
 */
void uart_send(uint8_t tx_buffer){
	HAL_UART_Transmit(&huart3, &tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
}
