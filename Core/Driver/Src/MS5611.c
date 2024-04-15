/*
 * MS5611.c
 *
 *  Created on: Mar 26, 2024
 *      Author: rodz
 */


#include "MS5611.h"
#include "math.h"


static PROM_Data prom_data;

// static prototypes

// PROM
static uint16_t MS5611_Read_PROM_REGISTER(uint8_t reg);
// Chip select
static void MS5611_CS_HIGH(void);
static void MS5611_CS_LOW(void);

// Conversions and ADC
static uint32_t MS5611_ADC_READ();
static void MS5611_Conversion_D1(ConversionCommandD1 command);
static void MS5611_Conversion_D2(ConversionCommandD2 command);

// Variable calculations
static int32_t calculate_temp_diff(PROM_Data * prom_data, uint32_t D2_value );
static int32_t calculate_temperature(PROM_Data * prom_data, uint32_t D2_value);
static int32_t calculate_pressure(PROM_Data * prom_data,uint32_t D1_value , uint32_t D2_value );
static int32_t calculateAltitude(int32_t pressure);
static int32_t celsiusToFahrenheit( int32_t temp_celsius);
// Implementations

static uint16_t MS5611_Read_PROM_REGISTER(uint8_t reg){

	uint8_t byte[3];
	uint16_t return_value;

	MS5611_CS_LOW();
	sendRead(reg, byte);
	//HAL_SPI_TransmitReceive(&hspi1, &reg, byte, 3, SPI_TIMEOUT);
	MS5611_CS_HIGH();

	return_value = ((uint16_t)byte[1]<<8) | (byte[2]);
	return return_value;
}



static void MS5611_CS_HIGH(void){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

static void MS5611_CS_LOW(void){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
}

int MS5611_write(uint8_t bytes){
	//MS5611_CS_LOW();
	if (send(bytes)!= HAL_OK) return 1;
	//MS5611_CS_HIGH();
	return 0;
}

int MS5611_read(uint8_t bytes){
	if (read(bytes)!= HAL_OK) return 1;
	return 0;
}

/**
 * @brief MS5611 constructor, handles sensor reset, and prom read.
 */
void MS5611_init(){

	uint8_t reset = RESET_CMD;
	MS5611_CS_LOW();
	//HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 0);
	HAL_SPI_Transmit(&hspi1, &reset, 1, 20);

	HAL_Delay(3);
	MS5611_CS_HIGH();
	//HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
	HAL_Delay(10);

	for (uint8_t i = 0; i < 6; i++) {

		switch (i) {
		case 0: prom_data.C1 = MS5611_Read_PROM_REGISTER(CMD_PROM_C1); break;
		case 1: prom_data.C2 = MS5611_Read_PROM_REGISTER(CMD_PROM_C2); break;
		case 2: prom_data.C3 = MS5611_Read_PROM_REGISTER(CMD_PROM_C3); break;
		case 3: prom_data.C4 = MS5611_Read_PROM_REGISTER(CMD_PROM_C4); break;
		case 4: prom_data.C5 = MS5611_Read_PROM_REGISTER(CMD_PROM_C5); break;
		case 5: prom_data.C6 = MS5611_Read_PROM_REGISTER(CMD_PROM_C6); break;
		default: break;
		}
	}
}


/**
 * @brief Reads real temperature from the sensor using internal processes defined on the datasheet.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 */
int32_t MS5611_read_temp(){
	MS5611_CS_LOW();
	MS5611_Conversion_D2( CONVERT_D2_OSR_256);
	MS5611_CS_HIGH();

	//HAL_Delay(10);
	uint32_t D2_value = MS5611_ADC_READ();

	int32_t T = calculate_temperature(&prom_data,D2_value);

	return T;
}

int32_t MS5611_read_temp_fahrenheit(){
	int32_t temp = MS5611_read_temp();
	int32_t temp_f =  celsiusToFahrenheit(temp);
	return temp_f;
}
/**
 * @brief Reads real pressure from the sensor using internal processes defined on the datasheet.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 */
int32_t MS5611_read_pressure(){
	MS5611_CS_LOW();
	MS5611_Conversion_D1(CONVERT_D1_OSR_256);
	MS5611_CS_HIGH();

	uint32_t D1_value = MS5611_ADC_READ();

	//HAL_Delay(10);

	MS5611_CS_LOW();
	MS5611_Conversion_D2(CONVERT_D2_OSR_256);
	MS5611_CS_HIGH();
	uint32_t D2_value = MS5611_ADC_READ();
	//int32_t T = calculate_temperature(&prom_data,D2_value);
	int32_t pressure = calculate_pressure(&prom_data,D1_value,D2_value);

	return pressure;
}

/**
 * @brief Reads real pressure from the sensor and performs calculations too get altitude in meters.
 * ituses the MS5611_read_pressure function to capture the pressure.
 */
int32_t MS5611_read_altitude(){

	int32_t pressure =  MS5611_read_pressure();
	int32_t altitude =  calculateAltitude(pressure);
	return altitude;
}

/**
 * @brief Executes the internal ADC read command,containing the temperature or pressure raw data.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 */
static uint32_t MS5611_ADC_READ(){
	uint8_t adc = ADC_READ;
	MS5611_CS_LOW();
	uint8_t result_buffer[4];
	HAL_StatusTypeDef ret;
	uint32_t return_value;

	ret= HAL_SPI_TransmitReceive(&hspi1,&adc, result_buffer, 4, 50);
	if(ret != HAL_OK)
	{
		MS5611_CS_HIGH();
		//HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
	}

	return_value = ((uint32_t)result_buffer[1]<<16) | (uint32_t)(result_buffer[2]<<8) | (result_buffer[3]);
	MS5611_CS_HIGH();
	//HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
	return return_value;
}

/**
 * @brief Executes pressure conversion sequence (D1).
 * @param ConversionCommandD1 pressure conversion command, it defines the ADC's internal sample rate
 * @note The higher the sample rate, the longer it takes for the sensor to return raw data.
 */
static void MS5611_Conversion_D1(ConversionCommandD1 command){

	MS5611_write(command);
	HAL_Delay(10);
}

/**
 * @brief Executes temperature conversion sequence (D2).
 * @param ConversionCommandD2 temperature conversion command, it defines the ADC's internal sample rate
 * @note The higher the sample rate, the longer it takes for the sensor to return raw data.
 */
static void MS5611_Conversion_D2(ConversionCommandD2 command){

	MS5611_write(command);
	HAL_Delay(10);
}


/**
 * @brief Calculates temperature difference from the prom value, and the raw temperature.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int32_t
 */
static int32_t calculate_temp_diff(PROM_Data * prom_data, uint32_t D2_value ){

	int32_t dT = D2_value - ((long)prom_data->C5 * 256);
	return dT;
}

/**
 * @brief Calculates actual temperature using data extracted from the prom,
 * uses the raw temperature, to calculate the temperature difference according to the datasheet.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int64_t
 */
static int32_t calculate_temperature(PROM_Data * prom_data, uint32_t D2_value ){


	int32_t dT = calculate_temp_diff(prom_data,D2_value );
	int64_t Temp = 2000 + ((int64_t)dT * prom_data->C6 )/ 8388608;
	return Temp;
}

static int32_t celsiusToFahrenheit( int32_t temp_celsius) {
    return (temp_celsius * 9 / 5) + 32;
}

/**
 * @brief Calculates actual pressure using data extracted from the prom,
 * uses the raw temperature, to calculate the temperature difference according to the datasheet.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D1_value(pressure) raw value of the temperature, extracted from the conversion sequence.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int64_t
 */
static int32_t calculate_pressure(PROM_Data * prom_data,uint32_t D1_value , uint32_t D2_value ){
	//OFF = OFFT1 + TCO * dT = C2 * 216 + (C4 * dT ) / 27
	int32_t dT = calculate_temp_diff(prom_data,D2_value );
	int64_t OFF = ((int64_t)prom_data->C2 * 65536) + ((int64_t)prom_data->C4 * dT)/128;
	//OFF = (int64_t)prom[1] * 65536 + ((int64_t)prom[3] * dT ) / 128;
	//SENS = (int64_t)prom[0] * 32768 + ((int64_t)prom[2] * dT) / 256;
	//SENS = SENST1 + TCS * dT = C1 * 2 15 + (C3 * dT ) / 28
	int64_t SENS = ((int64_t)prom_data->C1*32768) + ((int64_t)prom_data->C3 * dT)/256;

	//P = D1 * SENS - OFF = (D1 * SENS / 2 21 - OFF) / 2 15
	int64_t P = (D1_value * (SENS/ 2097152)- OFF)/32768;

	return (int32_t)P;
}

static int32_t calculateAltitude(int32_t pressure) {

	int32_t altitude = 145366.45 * (1.0 - pow((((pressure)/100)/ SEA_LEVEL_PRESSURE), 0.1903));
    return altitude * 0.3048;
}

