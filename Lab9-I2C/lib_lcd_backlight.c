/* ========================================================================== --
  
  Anthony TROUVE - 20501476

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include <string.h>

#include "lib_lcd_backlight.h"

/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   Local macros
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   Local types
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
unsigned char _displayfunction = 0x00; 
unsigned char _displaycontrol = 0x00; 

/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */

/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */

/**========================================================================== --
   Private functions
-- ========================================================================== */
/** without object */

/**========================================================================== --
   Public functions
-- ========================================================================== */
int lcd_sendcmd(i2c_t bus, unsigned char cmd)
{
   int Res = 666;

   Res = i2c_acquire(bus);
   /* 0 on success, -1 on error */ 
   if (Res != 0) return Res;

   /*
   
   int i2c_write_reg(i2c_t dev, uint16_t addr, uint16_t reg, uint8_t data, uint8_t flags);

   * @param[in]  dev          I2C peripheral device
   * @param[in]  reg          register address to read from (8- or 16-bit,
   *                          right-aligned)
   * @param[in]  addr         7-bit or 10-bit device address (right-aligned)
   * @param[in]  data         byte to write
   * @param[in]  flags        optional flags (see @ref i2c_flags_t)
   *
   * @return                  0 When success
   * @return                  -EIO When slave device doesn't ACK the byte
   * @return                  -ENXIO When no devices respond on the address sent on the bus
   * @return                  -ETIMEDOUT  When timeout occurs before device's response
   * @return                  -EINVAL When an invalid argument is given
   * @return                  -EOPNOTSUPP When MCU driver doesn't support the flag operation
   * @return                  -EAGAIN When a lost bus arbitration occurs

   */

   Res = i2c_write_reg(bus, LCD_ADDR, CMD_REG, cmd, 0);
   if (Res != 0) return Res; 

   i2c_release(bus); 

   return 0; 
}

int lcd_displayOn(i2c_t bus)
{ 
   _displaycontrol |= LCD_DISPLAYON; 
   return lcd_sendcmd(bus,(LCD_DISPLAYCONTROL | _displaycontrol));  
} 

int lcd_clear(i2c_t bus) 
{ 
   return lcd_sendcmd(bus,LCD_CLEARDISPLAY);  
} 

int lcd_init(i2c_t bus) 
{ 
   int Res = 666; 

   i2c_init(bus);

   // Init partie LCD 
   //Initialize displayfunction parameter for setting up LCD display 
   _displayfunction |= LCD_2LINE; 
   _displayfunction |= LCD_5x10DOTS; 

   xtimer_usleep(30*US_PER_MS); // Wait > 30ms 

   Res = lcd_sendcmd(bus,(LCD_FUNCTIONSET | _displayfunction)); 
   if (Res != 0) return  Res; 

   xtimer_usleep(40);    // Wait > 39µs 

   Res = lcd_displayOn(bus); 
   if (Res != 0) return  -22; 

   Res = lcd_clear(bus); 
   if (Res != 0) return  -33; 

   // Init RGB lib_lcd_backlight device 
   Res = i2c_acquire(bus); 
   if (Res != 0) return -44; 

   Res = i2c_write_reg(bus,BCK_ADDR,0,0,0); 
   if (Res != 0) return -55; 

   Res = i2c_write_reg(bus,BCK_ADDR,1,0,0); 
   if (Res != 0) return -66; 

   Res = i2c_write_reg(bus,BCK_ADDR,0x08,0xAA,0); 
   if (Res != 0) return -77; 

   i2c_release(bus); 

   return 0; 
} 

int lcd_setRGB(i2c_t bus, unsigned char Red, unsigned char Green, unsigned char Blue)
{
   int Res = 666;

   Res = i2c_acquire(bus); 
   if (Res != 0) return -44; 

   /* set R */
   Res = i2c_write_reg(bus, BCK_ADDR, RED_REG, Red, 0); 
   if (Res != 0) return -55; 

   /* set G */
   Res = i2c_write_reg(bus, BCK_ADDR, GREEN_REG, Green, 0); 
   if (Res != 0) return -66; 

   /* set B */
   Res = i2c_write_reg(bus, BCK_ADDR, BLUE_REG, Blue, 0); 
   if (Res != 0) return -77; 

   i2c_release(bus); 

   return 0; 
}

int lcd_putch(i2c_t bus, unsigned char Car)
{
   int Res = 666;

   Res = i2c_acquire(bus); 
   if (Res != 0) return -44;

   Res = i2c_write_reg(bus, LCD_ADDR, DATA_REG, Car, 0);
   if (Res != 0) return Res; 

   i2c_release(bus);

   return Res;
}

int lcd_puts(i2c_t bus, unsigned char *pCar)
{
   int Res = 666;
   int size = 0;

   //mesure taille de la chaîne de caractères
   for(int i = 0; i<16; i++)
   {
      if(pCar[i]!='\0')
      {
         size++;
      }
      else
      {
         break;
      }
      
   }

   if(size>16) size = 16; //on limite la taille à 16 caractères

   lcd_clear(bus);
   xtimer_usleep(30*US_PER_MS);

   for(int i = 0; i<size; i++)
   {
      lcd_putch(bus, pCar[i]);
   }


   return Res;
}