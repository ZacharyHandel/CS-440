#Makefile for simplex server and client
CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: server client

server: server_daytime.c
	$(CC) $(CFLAGS) -o server server_daytime.c

client: client_daytime.c
	$(CC) $(CFLAGS) -o client client_daytime.c

clean:
	@rm -f server client *.c~ *.core
