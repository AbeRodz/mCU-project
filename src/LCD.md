# LCD

This is the implementation the Hitachi hd44780 LCD display.

---

## Table of Contents
- [Overview](#Overview)
- [Includes](LCD-driver.md#Prototypes)
- [Static Prototypes](LCD-driver.md#Initialization)


---


# Overview

This LCD controller works on I2C, in this case the driver was implemented to be used on the STM32 board.

Now this LCD required the following config:

- 10 MHz clock speed

## Usage Example

You can copy the following code to quickly test the driver:

```c


void main(){
    LCD_init();
    int32_t temp;
    LCD_send_txt((uint8_t *)"Temperature");
    while(1){
        temp = MS5611_read_temp();
        
        LCD_update_value(0,12,temp); // dynamically writes onto LCD

    }
}

```