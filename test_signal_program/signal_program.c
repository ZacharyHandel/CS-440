#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

void sig_handler(int);

volatile sig_atomic_t cleanup_exit;

int
main()
{
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    puts("Program running...");
    while (! cleanup_exit) {
	    ;
    }

    puts("Cleaning up and exiting");
    return 0;
}

void
sig_handler(int sig)
{
    int save_errno = errno;

    switch(sig) {
    case SIGINT :
                puts("CTRL-C pressed");
		break;
    case SIGTERM :
		 puts("SIGTERM received");
		 cleanup_exit = true;
		 break;
    default	 :
		 printf("%d not handled\n", sig);
    }

    errno = save_errno;
}
