#include "board.h"
#include "periph/spi.h"

#define    SPI_PORT		SPI_DEV(0) 
#define    SPI_CS_PIN	(spi_cs_t)GPIO_PIN(PORT_B,6)  

int max31855_init(spi_t bus,spi_cs_t cs);
int max31855_readtemp(spi_t bus,spi_cs_t cs,unsigned char* pBuffRes);
float max31855_decodetemp(unsigned char* pBuffRes);
