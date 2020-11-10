#include <stdio.h>
#include "shell.h"


int _target_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;
	 
	 switch (*argv[1]) { 
    case 'B' : 
    	printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    break; 
    case 'M' : 
		printf("This board features a(n) %s MCU.\n", RIOT_MCU);
    break; 
		default: printf("Illegal code, enter B for Board info or M for MCU info\n"); 
    break;
}
		
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "target", "get target device", _target_handler },
    { NULL, NULL, NULL }
};


int main(void)
{
	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	
	return 0;	
}


