#include <stdio.h>
#include "shell.h"

#include "thread.h"
#include "xtimer.h"

#include "board.h"
#include "periph/gpio.h"

static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;

#define LED2_PIN	GPIO_PIN(PORT_A, 5)
#define BP1_PIN		GPIO_PIN(PORT_C, 13)

void *first_thread(void *arg)
{
    (void) arg;
    
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init(BP1_PIN, GPIO_IN);
    
    while(1)
    {
		if(gpio_read(BP1_PIN)==0)
		{
			gpio_write(LED2_PIN, 1);
		}
		else
		{
			gpio_write(LED2_PIN, 0);
		}
	}
	
    
    return NULL;
}
int main(void)
{
    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN + 1, flag,
                  first_thread, NULL, "first_message");
                                   
                  
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
}

