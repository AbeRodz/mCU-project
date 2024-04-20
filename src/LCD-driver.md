# LCD-driver


## Prototypes

The following are the internal prototypes used in the creation of the driver.

### Initialization
```c
/**
 * @brief LCD initializer, sends the necessary commands to initialize the LCD in 4 bit mode.
 */
void LCD_init(void);
```
### LCD send data

```c
/**
 * @brief Sends and prints chars onto the LCD.
 * @note The LCD must be initialized.
 */
void LCD_send_txt(uint8_t *txt);

/**
 * @brief Sends a int32 value onto the LCD.
 */
void LCD_send_int32(int32_t *number);

/**
 * @brief Updates a changing value on the LCD without clearing the whole display, e.g sensor read values.
 * @note Using this function avoids screen flickering cause via clearing. This function is also used for int32_t values for this specific case.
 */
void LCD_update_value(uint8_t row, uint8_t col, int32_t value);

```
### LCD control
```c
/**
 * @brief Clears/wipes out the LCD.
 */
void LCD_clear();

/**
 * @brief Sets the cursor position given a row and a column.
 * @note this function only works for a 16x2 LCD.
 */
void LCD_setCursorPos(uint8_t row, uint8_t col);
/**
 * @brief Writes n number of whitespace values onto the LCD.
 */
void LCD_WriteSpaces(uint8_t count);
```

### Backlight control
```c
/**
 * @brief Turns on/off the backlight of the LCD.
 */
void LCD_backlight_state(_Bool state);
```

### Byte control
```c
/**
 * @brief Sends a byte given the type of command onto the LCD, this makes it capable of write for both control, and data modes.
 */
static void send_byte(uint8_t valor,_Bool type);

/**
 * @brief Sends a nibble given the type of command onto the LCD, this makes it capable of write for both control, and data modes.
 */
static void send_nibble(uint8_t valor,_Bool type);

/**
 * @brief Sends a control type nibble.
 */
static void send_control_nibble(uint8_t bytes);

/**
 * @brief Sends a data type nibble.
 */
static void send_data_nibble(uint8_t bytes);
```