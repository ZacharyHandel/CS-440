#ifndef BASIC_FTP
#define BASIC_FTP
#include "basic_ftp.h"

char* createMessage(char opCode[3], char fileName[61]) {
	char cmd[64];
	memset(cmd, 0, sizeof cmd);
	strcpy(cmd, opCode);
	strcat(cmd, fileName);
	return cmd;
}

int extractMessageType(char opCode[3], char fileName[61]){
	return;
}

char* extractMessagePayload(char[515]){
	return;
}

#endif
