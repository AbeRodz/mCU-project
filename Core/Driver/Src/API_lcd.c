/*
 * API_lcd.c
 *
 *  Created on: Mar 30, 2024
 *      Author: rodz
 */

#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"

#include "API_I2C.h"
#include "API_lcd.h"

// PROTOTYPES
static void send_nibble(uint8_t valor,_Bool type);
static void send_byte(uint8_t valor,_Bool type);
static void send_control_nibble(uint8_t bytes);
static void send_data_nibble(uint8_t bytes);
static const uint8_t LCD_INIT_CMD[]={
		_4BIT_MODE,DISPLAY_CONTROL,RETURN_HOME,ENTRY_MODE+AUTOINCREMENT,DISPLAY_CONTROL+DISPLAY_ON,CLR_LCD
};

/**
 * @brief LCD initializer, sends the necessary commands to initialize the LCD in 4 bit mode.
 */
void LCD_init(void){


	HAL_Delay(20);
	send_control_nibble(COMANDO_INI1);


	HAL_Delay(10);
	send_control_nibble(COMANDO_INI1);
	HAL_Delay(1);

	send_control_nibble(COMANDO_INI1);
	send_control_nibble(COMANDO_INI2);
	 for(uint8_t i=0;i<sizeof(LCD_INIT_CMD);i++)send_byte(LCD_INIT_CMD[i], CONTROL_CMD);
	HAL_Delay(2);

}

/**
 * @brief Updates a changing value on the LCD without clearing the whole display, e.g sensor read values.
 * @note Using this function avoids screen flickering cause via clearing. This function is also used for int32_t values for this specific case.
 */
void LCD_update_value(uint8_t row, uint8_t col, int32_t value) {
    char tempStr[12];

    // Convert the new int32_t to a string
    snprintf(tempStr, sizeof(tempStr), "%ld", value);

    // Set cursor position to the start of the number
    LCD_setCursorPos(row, col);

    // Clear the old number by printing spaces
    LCD_send_txt((uint8_t*)(' '));

    // Set cursor position to the start of the number again
    LCD_setCursorPos(row, col);
    LCD_send_txt((uint8_t *)tempStr);
    HAL_Delay(50);
}

/**
 * @brief Sends and prints chars onto the LCD.
 * @note The LCD must be initialized.
 */
void LCD_send_txt(uint8_t *txt){
	while(*txt)send_byte(*txt++,DATA_CMD);

}
/**
 * @brief Sends a int32 value onto the LCD.
 */
void LCD_send_int32(int32_t *number){

    char buffer[10];
    snprintf(buffer,10,"%ld",*number);
    LCD_send_txt((uint8_t *)buffer);
}


/**
 * @brief Writes n number of whitespace values onto the LCD.
 */
void LCD_WriteSpaces(uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
    	LCD_send_txt((uint8_t *)' ');

    }
}


/**
 * @brief Clears/wipes out the LCD.
 */
void LCD_clear(){

	send_control_nibble(CLR_LCD&HIGH_NIBBLE);
	send_control_nibble(CLR_LCD<<LOW_NIBBLE);
}

/**
 * @brief Sets the cursor position given a row and a column.
 * @note this function only works for a 16x2 LCD.
 */
void LCD_setCursorPos(uint8_t row, uint8_t col) {
    uint8_t address = 0;

    // Calculate the address based on row and column
    switch (row) {
        case 0:
            address = LINEA1 +  row + col;
            break;
        case 1:
            address = LINEA2 + col; // 0x80 + (row*40) + 24 + col
            break;

    }
    send_byte(address, CONTROL_CMD);

 }

/**
 * @brief Turns on/off the backlight of the LCD.
 */
void LCD_backlight_state(_Bool state){

	if (state==0){
		send_control_nibble(DISPLAY_OFF);
		HAL_Delay(1);
		send_data_nibble(BACKLIGHT_OFF_COMMAND);
	}else{
		send_control_nibble(DISPLAY_ON);
		HAL_Delay(1);
		send_data_nibble(~BACKLIGHT_OFF_COMMAND);
	}
}

/**
 * @brief Sends a byte given the type of command onto the LCD, this makes it capable of write for both control, and data modes.
 */
static void send_byte(uint8_t valor,_Bool type){
	send_nibble(valor&HIGH_NIBBLE, type);
	send_nibble(valor<<LOW_NIBBLE, type);

}

/**
 * @brief Sends a nibble given the type of command onto the LCD, this makes it capable of write for both control, and data modes.
 */
static void send_nibble(uint8_t valor,_Bool type){

	LCD_write(valor+type+EN+BL);
	HAL_Delay(1);
	LCD_write(valor+type+BL);
	HAL_Delay(1);
}

/**
 * @brief Sends a control type nibble.
 */
static void send_control_nibble(uint8_t bytes){
	send_nibble(bytes, CONTROL_CMD);


}

/**
 * @brief Sends a data type nibble.
 */
static void send_data_nibble(uint8_t bytes){
	send_nibble(bytes, DATA_CMD);


}



