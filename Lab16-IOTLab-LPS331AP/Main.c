/*	TP RIOTOS 2k20
 * 		POLYTECH
 * TROUVE et BOURNERON*/

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "board.h"
#include "xtimer.h"

#include "saul_reg.h"
#include "phydat.h"

//Plage mémoire et flag pour le thread
static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;


void *read_sensor(void *arg)
{
	//Pour éviter le warning de compilation
    (void) arg;
    
	//Pour le capteur saul
	saul_reg_t *dev;     	//device
	phydat_t res;           //valeur
	int dim = 0;
	
	//test pour s'assurer de la présence d'un device SAUL
    if(dev == NULL)             
    {
        printf("No SAUL device\n");
        return NULL;
    }
    
    while(1){
		dev = saul_reg_find_name("lps331ap");
		
		//Appel de la fonction de lecture
		dim = saul_reg_read(dev, &res);
        phydat_dump(&res, dim);

        dev = dev->next;
        
        dim = saul_reg_read(dev, &res);
        phydat_dump(&res, dim);

		//printf("\nDev: %s\tType: %s\n", dev->name, saul_class_to_str(dev->driver->type));
		
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
