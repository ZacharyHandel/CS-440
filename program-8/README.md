#Program 8: Basic FTP protocol
Name - Zachary Handel
CS 440 - Program 8
April 12th, 2023

#Program Requirements
This document describes the basic FTP protocol connection between a web client and a web server. 

##Protocol
The required basic ftp protocol has 5 message types:
###GET
- This is where you will request to dowjnload a file from the server.
###PUT
- This is where you will request to upload a file to the server.
###DAT
- This is a packet for the data.
###RDY
- This is where the server is ready to process the client's request and will be sent as almost a handshake between the client and server.
###ERR
- This means something went wrong with the client's request.

##Packet Info/Format
- The opcode/type in the message will always be uppercase. This means that if the user inputs it in lowercase, the program can handle it.
- The format consists of a 3 byte ASCII opcode and a 512 byte ASCII payload that is null terminated when it is NOT a data packet.
	- This means that if the payload is a file name or an error message, it is null terminated (DAT packets are not null terminated).

- The end of a file transfer is signalled by a DAT packet with less than 512 bytes of a payload.
	- This means if the number of bytes in the payload is 0 to 511 bytes, we will close the file

##FTP Header and Implementation
- We will use a basic ftp protocol header for both the client and server. 
###Required Operations
- Create a new message: This creates a new message packet from some set parameters
- Extract the message type: This will return the message type/opcode from a message as a code or enumerated type
- Extract the message payload: This extracts the payload from a message and copies it into a buffer.

##Client
- The client will require one command line argument of the hostname of the basic FTP server. If this is not provided then the client should display a usage message and terminate. 
- The client will act as an interactive shell. The user will be able to type a command and the client will perform the requested operation. The four possible options the user can use are the following:
	- get
	- put
	- bye
	- help
- for both get and put, they will require a file name. this will be case sensitive. get will cause the client to download the named file from the server. the put command will cause the client to upload the named file to the server.
- if the client cannot complete an operation, then the client will send an err message to the server and display an error to the user (e.g. "error: unable to open foo.txt").
	- note: the client will not terminate when it sends or receives an err message. it will allow the user to type another command.
- the help command will simply output a brief description of the client commands. 
- the bye command will cause the client to clean up and terminate.

- The client will be able to transfer several files in a single session before disconnecting.

##Server
- There will be no commadn line input and no console output by the server.
- The server will simply wait for for new clients after each client session is completed. 
- The only reason the server should terminate is if it receives a SIGTERM. The server will use signal(3) and select(2).
- Any time the server receives a GET or PUT, it will acknowledge it with a RDY packet. If the server cannot fulfil the PUT or GET request, it will send an ERR packet. The ERR packet will include an informative error string as the payload (this will be null terminated).
	- File not found
	- File access denied
	- Unable to write file

##Extra Requirements
- The server and client MUST BE in seperate folders when testing. This means you cannot download a folder from a file into the same folder. The same applies to uploadin
##Extra Requirements
- The server and client MUST BE in seperate folders when testing. This means you cannot download a folder from a file into the same folder. The same applies to uploading.

#Program Inputs
The client will accept the hostname of the server. When the client is running, the created interactive shell will accept the following:
- get
- put
- bye
- help
For both get and put, they will require a file name. this will be case sensitive. get will cause the client to download the named file from the server. the put command will cause the client to upload the named file to the server.

If the client cannot complete an operation, then the client will send an err message to the server and display an error to the user (e.g. "error: unable to open foo.txt").
- Note: the client will not terminate when it sends or receives an err message. it will allow the user to type another command.
The help command will simply output a brief description of the client commands. 
The bye command will cause the client to clean up and terminate.

- The server accepts no inputs.

#Program Outputs
The server will output a requested file from its root directory to the client. The server will also write files sent from the client to its root directory.

#Test Cases
##Test Case 1: Test the connectivity of the client
For this, we will use netcat to test the connectivity of the client. This is where we can test to see if the files are sending correctly.

##Test Case 2: Test the correct format of the packet
This is where we will output (either in the server or client) the packet that is created from the basic ftp protocol. We can then tweak the packet format based off of this.

##Test Case 3: Test the RDY packet Ackowledgement
After we get the packets working, we can then test to see if the server will ackowledge a message from the client by sending it a RDY packet.

##Test Case 4: Test ERR packets
This is where we will purposefully check the functionality of all possible error cases. This will include not being able to fulfil a GET and PUT as well ass the client throwing an error to the SERVER (if the client throws an error, the program will continue to run).

##Test Case 5: Testing file transfer
This is where we will test the final functionality of the program to see if files transfer correctly.

