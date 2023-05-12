/*
* Name: Zachary Handel
* Course-Section: Networking
* Assignment: Simple Server Example
* Due Date: N/A
* Collaborators: None
* Resources: N/A
* Description: Example server to demonstrate how to use the BSD socket API
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void sig_handler(int);

volatile sig_atomic_t cleanup_exit;

const int SERVER_PORT = 1313;
const int MAX_PENDING = 5;
const int MAX_LINE = 256;

int
main(void)
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	socklen_t new_len;
	int s, new_s;

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

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	puts("Server running...");
	/*listening for client debug message*/
	printf("Listening for client...\n");

	while (! cleanup_exit) {
   		/*wait for connection, then receive and print text*/
		new_len = sizeof sin;
		if((new_s = accept(s, (struct sockaddr *)&sin, &new_len)) == -1) {	//*IF NEW SOCKET IS NOT ACCEPTED
			close(s);	//*CLOSE ORIGIONAL SOCKET
			err(1, "accept failed");	//*DISPLAY ERROR MESSAGE THAT CONNECTION REQUEST FAILED
		}
	printf("New client connected\n");
		time_t currentTime;    //CREATE TIME VARIABLE
	time(&currentTime);	//SET TIME SEED
	send(new_s, ctime(&currentTime), 30, 0);	//SEND TIME TO THE CONNECTED CLIENT
		/*NOT REACHED*/
		close(s);
		return 0;
	}
	puts("Cleaning up and exiting server. Goodbye!");
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
		exit(0);
		break;
	default :
		printf("%d not handled\n", sig);
	}
	errno = save_errno;
}
