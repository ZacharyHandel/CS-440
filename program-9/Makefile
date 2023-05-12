#Makefile for Basic Directory Listing Service
CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: dirclient dirserver

dirclient: dirclient.c
	$(CC) $(CFLAGS) dirclient.c -o client basicDirList.c 

dirserver:
	$(CC) $(CFLAGS) dirserver.c -o server basicDirList.c

clean:
	@rm -f client server *.c~ *.core 
