#Program 9 Design Document: Basic Directory Listing Service

Name - Zachary Handel
CS 440 - Program 9
May 1st, 2023

#Program Requirements
This document describes the basic directory listing server-client interaction. The client will request a directory to be listed by sending the directory (as a C string) to the server. This server will then iterate through the required directory and then send all of the listed files inside said directory.

##Client
The client will send the folder name (as a C string) to the server. No other messages are sent by the client.

##Server
The server will continue waiting for a new clients after each client session is completed. The server should onyl terminate when a SIGTERM is received. The serer must terminate immediately when it recieves a SIGTERM. The server wiull use signal(3) and select(2). 

The server will perform a directory listing of the requested folder from the client and return a message indicating how many files were found in the directory. It will then list the file names in the directory. We will use the basicDirList implementation to support this functionality.
#Program Inputs

##Client
The client requires two command line arugments: The hostname of the server and the name of the folder to list.

##Server
There is no command line input and no console output for the server.

#Test Cases
##Test Case 1:
We will first use netcat to test the sending of the file name to the server.
###Example:
- Client Input: /temp
- Netcat Output: /temp

##Test Case 2:
We are going to receive from the server after we send a temp
- Server Input: *Any list of files*
- Client Output: *Any list of files*

##Test Case 3:
We are going to test select(2)
- Upon passive open, when connected then client should receive the list of files.

##Test Case 4:
We are going to test if the server stays open after client retrieval.
- Upon client connection, the client should receive the list of files and close. The server will stay open.


