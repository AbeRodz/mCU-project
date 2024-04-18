/*
 * port.h
 *
 *  Created on: Mar 26, 2024
 *      Author: rodz
 */

#ifndef MS5611_INC_PORT_H_
#define MS5611_INC_PORT_H_
#include "stm32f4xx_hal.h"

#include <stdbool.h>



extern SPI_HandleTypeDef hspi1;



HAL_StatusTypeDef sendRead(uint8_t tx_buffer, uint8_t *rx_buffer);
HAL_StatusTypeDef read(uint8_t rx_buffer);
HAL_StatusTypeDef send(uint8_t tx_buffer);


#endif /* MS5611_INC_PORT_H_ */
