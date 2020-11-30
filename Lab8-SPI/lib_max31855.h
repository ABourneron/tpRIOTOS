#include "board.h"
#include "periph/spi.h"

int max31855_init(spi_t bus,spi_cs_t cs);
int max31855_readtemp(spi_t bus,spi_cs_t cs,unsigned char* pBuffRes);
float max31855_decodetemp(unsigned char* pBuffRes);
