/*
 * API_uart.c
 *
 *  Created on: Apr 13, 2024
 *      Author: rodz
 */

#include "API_uart.h"




void sendInt32OverUSART(int32_t data) {
    uint8_t buffer[4]; // Assuming 8 bytes for int64
    for(int i = 0; i < 4; i++) {
        buffer[i] = (data >> (8 * i)) & 0xFF; // Extract each byte
    }
    //i2c_send(buffer);
    HAL_UART_Transmit(&huart3, buffer, 4, HAL_MAX_DELAY); // Transmit the bytes
}


void uart_send(uint8_t tx_buffer){
	HAL_UART_Transmit(&huart3, &tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
}
