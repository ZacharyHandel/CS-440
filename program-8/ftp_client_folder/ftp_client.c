/*
*
*
*
*
*
*
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

#include "../basic_ftp.h"
const int SERVER_PORT = 11621;
const int MAX_COMMAND_LINE = 64;
const int MAX_PACKET_LINE = 515;
const int MAX_OPCODE_LINE = 3;
const int MAX_FILENAME_LINE = 61;

char* createMessage(char[3], char[61]);
//int extractMessageType(char[3], char[61]);
//char* extractMessagePayload(char[515]);

int
main(int argc, char * argv[])
{
    char cmd[MAX_COMMAND_LINE];
	char opCode[MAX_OPCODE_LINE];
	char fileName[MAX_FILENAME_LINE];
	char buf[MAX_PACKET_LINE];
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    int s;
	FILE* receivedFile;
	size_t len;

    if(argc == 2)
        host = argv[1];
    else {
        fprintf(stderr, "usage: client hostname\n"); // IF NOT 2 ARGUMENTS
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

    /*main loop: get text from stdin and send*/
	printf("***Welcome to the Basic FTP Protocol Client***\n");
	printf("Basic-ftp commands:\n"
		"\t GET- download the named file from the basic-ftp server\n"
		"\t PUT- upload the named fule to the basic-ftp perser\n"
		"\t BYE-quit\n"
		);

    while(1) {
		memset(opCode, 0, sizeof opCode);
		memset(fileName, 0, sizeof fileName);
       	memset(cmd, 0, sizeof cmd);
		memset(buf, 0, sizeof buf);
		printf("bftp>");
		scanf("%64s", opCode);
		if(strcasecmp(opCode, "GET") == 0) {
			printf("\n");
			scanf("%64s", fileName);
			printf("***OPCODE: %s\n", opCode);
			printf("***FILENAME: %s\n", fileName);
			strcpy(cmd, createMessage(opCode, fileName));
			send(s, cmd, sizeof cmd, 0);
			recv(s, buf, sizeof buf, 0);

			if (strcmp(buf, "RDY") == 0) {
				memset(buf, 0, sizeof buf);
				receivedFile = fopen(fileName, "w+");
				while(recv(s, buf, sizeof buf, 0) == 515) {
					printf("%s\n", buf);
					fprintf(receivedFile, "%s", buf);
					fwrite(buf, 1, sizeof buf, receivedFile);
					memset(buf, 0, sizeof buf);
				}
				printf("%s\n", buf);
				fprintf(receivedFile, "%s", buf);
				fwrite(buf, sizeof (char), sizeof buf, receivedFile);
				memset(buf, 0, sizeof buf);
				fclose(receivedFile);
			} else {
				printf("Error: No RDY received.\n");
			}
		}

		else if (strcasecmp(opCode, "PUT") == 0) {
			printf("\n");
			scanf("%64s", fileName);
			strcpy(cmd, createMessage(opCode, fileName));
			send(s, cmd, sizeof cmd, 0); 
			recv(s, buf, sizeof buf, 0);
			if (strcmp(buf, "RDY") == 0) {
				memset(buf, 0, sizeof memset);
				len = fread(buf, 1, sizeof buf, receivedFile);
				
				if (len == 515) {
					while(len == 515) {
						send(s, buf, sizeof buf, 0);
						memset(buf, 0, sizeof buf);
						len = fread(buf, 1, sizeof buf, receivedFile);
					}
					//send final packet
					send(s, buf, sizeof buf, 0);
			    } else {
					send(s, buf, sizeof buf, 0);
					memset(buf, 0, sizeof buf);
				}
			fclose(receivedFile);
			}
		}
		else if (strcasecmp(opCode, "BYE") == 0) {
			puts("Thank you for using BFTP-CLIENT. Goodbye!\n");
			break;
		}
		else if (strcasecmp(opCode, "HELP") == 0) {
			printf("Basic-ftp commands:\n"
		"\t GET- download the named file from the basic-ftp server\n"
		"\t PUT- upload the named fule to the basic-ftp perser\n"
		"\t BYE-quit\n"
		);	
		}
		//send(s, messageCode, strlen(messageCode), 0);
		
	}
    /*NOT REACHED*/
    close(s);
    return 0;
}

char*
createMessage(char opCode[3], char fileName[61]){
	char cmd[64];
	memset(cmd, 0, sizeof cmd);
	strcpy(cmd, opCode);
	strcat(cmd, fileName);
	return cmd;
}
