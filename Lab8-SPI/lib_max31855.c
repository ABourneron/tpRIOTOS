#include "/home/etudiant/riot/DII5_Riot/Lab8-SPI/lib_max31855.h"

/*
    MODE_0: CPOL=0, CPHA=0 	- The first data bit is sampled by the receiver on the first SCK rising SCK edge (this mode is used most often).
    MODE_1: CPOL=0, CPHA=1 	- The first data bit is sampled by the receiver on the second rising SCK edge.
    MODE_2: CPOL=1, CPHA=0 	- The first data bit is sampled by the receiver on the first falling SCK edge.
    MODE_3: CPOL=1, CPHA=1 	- The first data bit is sampled by the receiver on the second falling SCK edge.

	SPI_CLK_100KHZ 			- drive the SPI bus with 100KHz
	SPI_CLK_400KHZ 			- drive the SPI bus with 400KHz
	SPI_CLK_1MHZ 			- drive the SPI bus with 1MHz
	SPI_CLK_5MHZ 			- drive the SPI bus with 5MHz
	SPI_CLK_10MHZ 			- drive the SPI bus with 10MHz 
*/

int max31855_init(spi_t bus,spi_cs_t cs) 
{
	spi_init_pins(bus);
	return spi_init_cs(bus, cs);
}

int max31855_readtemp(spi_t bus,spi_cs_t cs,unsigned char* pBuffRes) 
{
	//spi_acquire (spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
	int err = spi_acquire(bus, cs, SPI_MODE_0, SPI_CLK_100KHZ);
	
	//spi_transfer_bytes (spi_t bus, spi_cs_t cs, bool cont, const void *out, void *in, size_t len)
	spi_transfer_bytes(bus, cs, 1, &pBuffRes, NULL, 4);
	
	//spi_release (spi_t bus)
	spi_release(bus);
	
	return err;
}
float max31855_decodetemp(unsigned char* pBuffRes)
{
  printf("%d %d %d %d\n", pBuffRes[0], pBuffRes[1], pBuffRes[2], pBuffRes[3]);
  return 0;
}
