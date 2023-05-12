#ifndef BASIC_FTP
#define BASIC_FTP

#include <stdio.h>
#include <string.h>
/*TEMPLATE FOR FUNCTIONS*/
//Function Name:
//Description:
//Inputs:
//Outputs:
//Return Value:

//Function Name: createMessage
//Description: This will creae a new message packet from parameters
//Inputs: Opcode (3 bytes ASCII), Payload (512 bytes ASCII)
//Outputs:
//Return Value:
char* createMessage(char[3], char[512]);

//Function Name: extractMessageType
//Description: This will return the message type (opcooode0 from a message as a code or enumerated type
//Inputs: Command with opcode and file (64 bytes ASCII)
//Outputs: N/A
//Return Value: Message type/opcode as a code / enumerated type
int extractMessageType(char[3], char[61]);

//Function Name: extractMessagePayload
//Description: Extracts payload from a message and cpoies it into a buffer
//Inputs: Message Payload (515 bytes ASCII)
//Outputs: Coppied buffer
//Return Value:
char* extractMessagePayload(char[515]);
#endif
