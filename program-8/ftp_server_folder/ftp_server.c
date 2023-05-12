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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "../basic_ftp.h"

char* createMessage(char[3], char[61]);
char* extractFileName(char[64]);
//char* extractMessagePayload(char[515]);

void sig_handler(int);

volatile sig_atomic_t cleanup_exit;

const int SERVER_PORT = 11621;
const int MAX_PENDING = 5;
const int MAX_LINE = 256;
const int MAX_COMMAND_LINE = 64;
const int MAX_PACKET_LINE = 515;
const int MAX_OPCODE_LINE = 3;
const int MAX_FILENAME_LINE = 61;

int
main(void)
{	
	char cmd[MAX_COMMAND_LINE];
	char opCode[MAX_OPCODE_LINE];
	char fileName[MAX_FILENAME_LINE];
	char buf[MAX_PACKET_LINE];
    struct sockaddr_in sin;
	FILE* receivedFile;
	size_t len;
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

	puts("***WELCOME TO THE FTP SERVER***");
    while(! cleanup_exit) {
		/*wait for connection, then receive*/
		new_len = sizeof sin;
		if ((new_s = accept(s, (struct sockaddr *)&sin, &new_len)) == -1) {
			close(s);
			err(1, "accept failed");
    	}
		puts("NEW CLIENT CONNECTED");
		memset(cmd, 0, sizeof cmd);
		recv(new_s, cmd, sizeof cmd, 0);
		printf("RECEIVED COMMAND: %s\n", cmd);
		if (strncasecmp(cmd, "GET", 3) == 0) {
			send(new_s, "RDY", 3, 0);
			
			//TESTING EXTRACT FILE NAME
			memset(fileName, 0, sizeof fileName);
			strcpy(fileName, cmd+3);
			printf("***FILE NAME: %s\n", fileName);
			receivedFile = fopen(fileName, "w+");
			//SEND DATA
			memset(buf, 0, sizeof buf);
			len = fread(buf, 1, sizeof buf, receivedFile);
			if(len == 515) {
				while(len == 515) {
					send(new_s, buf, sizeof buf, 0);
					memset(buf, 0, sizeof buf);
					len = fread(buf, 1, sizeof buf, receivedFile);
				}
				//send final packet
				send(new_s, buf, sizeof buf, 0);
			} else {
				send(new_s, buf, sizeof buf, 0);
				memset(buf, 0, sizeof buf);
			}
		} else if (strncasecmp(cmd, "PUT", 3) == 0) {
			send(new_s, "RDY", 3, 0);
			memset(fileName, 0, sizeof fileName);
			memset(buf, 0, sizeof buf);
			strcpy(fileName, cmd+3);
			
			receivedFile = fopen(fileName, "w+");
			while(recv(new_s, buf, sizeof buf, 0) == 515) {
				fprintf(receivedFile, "%s", buf);
				fwrite(buf, 1, sizeof buf, receivedFile);
				memset(buf, 0, sizeof buf);
			}
			fprintf(receivedFile, "%s", buf);
			fwrite(buf, sizeof (char), sizeof buf, receivedFile);
			memset(buf, 0, sizeof buf);
			fclose(receivedFile);
		}
	}

	puts("CLIENT CONNECTED");
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

char*
createMessage (char opCode[3], char fileName[61]) {
	char cmd[64];
	memset(cmd, 0, sizeof cmd);
	strcpy(cmd, opCode);
	strcat(cmd, fileName);
	return cmd;
}

char*
extractFileName (char cmd[64]){
	return cmd+3;
}


