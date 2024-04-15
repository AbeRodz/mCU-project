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
static void SendByte(uint8_t valor,_Bool type);
static void send_control_nibble(uint8_t bytes);
static void send_data_nibble(uint8_t bytes);
static const uint8_t LCD_INIT_CMD[]={
		_4BIT_MODE,DISPLAY_CONTROL,RETURN_HOME,ENTRY_MODE+AUTOINCREMENT,DISPLAY_CONTROL+DISPLAY_ON,CLR_LCD
};


LCD_StatusTypeDef LCD_init(void){


	HAL_Delay(20);
	send_control_nibble(COMANDO_INI1);


	HAL_Delay(10);
	send_control_nibble(COMANDO_INI1);
	HAL_Delay(1);

	send_control_nibble(COMANDO_INI1);
	send_control_nibble(COMANDO_INI2);
	 for(uint8_t i=0;i<sizeof(LCD_INIT_CMD);i++)SendByte(LCD_INIT_CMD[i], CONTROL_CMD);
	HAL_Delay(2);
	return LCD_OK;
}

void LCD_update_value(uint8_t row, uint8_t col, int32_t value) {
    char tempStr[12];

    // Convert the new int32_t to a string
    snprintf(tempStr, sizeof(tempStr), "%ld", value);

    // Set cursor position to the start of the number
    LCD_SetCursorPos(row, col);

    // Clear the old number by printing spaces
    LCD_send_txt((uint8_t*)(' '));

    // Set cursor position to the start of the number again
    LCD_SetCursorPos(row, col);
    LCD_send_txt((uint8_t *)tempStr);
    HAL_Delay(50);
}


void LCD_send_txt(uint8_t *txt){
	while(*txt)SendByte(*txt++,DATA_CMD);
	//SendByte(txt,DATA_CMD);
}
void LCD_send_int32(int32_t *number){

    char buffer[10];
    snprintf(buffer,10,"%ld",*number);
    LCD_send_txt((uint8_t *)buffer);
}


void SendByte(uint8_t valor,_Bool type){
	send_nibble(valor&HIGH_NIBBLE, type);
	send_nibble(valor<<LOW_NIBBLE, type);

}

void LCD_WriteSpaces(uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
    	LCD_send_txt((uint8_t *)' ');

    }
}

LCD_StatusTypeDef LCD_write(uint8_t bytes){
	if (i2c_send(LCD_ADDRESS,bytes)!= HAL_OK) return LCD_ERROR;
	return LCD_OK;
}

void PosCaracHLcd(uint8_t posH){
	SendByte(posH | LINEA1, CONTROL_CMD);
}

void LCD_clear(){

	send_control_nibble(CLR_LCD&HIGH_NIBBLE);
	send_control_nibble(CLR_LCD<<LOW_NIBBLE);
}
void LCD_SetCursorPos(uint8_t row, uint8_t col) {
    uint8_t address = 0;

    // Calculate the address based on row and column
    switch (row) {
        case 0:
            address = LINEA1 +  row + col;
            break;
        case 1:
            address = LINEA2 + col; // 0x80 + (row*40) + 24 + col
            break;
        // Add cases for additional rows if needed
    }
    SendByte(address, CONTROL_CMD);
   //PosCaracHLcd(address);
 }


static void send_nibble(uint8_t valor,_Bool type){

	LCD_write(valor+type+EN+BL);
	HAL_Delay(1);
	LCD_write(valor+type+BL);
	HAL_Delay(1);
}

static void send_control_nibble(uint8_t bytes){
	send_nibble(bytes, CONTROL_CMD);


}

static void send_data_nibble(uint8_t bytes){
	send_nibble(bytes, DATA_CMD);


}

void backlight_state(_Bool state){

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
//TODO
void blink_state(_Bool state){

	if (state==0){
		send_control_nibble(DISPLAY_OFF);
		HAL_Delay(1);
		send_data_nibble(BLINK);
	}else{
		send_control_nibble(DISPLAY_ON);
		HAL_Delay(1);
		send_data_nibble(~BLINK);
	}
}


