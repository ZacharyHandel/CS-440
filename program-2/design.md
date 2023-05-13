# Design Sketch - Daytime server and client

Name - Zachary Handel
CS 440 - Assignment #2
February 1, 2023

# Program requirements

This document describes the design for a daytime server and client operating on TCP port 1313. The daytime service, a "small server", is described in [RFC 867](https://tools.ietf.org/html/rfc867).

## Server
The server will generate the current data/time and sent it to the client. The server should handle errors so that it should recover from the error and continue if possible. If not possible, it should display an error, cleanup messages, and then terminate.

## Client
On success, the client will display the received date/time string to the console then terminate. The client should handle errors so that it should recover from the error and continue if possible. If not possible, it should display an error, clean up messages, and then terminate.

# Program Inputs
The client will have one required command line argument which is the hostname / IP address of the server.

# Program Outputs
The server will output to the client the current date/time.

# Test Plan
In order to test anything, we need to change the port to the suggested port so that we don't crash with any traffic from other students.

Test Case 1: Testing Server Skeleton
	- In order to test the code skeleton, we will run the make file. Then, we will use tmux to create a client / server interaction workspace. We will have 2 windows (one being the server and the other being the client). We will run both compiled files in their designated window. Then, we will type a message through the client. If the message appears in the server's window, we know we have a connection
	- We can also test this by typing the following command: echo "\r" |nc localhost [port]. In the end, we will switch back to the 1313 port suggested by the professor.
	- The expected input for this test case will be either the user input from the client side or the command shown above. The output will be the resulting message on the server's terminal screen.

Test Case 2:
	- Once we write the correct code and we know we have connection between the client and the server, we will need to test for if a message will be displayed once the client joins the server (for this case it will be the current date/time).
	- The expected input for this test case will be either the user input from the client side or the command shown above. The output will be the current date/time from the server onto the client's terminal.
# Solution Overview
First, edit the daytime server and change the port to the desired testing port (when done, you will switch back to 1313, but for testing purposes the port will be 11627). Then, edit the Makefile to correctly compile the desired files using the clang compiler. You will then compile the skeleton code and the result should be two executable files. Once that is done, you will use tmux to create 2 console screens (one for the server and one for the client). You will then test the connection between the two by running the server and then running the client to connect to the server on the correct hostname. Then, type some messages from the client side and see if they come into the server's terminal. If this happens, you have connection between the two. After you have established a connection between the client and the server, you will need to edit the server daytime C file in order to make it display the current date/time whenever a client is connected. This will happen by the server listening unil a client is connected. Once the client is connected to the correct address the message will be displayed on the client's screen. We will then close the connection after the quote is send according to the RFC 867. 

# How to Run
## How to Run
1. Download the [Clang Compiler](https://releases.llvm.org/download.html)
2. In the same directory as the program, use Clang to compile client_daytime.c and server_daytime.c
```bash
clang client_daytime.c server_daytime.c -o <out-file-name-here>
```
3. Run the server in its own terminal
```bash
./<server-out-file-name-here>
```
4. Connect the client to the server in a seperate terminal by running
```bash
./<client-out-file-name-here> local host <port-number-here>
```
5. Observe the output to the client terminal
