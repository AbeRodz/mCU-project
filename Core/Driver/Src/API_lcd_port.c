/*
 * API_lcd_port.c
 *
 *  Created on: Apr 17, 2024
 *      Author: rodz
 */
#include "API_lcd_port.h"


/**
 * @brief Sends bytes via I2C API to the LCD slave address.
 */
void LCD_write(uint8_t bytes){
	i2c_send(LCD_ADDRESS,bytes);
}
