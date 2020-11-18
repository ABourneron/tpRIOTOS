#include <stdio.h>
#include "shell.h"

#include "thread.h"
#include "xtimer.h"

#include "board.h"
#include "periph/gpio.h"

static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;

kernel_pid_t gpio_update_thread_pid;

#define LED2_PIN	GPIO_PIN(PORT_A, 5)
#define BP1_PIN		GPIO_PIN(PORT_C, 13)

static void gpio_cb(void *arg)
{
    (void) arg;
    
    thread_wakeup(gpio_update_thread_pid);
}

void *gpio_update_thread(void *arg)
{
    (void) arg;
    
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init_int(BP1_PIN, GPIO_IN, GPIO_RISING, gpio_cb, NULL);
    
    while(1)
    {
		gpio_toggle(LED2_PIN);
		
		//PUT the thread in sleep mode
		thread_sleep();		
	}
	
    return NULL;
}
int main(void)
{
    gpio_update_thread_pid=thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN + 1, flag,
                  gpio_update_thread, NULL, "gpio_update_thread");
                  
                  printf("%d\n",gpio_update_thread_pid);
                                   
                  
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
}

