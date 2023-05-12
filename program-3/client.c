/*
*Name: Zachary Handel
*Course: CS440
*Assignment: Program 3
*Due Date: NA
*Collaborators: NA
*Description: This file is the client to the client-server socket connection. The client will send out a question to the server and the server will reply with a randomly generated answer as if it were an 8-ball.
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


const int SERVER_PORT = 11627;
const int MAX_LINE = 256;

char* make_packet(char[], char[], char[]);
char* substr(char [], int, int);

int main(int argc, char * argv[])
{
    char buf[36], buf_code[2];
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    int s, packet_code_num;
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
    //memset(buf, 0, sizeof buf);
    //while(fgets(buf, sizeof buf, stdin)) {
        //len = strnlen(buf, sizeof buf) + 1;
        //send(s, buf, len, 0);
        //memset(buf, 0, sizeof buf);
    //}
	memset(buf, 0, sizeof buf);	
	strcpy(buf, make_packet("10","05","Hello"));	//send hello to server
	send(s, buf, strlen(buf), 0);

	memset(buf, 0, sizeof buf);
	recv(s, buf, sizeof buf, 0);
	strcpy(buf, substr(buf, 4, sizeof buf));
	printf("Server:%s\n ", buf);
	//strcpy(buf, substr(buf, 0, 1));
	//strtonum(packet_code_num, buf);
	//packet_code_num = atoi(buf);
	//if(packet_code_num == 20)
		
	memset(buf, 0, sizeof buf);
	scanf("%s", &buf);
	sprintf(buf_code, "%d", (int)sizeof(buf));
	//printf("BUF CODE: %d\n", buf_code);
	strcpy(buf, make_packet("30", buf_code, buf));
	send(s, buf, strlen(buf), 0);
	memset(buf, 0, sizeof buf);
	recv(s, buf, sizeof buf, 0);
	printf("Server: %s\n", buf);
	
	
	
   /*NOT REACHED*/
    close(s);
    return 0;
}

char* make_packet(char packet_code[2], char packet_length[2], char packet_payload[32]) {
	size_t code_len = strlen(packet_code);
	size_t length_len = strlen(packet_length);
	size_t payload_len = strlen(packet_payload);
	char* res = malloc(code_len + length_len + payload_len + 1);
	if(res) {
		memcpy(res, packet_code, code_len);
		memcpy(res + code_len, packet_length, length_len);
		memcpy(res + code_len + length_len, packet_payload, payload_len + 1);
	}
	return res;
}

char* substr(char str[], int begin, int end) {
	static char b[100];
	
	int i = 0;
	
	while (begin <= end) {
		b[i] = str[begin];
		
		i++;
		begin++;
	}
	return b;
}
