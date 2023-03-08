/*
 * Name: Zachary Handel
 * Course-Section: Networking
 * Assignment: Magic 8 Ball Protocol
 * Due Date: NA
 * Collaborators: NA
 * Description: Server file for the Magic 8 Ball protocol interaction
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
#include <stdlib.h>
//#include <bsd/stdlib.h>

void sig_handler(int);
char* make_packet(char[], char[], char[]);
char* random_message_generator();
char* substr(char[], int, int);
volatile sig_atomic_t cleanup_exit;

const int SERVER_PORT = 11627;
const int MAX_PENDING = 5;
const int MAX_LINE = 256;

int
main(void)
{
	struct sockaddr_in sin;
	char buf[36];
	socklen_t new_len;
	int s, new_s;

	/*build address data structrue*/
	memset((char*)&sin, 0, sizeof sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/*setup passive open*/
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		err(1, "enable to open socket");

	if((bind(s, (struct sockaddr *)&sin, sizeof sin)) == -1)
		err(1, "unable to bind socket");

	if((listen(s, MAX_PENDING)) == -1)
		err(1, "listen on socket failed");

	    
	    signal(SIGINT, sig_handler);
	    signal(SIGTERM, sig_handler);

	    puts("Server running...");
	
	printf("Listening for client...\n");
	while(! cleanup_exit) {
		/*wait for connection, then receive and print text*/
		new_len = sizeof sin;
		if((new_s = accept(s, (struct sockaddr *)&sin, &new_len)) == -1) {
			close(s);
			err(1, "accept failed");
		}

		//START MESSAGE CODE READING*****
		char buf_code[2];
		memset(buf_code, 0, sizeof buf_code);	//set buffer to 0
		memset(buf, 0, sizeof buf);		//set buf to 0

		recv(new_s, buf, sizeof(buf), 0);	//RECV 10
		strcpy(buf_code, substr(buf, 0, 1));	//copy code of buf	
		if(strcmp(buf_code, "10") == 0){	//if code is 10
			printf("Client Code: %s\n", buf_code);	//print code sent from client
		} else {
			puts("CODE NOT 10. 50 THROWN\n");	
			memset(buf, 0, sizeof buf);
			strcpy(buf, make_packet("50","23","Error! Wrong Code Type."));	
			send(new_s, buf, strlen(buf), 0);	//send code error
			close(s);	//end session
			return 0;
			//throw 50
		}


		memset(buf, 0, sizeof(buf));	//set buffer to 0
		memset(buf_code, 0, sizeof buf_code);	
		strcpy(buf, make_packet("20","28","Hello, what is your qustion?"));	//copy message to send to client
		send(new_s, buf, strlen(buf), 0);	//send 20 code to client
		memset(buf, 0, sizeof(buf));	//set buffer to 0

		recv(new_s, buf, sizeof(buf), 0);		//REC 30
		strcpy(buf_code, substr(buf, 0, 1));
		if(strcmp(buf_code, "30") == 0) {
			printf("Client Code: %s\n", buf_code);
		} else {
			puts("CODE NOT 30. 50 THROWN\n");
			memset(buf, 0, sizeof buf);
			strcpy(buf, make_packet("50","23","Error! Wrong Code Type."));
			send(new_s, buf, strlen(buf), 0);
			close(s);
			return 0;
		}
		
		memset(buf, 0, sizeof(buf));
		strcpy(buf, random_message_generator());
		send(new_s, buf, strlen(buf), 0);

		/*not reached*/
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
			break;
	default : 
			printf("%d not handled\n", sig);
	}
	errno = save_errno;
}

char* random_message_generator() {
	char* random_messages[20] = {"It is certain","Without a doubt","You may rely on it","Most likely","Yes",
									"Reply hazy try again","Better not tell you now","Concentrate and ask again","My reply is no","Outlook not so good",
									"It is decidedly so","Yes, definately","As I see it, yes"," Outlook good","Signs point to yes",
									"Ask again later","Cannot predict now","Don't count on it","My sources say no","Very doubtful"};
	return random_messages[arc4random_uniform(20)];
	
}

char* make_packet(char packet_code[2], char packet_length[2], char packet_payload[32]) {
	size_t code_len = strlen(packet_code);
	size_t length_len = strlen(packet_length);
	size_t payload_len = strlen(packet_payload);
	char* res = malloc(code_len + length_len + payload_len + 1);
	if(res) {
		memcpy(res, packet_code, code_len);
		memcpy(res + code_len, packet_length, length_len);
		memcpy(res + code_len + length_len, packet_payload, payload_len +1);
	}
	return res;
}

char* substr(char str[], int begin, int end) {
	static char b[100];
	
	int i = 0;

	while(begin <=end) {
		b[i] = str[begin];
		
		i++;
		begin++;
	}
	return b;
}
