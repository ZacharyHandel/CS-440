# Design Document - Magic 8 Ball Protocol

Name - Zachary Handel
CS 440 - Assignment #5
March 3, 2023

# Program Requirements
This document describes the design for a migic 8 ball protocol server and client operating on TCP port 11627. The protocol consists of 5 message types:
- 10: A 'hello' from the client sent to the server
- 20: A 'hello, from the server sent to the client
- 30: A yes/no question sent from the client to the server
- 40: A response to the question sent from the server
- 50: Error sent from the server or the client depending on the circumstances of the error

The message format for each message type must follow the design below:
- Message type code: 2 bytes in ASCII
- Payload length, 2 bytes in ASCII
- Payload, 32 bytes, in ASCII

## Type 10 Message
Type 10 messages are a 'hello' from the client to the server. We can use the example text provided by the instructor for this message.

## Type 20 Message
Type 20 messages are a 'hello' from the server to the client. Think of it as a response. We can use the example text provided by the instructor for this message.

## Type 30 Message
The payload for the type 30 is a yes/no question. The program does not need to examine the content of the qeustion, but it needs to verify the sanity of the overall message. 

## Type 40
The payload for the type 40 should be a randomly selected message from the 20 messages provided by the instructor. For this we will use the function arc4random_uniform(3)

## Type 50
Type 50 messages are only sent when the magic 8 ball protocol is not followed. If either side of the connect receives a message that fails the sanity check, then the receiver should reply with a type 50 message and dissconnect. 

# Program Inputs
The client will have one required command line argument which is the hostname / IP address for the server. It will also be prompted to input a yes/no question. 

# Program Outputs
The server will output to the server a prompt to ask a yes/no question as well as a reply to that question.

# Test Plan
We are using a custom port in order to avoid collision with other students working on this assignment.

## Test Case 1: Testing the Server Skeleton and Makefile
- In order to test the code skeleton, we will run the make file. Then, we will use tmux to create a client/server interaction workspace. We will have 2 windows (one being the server and the other being the client). We will run both compiled files in their designated window. (Note: Before we create the client, we will use netcat to test the connectivity of the server. Debug messages will be used during this time). 

## Test Case 2: Testing Message Type Code Interaction:
- After we have the skeleton and makefile working, We will write test to make sure the interaction between the server and client are working via the provided codes. We will do this by running both programs and connecting the client to the server. We will then observe to see if the correct messages are being sent in order.

## Test Case 3: Testing the Random Message Generator Code
- After we have established that the message types are working, we will then test our random message generator. This will be as simple as just running the code multiple times to see if different messages are outputted each time.

## Test Case 4: Testing the Sanity of The Messages:
- We will need to tes the sanity of the messages. If there is an error, then a message type 50 should be sent.

# Solution Overview:
First, use the skeleton BST API code provided by the instructor and create a server, client, and make file. Make sure you implement signal checks for SIGINT and SIGTERM. We will be using port 11627 until told otherwise. Then, edit the Makefile in order to correctly compile the desired files using the Clang compiler. Once this is done, test the connection of the server with netcat. If that works, then create a workspace using tmux where one window will be the server and one will be the client. Test the connection between these two files and test signaling as well. Then, work on coding the message type checking. When that is done, test the message types and check for errors. Then, create the PRNG for the messages sent from the server to the client. Test that and run the code multiple times to see if different responses are sent each time.
