#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "shell.h"          //pour inclure un shell et créer ses commandes
#include "board.h"          //pour inclure les LED0_PIN ...
#include "periph/gpio.h"    //pour inclure les fonctions gpio_init, toggle ...
#include "xtimer.h"         //pour inclure les fonctions timers
#include "periph/hwrng.h" 

#include "lib_lcd_backlight.h"

static char stackONE[THREAD_STACKSIZE_MAIN];

uint8_t RandomBuffRed[1];
uint8_t RandomBuffGreen[1];
uint8_t RandomBuffBlue[1];

char *MyBeautifulChaine = "Salut Coco";

int cmd_led2_handler(int argc, char *argv[])
{
	if (argc <2)
    {
        printf("no argument\n");
    }
    else
	{
    	if(strcmp("on",argv[1])==0){
            printf("commande on\n");
            LED0_ON;    //on allume la LED

        }else if(strcmp("off",argv[1])==0) {
            printf("commande off\n");
            LED0_OFF;   //on éteint la lED

        }else if(strcmp("toggle",argv[1])==0) {
            printf("commande toggle\n");
	        //gpio_toggle(LED0_PIN);
            LED0_TOGGLE;    //on inverse la LED

        }else {
            printf("try on, off or toggle\n");
        }
	}
	return 0;
}

static const shell_command_t shell_commands[] = 
{
    { "led2", "contrôle LED2", cmd_led2_handler },
   	{ NULL, NULL, NULL }
};


static void *threadONE_handler(void *arg)     
{
    (void) arg;
    
    //int err = 666;

    LED0_TOGGLE;

    hwrng_read(RandomBuffRed, 1);
    hwrng_read(RandomBuffGreen, 1);
    hwrng_read(RandomBuffBlue, 1);

    lcd_setRGB(I2C_PORT, RandomBuffRed[0], RandomBuffGreen[0], RandomBuffBlue[0]);

    lcd_puts(I2C_PORT, (unsigned char*)MyBeautifulChaine);

    return NULL;
}

static void gpio_cb(void *arg)                  
{
    (void) arg;
    printf("Creation thread %d prise temp\n", thread_getpid());
    thread_create(stackONE, sizeof(stackONE),                    
                  THREAD_PRIORITY_MAIN + 1,     
                  0,
                  threadONE_handler,
                  NULL, "Aïïïe !!!");
}

int main (void)
{
    int err = 0;

    printf("Hello from main\n");

    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init_int(BTN0_PIN, GPIO_IN, GPIO_FALLING, gpio_cb, NULL);
    
    err = lcd_init(I2C_PORT);
    printf("lcd_init res : %d\n", err);

    err = lcd_setRGB(I2C_PORT, 0, 255, 128);
    printf("setRGB res : %d\n", err);

    hwrng_init();

	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    
    return 0;
}
