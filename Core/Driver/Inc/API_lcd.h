/*
 * API_lcd.h
 *
 *  Created on: Mar 30, 2024
 *      Author: rodz
 */

#ifndef API_INC_API_LCD_H_
#define API_INC_API_LCD_H_


#include "stm32f4xx_hal.h"
#include "API_lcd_port.h"

#define CONTROL_CMD 0
#define DATA_CMD 1

#define EN (1<<2)
#define BL (1<<3)


#define  _4BIT_MODE 0x28
#define DISPLAY_CONTROL (1<<3)
#define RETURN_HOME (1<<1)
#define ENTRY_MODE (1<<2)
#define AUTOINCREMENT (1<<1)
#define DISPLAY_ON 0x04 //(1<<2)
#define DISPLAY_OFF 0x00
#define CLR_LCD 1
#define BACKLIGHT_OFF_COMMAND 0x1D
#define BLINK 0x01
#define LINEA1 0x80
#define LINEA2 0xc0

#define COMANDO_INI1 0x30
#define COMANDO_INI2 0x20

// NIBBLES
#define HIGH_NIBBLE 0xf0
#define LOW_NIBBLE 4




void LCD_init(void);
void LCD_update_value(uint8_t row, uint8_t col, int32_t value);
void LCD_clear(void);

void LCD_setCursorPos(uint8_t row, uint8_t col);
void LCD_backlight_state(_Bool state);
void LCD_send_txt(uint8_t *txt);
void LCD_send_int32(int32_t *number);

#endif /* API_INC_API_LCD_H_ */
