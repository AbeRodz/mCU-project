
---
## Prototypes

The following are the internal prototypes used in the creation of the driver.


### Initialization
```c
/**
 * @brief MS5611 initializer, handles sensor reset sequence, and reads factory settings from the prom to perform calibration.
 */
void MS5611_init();
```
### SPI interface
```c
/**
 * @brief Sends bytes via SPI API.
 */
int MS5611_write(uint8_t bytes);

/**
 * @brief Receives bytes via SPI API.
 */
int MS5611_read(uint8_t bytes);

```

### Read
```c
/**
 * @brief Reads real temperature from the sensor using internal processes defined on the datasheet.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 */
int32_t MS5611_read_temp();

/**
 * @brief Reads real temperature from the sensor in Fahrenheit units.
 */
int32_t MS5611_read_temp_fahrenheit();

/**
 * @brief Reads real pressure from the sensor using internal processes defined on the datasheet.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 */
int32_t MS5611_read_pressure();

/**
 * @brief Reads real pressure from the sensor and performs calculations to get altitude in meters.
 */
int32_t MS5611_read_altitude();
```
### PROM
```c
/**
 * @brief Reads from the prom memory the factory settings according to the passed register
 * the register are the values C1 to C6, check the PROM_Data struct to check each value definition.
 * @retval uint16_t containin the prom value of the passed register.
 * @note First the reset sequence must be performed to receive the prom data.
 */
static uint16_t MS5611_Read_PROM_REGISTER(uint8_t reg);
```
### Chip Select
```c
/**
 * @brief Sets chip select to high.
 */
static void MS5611_CS_HIGH(void);
/**
 * @brief Sets chip select to low.
 */
static void MS5611_CS_LOW(void);
```

### Conversions and ADC
```c
/**
 * @brief Executes the internal ADC read command, containing the temperature or pressure raw data.
 * it is expected to receive 24 bits from the IC, so it must be casted onto an uint32_t.
 * @note First it a conversion command must be executed in order to receive data.
 * @retval uint32_t with raw measurement value.
 */
static uint32_t MS5611_ADC_READ();

/**
 * @brief Executes pressure conversion sequence (D1).
 * @param ConversionCommandD1 pressure conversion command, it defines the ADC's internal sample rate
 * @note The higher the sample rate, the longer it takes for the sensor to return raw data.
 */
static void MS5611_Conversion_D1(ConversionCommandD1 command);

/**
 * @brief Executes temperature conversion sequence (D2).
 * @param ConversionCommandD2 temperature conversion command, it defines the ADC's internal sample rate
 * @note The higher the sample rate, the longer it takes for the sensor to return raw data.
 */
static void MS5611_Conversion_D2(ConversionCommandD2 command);
```
### Variable Calculations
```c
/**
 * @brief Calculates temperature difference from the prom value, and the raw temperature.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int32_t
 */
static int32_t calculate_temp_diff(PROM_Data * prom_data, uint32_t D2_value );

/**
 * @brief Calculates actual temperature using data extracted from the prom,
 * uses the raw temperature, to calculate the temperature difference according to the datasheet.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int32_t
 */
static int32_t calculate_temperature(PROM_Data * prom_data, uint32_t D2_value);

/**
 * @brief Calculates the temperature in fahrenheit units given the temperature in celsius.
 * @param temp_celsius temperature value obtained from the sensor.
 * @retval int32_t converted temperature.
 */
static int32_t celsiusToFahrenheit(int32_t temp_celsius);
/**
 * @brief Calculates actual pressure using data extracted from the prom,
 * uses the raw temperature, to calculate the temperature difference according to the datasheet.
 * @param PROM_Data pointer to a populated struct with data from the prom.
 * @param D1_value(pressure) raw value of the temperature, extracted from the conversion sequence.
 * @param D2_value(temperature) raw value of the temperature, extracted from the conversion sequence.
 * @retval int32_t
 */
static int32_t calculate_pressure(PROM_Data * prom_data,uint32_t D1_value , uint32_t D2_value );
/**
 * @brief Calculates the altitude given the pressure.
 * @param pressure value obtained from the sensor.
 * @note formula obtained from https://www.weather.gov/media/epz/wxcalc/pressureAltitude.pdf
 * @retval int32_t
 */
static int32_t calculateAltitude(int32_t pressure);

```