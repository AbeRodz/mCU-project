/*
 * API_I2C.h
 *
 *  Created on: Mar 30, 2024
 *      Author: rodz
 */

#ifndef API_API_I2C_H_
#define API_API_I2C_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"


extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef i2c_read(uint16_t tgt_address, uint8_t rx_buffer);
HAL_StatusTypeDef i2c_send(uint16_t tgt_address, uint8_t tx_buffer);






#endif /* API_API_I2C_H_ */
