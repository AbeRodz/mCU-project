/*
 * API_lcd_port.h
 *
 *  Created on: Apr 17, 2024
 *      Author: rodz
 */

#ifndef DRIVER_INC_API_LCD_PORT_H_
#define DRIVER_INC_API_LCD_PORT_H_

#include "API_I2C.h"

#define LCD_ADDRESS 0x27


void LCD_write(uint8_t bytes);

#endif /* DRIVER_INC_API_LCD_PORT_H_ */
