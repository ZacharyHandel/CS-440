#Makefilew for Basic FTP Protocol
CC=clang
CFLAGS=-Wall -g

.PHONY: all clean

all: ftp_client ftp_server

ftp_client: ftp_client_folder/ftp_client.c
	$(CC) $(CFLAGS) -I basic_ftp.c -o ftp_client_folder/ftp_client ftp_client_folder/ftp_client.c

ftp_server: ftp_server_folder/ftp_server.c
	$(CC) $(CFLAGS) -I basic_ftp.c -o ftp_server_folder/ftp_server ftp_server_folder/ftp_server.c

clean:
	@rm -f ftp_client ftp_server *.c~ *.core
