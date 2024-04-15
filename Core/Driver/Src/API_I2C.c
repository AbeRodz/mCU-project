/*
 * API_delay.c
 *
 *  Created on: Mar 26, 2024
 *      Author: rodz
 */


/* USER CODE END 0 */
//#include "stm32f4xx_hal.h"
#include "API_I2C.h"

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/*
bool MX_I2C_Init(){
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	//GPIO_I2C();
    if (HAL_I2C_Init(&hi2c1)!= HAL_OK){
    	return false;
    }
    	return true;
}

*/
HAL_StatusTypeDef i2c_send(uint16_t tgt_address, uint8_t tx_buffer){
//if(HAL_I2C_Master_Transmit (&hi2c1,LCD_DIR<<1,&valor, sizeof(valor),HAL_MAX_DELAY)!=HAL_OK)Error_Handler();
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, tgt_address<<1, &tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
	if (status != HAL_OK){
		return HAL_ERROR;
	}
	return status;
}

HAL_StatusTypeDef i2c_read(uint16_t tgt_address, uint8_t rx_buffer){

	HAL_StatusTypeDef status = HAL_I2C_Master_Receive(&hi2c1, tgt_address, &rx_buffer, sizeof(rx_buffer), HAL_MAX_DELAY);
	if (status != HAL_OK){
		return HAL_ERROR;
	}
	return status;
}

/*

I2C_interface i2c_constructor(void) {
	I2C_interface i2c_interface = {
	    .init = MX_I2C_Init,
	    .i2c_read = i2c_read,
	    .i2c_send = i2c_send,
	};

	return i2c_interface;
}
*/
