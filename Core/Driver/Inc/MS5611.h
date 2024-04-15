/*
 * MS5611.h
 *
 *  Created on: Mar 26, 2024
 *      Author: rodz
 */

#ifndef MS5611_INC_MS5611_H_
#define MS5611_INC_MS5611_H_


#include "port.h"

#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define RESET_CMD 0x1E
#define ADC_READ 0x00;
#define PROM_READ 0xA0;

#define SPI_TIMEOUT 50

#define CMD_PROM_C1 0xA2
#define CMD_PROM_C2 0xA4
#define CMD_PROM_C3 0xA6
#define CMD_PROM_C4 0xA8
#define CMD_PROM_C5 0xAA
#define CMD_PROM_C6 0xAC

#define SEA_LEVEL_PRESSURE 1013.25

extern SPI_HandleTypeDef hspi1;

typedef struct {
	uint8_t Command;
	uint32_t ConversionTime;

} OSRConfig;

typedef enum {
    CONVERT_D1_OSR_256 = 0x40,    // Convert D1 (OSR=256)
    CONVERT_D1_OSR_512 = 0x42,    // Convert D1 (OSR=512)
    CONVERT_D1_OSR_1024 = 0x44,   // Convert D1 (OSR=1024)
    CONVERT_D1_OSR_2048 = 0x46,   // Convert D1 (OSR=2048)
    CONVERT_D1_OSR_4096 = 0x48    // Convert D1 (OSR=4096)
} ConversionCommandD1;

typedef enum {
    CONVERT_D2_OSR_256 = 0x50,    // Convert D2 (OSR=256)
    CONVERT_D2_OSR_512 = 0x52,    // Convert D2 (OSR=512)
    CONVERT_D2_OSR_1024 = 0x54,   // Convert D2 (OSR=1024)
    CONVERT_D2_OSR_2048 = 0x56,   // Convert D2 (OSR=2048)
    CONVERT_D2_OSR_4096 = 0x58    // Convert D2 (OSR=4096)
} ConversionCommandD2;


typedef struct {
    uint16_t C1;  // Pressure sensitivity PSens
    uint16_t C2;  // Pressure offset OFF
    uint16_t C3;  // Temperature coefficient of pressure sensitivity TCS
    uint16_t C4;  // Temperature coefficient of pressure offset TCO
    uint16_t C5;  // Reference temperature TRef
    uint16_t C6;  // Temperature coefficient of the temperature TEMPSENS
} PROM_Data;


void MS5611_init();

int32_t MS5611_read_temp();
int32_t MS5611_read_temp_fahrenheit();
int32_t MS5611_read_pressure();
int32_t MS5611_read_altitude();
#endif /* MS5611_INC_MS5611_H_ */
