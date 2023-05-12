/*
* Name: Zachary Handel
* Course-Section: Networking
* Assignment: Basic File Directory Listing Server
* Due Date: N/A
* Collaborators: None
* Resources: N/A
* Description: This server accepts a file directory and will send the client all the files listed in said directory
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "basicDirList.h"


volatile sig_atomic_t cleanup_exit;

void sig_handler(int);

const int SERVER_PORT = 11627;
const int MAX_PENDING = 5;
const int MAX_LINE = 256;

int
main(void)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
	char sending_buf[MAX_LINE];
    socklen_t new_len;
    int s, new_s;

	fd_set rfds;
	struct timeval tv;
	int retval;

    /*build address data structure*/
    memset((char*)&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /*setup passive open*/
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(1, "unable to open socket");

    if((bind(s, (struct sockaddr *)&sin, sizeof sin)) == -1)
        err(1, "unable to bind socket");

    if((listen(s, MAX_PENDING)) == -1)
        err(1, "listen on socket failed");
    
    /*wait for connection, then receive and print text*/
    new_len = sizeof sin;

	puts("WELCOME TO THE BASIC DIRECTORY LISTING SERVICE SERVER! Please wait for a client connection...");
	
	FD_ZERO(&rfds);
	FD_SET(s, &rfds);

    while(! cleanup_exit) {
		//setting timeout to wait 0.25 seconds
		tv.tv_sec = 0;
		tv.tv_usec = 250000;

		retval = select(s, &rfds, NULL, NULL, &tv);

		if (retval == -1) {
			err(1, "select(2)");
			close(s);
		}
	
		if((new_s = accept(s, (struct sockaddr *)&sin, &new_len)) == -1) {
			close(s);
			err(1, "accept failed");
		}
		FD_SET(new_s, &rfds);
		puts("NEW CLIENT CONNECTED");

		memset(buf, 0, sizeof buf);
		memset(sending_buf, 0, sizeof buf);
		recv(new_s, buf, sizeof buf, 0);
		//printf("BUF RECIEVED: %s\n", buf);

		strcpy(sending_buf, getDirListing(buf));
		//printf("SENDING BUF:\n%s\n", sending_buf);
		
		send(new_s, sending_buf, sizeof sending_buf, 0);
	}
	
    /*NOT REACHED*/
    close(s);
    return 0;
}

void
sig_handler(int sig)
{
	int save_errno = errno;

	switch (sig) {
		case SIGINT :
			puts("CTRL-C detected");
			break;
		case SIGTERM :
			puts("SIGTERM received");
			cleanup_exit = true;
			break;
		default :
		 printf("%d not handled\n", sig);
	}
	errno = save_errno;
}
