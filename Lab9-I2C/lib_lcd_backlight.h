/* ========================================================================== --
  
  Anthony TROUVE - 20501476

-- ========================================================================== */

#ifndef LIB_LCD_BACKLIGHT_H
#define LIB_LCD_BACKLIGHT_H 

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "periph/i2c.h"
#include "xtimer.h"

/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
#define I2C_PORT  I2C_DEV(0)

#define BCK_ADDR      0x62 
#define LCD_ADDR      0x3E 

#define BLUE_REG      0x02 
#define GREEN_REG     0x03 
#define RED_REG       0x04 

#define CMD_REG       0x80 
#define DATA_REG      0x40 

// commands 
#define LCD_CLEARDISPLAY     0x01 
#define LCD_DISPLAYCONTROL   0x08 
#define LCD_FUNCTIONSET      0x20 

// flags for display on/off control 
#define LCD_DISPLAYON        0x04 
#define LCD_DISPLAYOFF       0x00 

// flag for entry mode 
#define LCD_ENTRYLEFT 0x02 

// flags for function set 
#define LCD_8BITMODE 0x10 
#define LCD_2LINE    0x08 
#define LCD_5x10DOTS 0x04 

/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */

/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int lcd_init(i2c_t bus); 

int lcd_setRGB(i2c_t bus,unsigned char Red,unsigned char Green,unsigned char Blue); 

int lcd_sendcmd(i2c_t bus,unsigned char cmd); 

int lcd_displayOn(i2c_t bus); 

int lcd_clear(i2c_t bus); 

int lcd_putch(i2c_t bus,unsigned char Car); 

int lcd_puts(i2c_t bus,unsigned char *pCar); 

#endif /* LIB_LCD_BACKLIGHT_H */