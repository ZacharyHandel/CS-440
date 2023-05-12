#Makefile for Magic 8 Ball Protocol Files
CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	@rm -f server client *.c~ *.core
