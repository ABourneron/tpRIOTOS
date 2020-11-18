#include <stdio.h>
#include "shell.h"

#include "thread.h"

static char stack[THREAD_STACKSIZE_MAIN];
int flag = 0;

void *first_thread(void *arg)
{
    (void) arg;
    printf("Hello from thread %d\n", thread_getpid());

    return NULL;
}
int main(void)
{
    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN - 1, flag,
                  first_thread, NULL, "first_thread");
                  
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
}

