/*
*Name: Zachary Handel
*Course-Section: Networking
*Assignment: Program 2 Daytime Server
*Due Date: N/A
*Collaborators: N/A
*Resources: N/A
*Description: This is the client side to a daytime server connection. Once connected to the server, it should recieve a message that is the current day and time.
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


const int SERVER_PORT = 1313;
const int MAX_LINE = 1000;
int main(int argc, char * argv[])
{
    char buf[MAX_LINE];
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    int s;
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
    memset(buf, 0, sizeof buf);
    while(fgets(buf, sizeof buf, stdin)) {
        len = strnlen(buf, sizeof buf) + 1;
        send(s, buf, len, 0);
        memset(buf, 0, sizeof buf);
    }

    /*NOT REACHED*/
    close(s);
    return 0;
}
