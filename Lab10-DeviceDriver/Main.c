#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "board.h"
#include "xtimer.h"

#include "/home/etudiant/riot/RIOT/drivers/tsl2561/include/tsl2561_params.h"

static char stack[THREAD_STACKSIZE_MAIN];
static tsl2561_t CapteurLum;

int flag = 0;

void *first_thread(void *arg)
{
    (void) arg;
    
    while(1){
		printf("La luminosité de la pièce est de %d\n", tsl2561_read_illuminance(&CapteurLum));
		xtimer_usleep(3000000);
		}

    return NULL;
}


int main (void)
{
	
	int err = tsl2561_init(&CapteurLum, &tsl2561_params[0]);
	if (err != 0) printf("Error/n");
	
	thread_create(stack, sizeof(stack),
			  THREAD_PRIORITY_MAIN + 1, flag,
			  first_thread, NULL, "thread_message");
	
 	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    return 0;
}
