/*
 * API_delay.c
 *
 *  Created on: Mar 26, 2024
 *      Author: rodz
 */


/* USER CODE END 0 */
//#include "stm32f4xx_hal.h"
#include <MS5611_port.h>

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/*
bool MX_SPI1_Init(SPI_HandleTypeDef *hspi)
{
    hspi->Instance = SPI4;
    hspi->Init.Mode = SPI_MODE_MASTER;
    hspi->Init.Direction = SPI_DIRECTION_2LINES;
    hspi->Init.DataSize = SPI_DATASIZE_8BIT;
    hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi->Init.NSS = SPI_NSS_SOFT;
    hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi->Init.TIMode = SPI_TIMODE_DISABLE;
    hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi->Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(hspi) != HAL_OK){
    	return false;
    }else{
    	 //__HAL_SPI_ENABLE(hspi);
    	return true;
    }

}

*/

/**
 * @brief sends and receives data onto both a transmit and receive buffers, via SPI.
 * @note First the CS pin must be triggered to expect the correct functionality.
 */
HAL_StatusTypeDef sendRead(uint8_t tx_buffer, uint8_t *rx_buffer){
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi1, &tx_buffer, rx_buffer,  sizeof(rx_buffer), HAL_MAX_DELAY);
	if (status != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}

/**
 * @brief sends data given a transmit buffer, via SPI.
 * @note First the CS pin must be triggered to expect the correct functionality.
 */
HAL_StatusTypeDef send( uint8_t tx_buffer){

	HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, &tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
	if (status != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}

/**
 * @brief sends data given a receive buffer, via SPI.
 * @note First the CS pin must be triggered to expect the correct functionality.
 */
HAL_StatusTypeDef read( uint8_t rx_buffer){

	HAL_StatusTypeDef status = HAL_SPI_Receive(&hspi1, &rx_buffer, sizeof(rx_buffer),HAL_MAX_DELAY);
	if (status != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}
/*
SPI_interface spi_constructor(void) {
	SPI_interface spi_interface = {
	    .init = MX_SPI1_Init,
	    .read = read,
	    .send = send,
	};

	return spi_interface;
}*/
