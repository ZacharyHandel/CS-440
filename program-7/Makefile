#Makefiel for Web Client File
CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: webclient

webclient: webclient.c
	$(CC) $(CFLAGS) -o webclient webclient.c

clean:
	@rm -f webclient *.c~ *.core	
