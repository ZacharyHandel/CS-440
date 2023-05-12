/*
*Name: Zachary Handel
*Course-Section: Networking
*Assignment: Program 2 Daytime Server
*Due Date: N/A
*Collaborators: N/A
*Resources: N/A
*Description: This is a web client that will use a GET method to retrieve a file from a specified server. See design.md for more information.
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


const int SERVER_PORT = 80;	//port 80 for HTTP 1.0
const int MAX_LINE = 1000;

char* generateRequest(char[], char[]);

int 
main(int argc, char * argv[])
{
    char req[MAX_LINE];
	char URI[MAX_LINE];
	char receivedBuf[MAX_LINE];
	FILE *received_file = NULL;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    int s, file_size;

	//deal with arguments
    if (argc == 2)
	{
        host = argv[1];
		strcpy(URI, "/");
	}
	else if (argc == 3)
	{
		host = argv[1];
		strcpy(URI, argv[2]);	//set request = initially inputted server path
	}
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
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(1, "unable to open socket");

    if ((connect(s, (struct sockaddr*)&sin, sizeof sin)) == -1) {
        close(s);
        err(1, "connect failed");
    }

    /*main loop*/
	//PUT MAIN CODE HERE
	strcpy(req, generateRequest("GET", basename(URI)));
	send(s, req, strlen(req), 0);
	printf("URI %s\n", URI);
	received_file = fopen("outfile", "w");
	

	//HAD ISSUES WITH THIS!!!!!!!
	size_t bytes;
	while (0 < (bytes = recv(s, receivedBuf, sizeof receivedBuf, 0)))
		fwrite(receivedBuf, 1, bytes, received_file);

	//recv(s, testBuf, sizeof testBuf, 0);
	//printf("TESTING INFO: \n%s\n", testBuf);
	//puts("***AFTER OPEN***\n");
	
	if (received_file == NULL)
	{
		fprintf(stderr, "Failed to open file\n");
		
		exit(EXIT_FAILURE);
	}


	fclose(received_file);
    /*NOT REACHED*/
    close(s);
    return 0;
}

char*
generateRequest(char method[4], char URI[MAX_LINE]) {
	int method_length = strlen(method);
	int URI_length = strlen(URI);
	char version[17] = " HTTP/1.0\r\n\r\n";
	int version_length = strlen(version);
	int size = method_length + URI_length + version_length + 1;	// + 1 for the null terminator
	char* request = calloc(size, sizeof(char));	//allocate memory for the request
	char first_slash[2] = " /";
	//make for loops to copy stuff from method URI and version into request
	for (int i = 0; i < method_length; i++)
		request[i] = method[i];	

	for (int i = 0; i < strlen(first_slash); i++)
		request[method_length + i] = first_slash[i];
 
	for (int i = 0; i < URI_length; i++)
		request[(method_length + 2) + i] = URI[i];

	for (int i = 0; i < version_length; i++)
		request[(method_length+2+URI_length)+i] = version[i];	

	return request;
}
