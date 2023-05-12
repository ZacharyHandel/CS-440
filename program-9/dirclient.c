/*
*Name: Zachary Handel
*Course: CS-440
*Assignment: Program-9
*Due Date: May 3rd, 2023
*Collaborators: N/A
*Description: This is the client side to the basic directory listing service.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "basicDirList.h"

const int SERVER_PORT = 11627;
const int MAX_LINE = 256;

int main(int argc, char * argv[])
{
    char* dir;
	char buf[MAX_LINE];
    struct hostent *hp;
    struct sockaddr_in sin;
    char* host;
    int s, numFiles;
    //size_t len;

    if (argc == 3) {
        host = argv[1];
		dir = argv[2];
	}
    else {
        fprintf(stderr, "usage: client <hostname> <directory>\n"); // IF NOT 2 ARGUMENTS
        exit(1);
    }

    /*translate host name into peer's IP address*/
    hp = gethostbyname(host);
    if (!hp)
        errx(1, "unknown host %s", host);

    /*build address data structure*/
    memset((char*)&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
    memcpy((char*)&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    /*active open*/
    if((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(1, "unable to open socket");

    if((connect(s, (struct sockaddr*)&sin, sizeof sin)) == -1) {
        close(s);
        err(1, "connect failed");
    }

    /*main: indicate connection request is sent; send a buffer with the name of the directory requested by argv[2]; */
   	puts("Connection Request Sent...");

	//send out directory request
	memset(buf, 0, sizeof buf);
	strcpy(buf, dir);
	send(s, buf, sizeof buf, 0);
	
	//Recieve message with number of files and file listing
	memset(buf, 0, sizeof buf);
	recv(s, buf, sizeof buf, 0);

	//print recieved message
	printf("%s\n", buf);

    /*NOT REACHED*/
    close(s);
    return 0;
}
