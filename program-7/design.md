# Program 7 Design Document: Client Web Server Fetch

Name - Zachary Handel
CS 440 - Program 7
March 3, 2023

# Program Requirements
This document describes the client web server fetch program. The client will will implement a utility to fetch a single asset (file) from a web server and save it into a file.
Some things to note:
- The client will speak the 1.0 http protrocol (see RFC 1945). Web servers that speak http listen on tcp port 80.
- The web client will use GET to request the asset.
- There are 3 parts to the HTTP request we will be using:
	- The method
	- the URI
	- the version of http the client is speaking
- The request line is terminated by a CR and LF and is followed by a blank line (which is also terminated by a CR and LF).
	- Ex: For the client to reach a file named cat.jpg in a folder named images, the requiest will look like this:
		- GET /images/cat.jpg HTTP/1.0\r\n\r\n
- The client will use nothing other than GET and HTTP/1.0
- One run will equal one fetched asset.

- For our file operations we will use:
	- fopen
	- fwrite
	- fclose

# Program Inputs
2 arguments are accepted:
- the hostname of the web server (REQUIRED)
- the fully qualified path and name of the requested asset (OPTIONAL)
	- NOTE: If the second option is not supplied on the command line then the client should request "/" as the file name (see RFC 1945). A single forward slash requests the web server's index.html file. This will be saved by the client as index.html (W/O THE SLASH). If the second command is supplied on the command line, the client will request the file as sepcified and save it without a path (for this we will use basename() function to reutrn just the bare filename from the requested fully qualified path and name.
- Argument may only contain characters a-z, A-Z, 0-9, '-','.','/','_', or '`'. In the case of invalid errors the client may:
	- Display an error mesages indicated invalid URI characters were detected
	- use the curl() library's curl_easy_escape() to escape the URI

Program Outputs
The program will output one of the following based on predefined conditions:
- An outputted asset folder
- An outputted index.html folder

# Test Cases
## Test Case 1: Testing Client Command Line Arguments
For this, Try running the client inside the command line with the following inputs:
	- ./webclient cs.csis.work
	- ./webclient cs.csis.work /
	- ./webclient cs.csis.work /acm.html
	- ./webclient cs.csis.work /images/cat.jpg
NOTE: THESE INPUTS CAN VARY DEPENDING ON THE DESIRED FILE

## Test Case 2: Test for false input
For this, test the command line with invalid argument characters. The program should prompt the user that invalid URI characters were detected.

## Test Case 3: Test for Proper File Output
For this, run the webclient program with and without the second argument. For one argument, the program should output the web servers index.html. For two arguments, the program should output just the bare filename.


