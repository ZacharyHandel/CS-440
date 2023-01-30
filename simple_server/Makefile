CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: server client

server: simple_server.c
		$(CC) $(CFLAGS) -o server simple_server.c

client: simple_client.c
		$(CC) $(CFLAGS) -o server simple_client.c

clean:
		@rm -f server client *.c~ *.core