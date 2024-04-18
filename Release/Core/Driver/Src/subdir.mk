################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Driver/Src/API_I2C.c \
../Core/Driver/Src/API_delay.c \
../Core/Driver/Src/API_lcd.c \
../Core/Driver/Src/API_lcd_port.c \
../Core/Driver/Src/API_uart.c \
../Core/Driver/Src/MEF_LCD.c \
../Core/Driver/Src/MEF_POWER_LCD.c \
../Core/Driver/Src/MS5611.c \
../Core/Driver/Src/MS5611_port.c 

OBJS += \
./Core/Driver/Src/API_I2C.o \
./Core/Driver/Src/API_delay.o \
./Core/Driver/Src/API_lcd.o \
./Core/Driver/Src/API_lcd_port.o \
./Core/Driver/Src/API_uart.o \
./Core/Driver/Src/MEF_LCD.o \
./Core/Driver/Src/MEF_POWER_LCD.o \
./Core/Driver/Src/MS5611.o \
./Core/Driver/Src/MS5611_port.o 

C_DEPS += \
./Core/Driver/Src/API_I2C.d \
./Core/Driver/Src/API_delay.d \
./Core/Driver/Src/API_lcd.d \
./Core/Driver/Src/API_lcd_port.d \
./Core/Driver/Src/API_uart.d \
./Core/Driver/Src/MEF_LCD.d \
./Core/Driver/Src/MEF_POWER_LCD.d \
./Core/Driver/Src/MS5611.d \
./Core/Driver/Src/MS5611_port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Driver/Src/%.o Core/Driver/Src/%.su Core/Driver/Src/%.cyclo: ../Core/Driver/Src/%.c Core/Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/rodz/Documents/uba/mCU-programming/FINAL_TP/Core/Driver/Inc" -I"/home/rodz/Documents/uba/mCU-programming/FINAL_TP/Core/Driver/Src" -I"/home/rodz/Documents/uba/mCU-programming/FINAL_TP/Drivers/BSP/STM32F4xx_Nucleo_144" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Driver-2f-Src

clean-Core-2f-Driver-2f-Src:
	-$(RM) ./Core/Driver/Src/API_I2C.cyclo ./Core/Driver/Src/API_I2C.d ./Core/Driver/Src/API_I2C.o ./Core/Driver/Src/API_I2C.su ./Core/Driver/Src/API_delay.cyclo ./Core/Driver/Src/API_delay.d ./Core/Driver/Src/API_delay.o ./Core/Driver/Src/API_delay.su ./Core/Driver/Src/API_lcd.cyclo ./Core/Driver/Src/API_lcd.d ./Core/Driver/Src/API_lcd.o ./Core/Driver/Src/API_lcd.su ./Core/Driver/Src/API_lcd_port.cyclo ./Core/Driver/Src/API_lcd_port.d ./Core/Driver/Src/API_lcd_port.o ./Core/Driver/Src/API_lcd_port.su ./Core/Driver/Src/API_uart.cyclo ./Core/Driver/Src/API_uart.d ./Core/Driver/Src/API_uart.o ./Core/Driver/Src/API_uart.su ./Core/Driver/Src/MEF_LCD.cyclo ./Core/Driver/Src/MEF_LCD.d ./Core/Driver/Src/MEF_LCD.o ./Core/Driver/Src/MEF_LCD.su ./Core/Driver/Src/MEF_POWER_LCD.cyclo ./Core/Driver/Src/MEF_POWER_LCD.d ./Core/Driver/Src/MEF_POWER_LCD.o ./Core/Driver/Src/MEF_POWER_LCD.su ./Core/Driver/Src/MS5611.cyclo ./Core/Driver/Src/MS5611.d ./Core/Driver/Src/MS5611.o ./Core/Driver/Src/MS5611.su ./Core/Driver/Src/MS5611_port.cyclo ./Core/Driver/Src/MS5611_port.d ./Core/Driver/Src/MS5611_port.o ./Core/Driver/Src/MS5611_port.su

.PHONY: clean-Core-2f-Driver-2f-Src

