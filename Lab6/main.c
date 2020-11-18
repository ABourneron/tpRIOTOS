#include <stdio.h>
#include "shell.h"

#include "thread.h"
#include "xtimer.h"

#include "board.h"
#include "periph/gpio.h"

static char stack1[THREAD_STACKSIZE_MAIN];
static char stack2[THREAD_STACKSIZE_MAIN];
int flag = 0;

void *first_thread(void *arg)
{
    (void) arg;
    
    while(1){
		printf("Hello from thread %d\n", thread_getpid());
		xtimer_usleep(500000);
		}

    return NULL;
}

void *second_thread(void *arg)
{
    (void) arg;
    //init LED0
	gpio_init(LED0_PIN, GPIO_OUT);
	
	//INIT TIMER
	xtimer_init();
	xtimer_ticks32_t last_time = xtimer_now();
	
	while(1){
		xtimer_periodic_wakeup(&last_time, 100000);
		LED0_TOGGLE;
	}

    return NULL;
}

int main(void)
{
    thread_create(stack1, sizeof(stack1),
                  THREAD_PRIORITY_MAIN + 1, flag,
                  first_thread, NULL, "thread_message");
                  
    thread_create(stack2, sizeof(stack2),
                  THREAD_PRIORITY_MAIN + 2, flag,
                  second_thread, NULL, "thread_led");
                  
                  
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
}

