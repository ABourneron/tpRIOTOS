/*	TP RIOTOS 2k20
 * 		POLYTECH
 * TROUVE et BOURNERON*/

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "board.h"
#include "xtimer.h"

#include "/home/etudiant/riot/RIOT/drivers/tsl2561/include/tsl2561_params.h"

//Plage mémoire et flag pour le thread
static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;

static tsl2561_t CapteurLum;

void *read_temp(void *arg)
{
	//Pour éviter le warning de compilation
    (void) arg;
    
    while(1){
		//Appel de la fonction de lecture
		printf("La luminosité de la pièce est de %d\n", tsl2561_read_illuminance(&CapteurLum));
		
		//Sleep pendant 3s
		xtimer_usleep(3000000);
		}

    return NULL;
}


int main (void)
{
	//Init du capteur tsl2561 avec retour d'erreur
	int err = tsl2561_init(&CapteurLum, &tsl2561_params[0]);
	if (err != 0) printf("Error\n");
	
	//création du thread de lecture de la température
	thread_create(stack, sizeof(stack),
			  THREAD_PRIORITY_MAIN + 1, flag,
			  read_temp, NULL, "thread read temp");
	
	//parametrise et démarage du shell
 	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    return 0;
}
