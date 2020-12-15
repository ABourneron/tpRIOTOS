/*	TP RIOTOS 2k20
 * 		POLYTECH
 * TROUVE et BOURNERON*/

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "board.h"
#include "xtimer.h"

#include "lpsxxx.h"
#include "lpsxxx_params.h"

//Plage mémoire et flag pour le thread
static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;


void *read_sensor(void *arg)
{
	//Pour éviter le warning de compilation
    (void) arg;
    
    lpsxxx_t dev;

    if (lpsxxx_init(&dev, &lpsxxx_params[0]) != LPSXXX_OK) {
        puts("Initialization échouée");
        return NULL;
    }
    
    uint16_t pres;
    int16_t temp;
    
    while(1){
        lpsxxx_enable(&dev);
        xtimer_sleep(1); /* wait a bit for the measurements to complete */

        lpsxxx_read_temp(&dev, &temp);
        lpsxxx_read_pres(&dev, &pres);
        lpsxxx_disable(&dev);

        int temp_abs = temp / 100;
        temp -= temp_abs * 100;

        printf("Pressure value: %ihPa\nTemperature: %2i.%02i°C\n",
               pres, temp_abs, temp);
	
		//Sleep pendant 5s
		xtimer_usleep(5000000);
		}

    return NULL;
}


int main (void)
{

	//création du thread de lecture du sensor
	thread_create(stack, sizeof(stack),
			  THREAD_PRIORITY_MAIN + 1, flag,
			  read_sensor, NULL, "thread read temp");
			  
	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    return 0;
}
