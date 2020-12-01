#include <stdio.h>
#include "shell.h"

#include "thread.h"
#include "xtimer.h"

#include "/home/etudiant/riot/DII5_Riot/Lab8-SPI/lib_max31855.h"

static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;
unsigned char buffer[4];

void *first_thread(void *arg)
{
	(void) arg;
	max31855_init(SPI_PORT, SPI_CS_PIN);
	
	while(1)
	{
		max31855_readtemp(SPI_PORT, SPI_CS_PIN, buffer);
		printf("La temperature est de %.2f °C\n",max31855_decodetemp(buffer));
		
		xtimer_usleep(500000);
		
	}
	
	return NULL;
}

int main(void)
{
	thread_create(stack, sizeof(stack), 
		THREAD_PRIORITY_MAIN + 1, flag,
		first_thread, NULL, "read temp");
                                   
             
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
}

