/************************************************************************************************************
# Name          : chatclient.c
# Author        : Jack Harrington
# Date          : May 4, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of a chat client.
*************************************************************************************************************/

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "util.h"

int client_socket = -1;
char username[MAX_NAME_LEN+1] = {0};
char inbuf[BUFLEN+1];
char outbuf[MAX_MSG_LEN+1];
struct sockaddr_in server_addr;
socklen_t addrlen = sizeof(struct sockaddr_in);
fd_set socketset;

int handle_stdin();
int handle_client_socket();

int main(int argc, char *argv[]){
    /* Checks number of arguments. */
    if (argc != 3){
        printf("Usage: %s <server IP> <port>\n",argv[0]);
        return 0;
    }

    char * ip;
    int portInt;
    /* Checks for valid IP address. */
    if (inet_pton(AF_INET, argv[1],ip) < 1){
        fprintf(stderr,"Error: Invalid IP address \'%s\'\n",argv[1]);
        return errno;
    }

    /* Checks for valid ports. */
    if ((parse_int(argv[2],&portInt,"port number")) == false){
        return EXIT_FAILURE;
    }

    /* Checks if port is in the useable range. */
    if (portInt < 1024 || portInt > 65535){
        fprintf(stderr,"Error: Port must be in range [1024, 65535].\n");
        return EXIT_FAILURE;
    }

    /* Gets username within the correct character range. */ 
    while(strlen(username) == 0 || strlen(username) > MAX_NAME_LEN){
        /* Prompts for the username. */
        printf("Please enter a username: ");
        scanf("%s",username);
        if(strlen(username) > MAX_NAME_LEN){
            printf("Sorry, limit your username to %d characters.\n", MAX_NAME_LEN);
        }
    }

    /* Begins the connection. */
    printf("Hello, %s. Let's try to connect to server.\n",username);
    client_socket = socket(PF_INET, SOCK_STREAM, 0);
    /* Checks if the socket connection is correct. */
    if(client_socket == -1){
        fprintf(stderr,"Error: Failed to create socket. %s.\n", strerror(errno));
        return errno;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portInt);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    /* Connects to server and begins more error checking. */
    if(connect(client_socket, (struct sockaddr *) &server_addr, addrlen) == -1){
        fprintf(stderr,"Error: Failed to connect to server. %s.\n",strerror(errno));
        close(client_socket);
        return errno;
    }

    int receive = recv(client_socket,inbuf, BUFLEN,0);
    /* Error: failed to recieve message. */
    if(receive == -1){
        fprintf(stderr,"Error: failed to receive message from server. %s.\n",strerror(errno));
        close(client_socket);
        return errno;
    }

    /* Error: the server is full. */
    if(receive == 0){
        fprintf(stderr,"All connections are busy. Try again later.\n");
        close(client_socket);
        return 0;
    }

    inbuf[receive] = '\0';
    printf("%s\n",inbuf);
    send(client_socket, username, strlen(username), 0);
    /* Keeps chat running. */
    while(1){
        /* Prints messages and flushes stdout. */
        printf("[%s]: ",username);
        fflush(stdout);
        FD_ZERO(&socketset);
        FD_SET(client_socket,&socketset);
        FD_SET(0,&socketset);
        if (select(client_socket + 1, &socketset, NULL, NULL, NULL) < 0 && errno != EINTR) {
            fprintf(stderr, "Error: select() failed. %s.\n", strerror(errno));
            close(client_socket);
            return errno;
        }

        /* Recvieved user input. */
        if (FD_ISSET(0,&socketset)){
            handle_stdin();
        }

        /* Recieved message from server. */
        if (FD_ISSET(client_socket, &socketset)) {
            handle_client_socket();
        }
    }
    close(client_socket);
    return 0;
}

/**
 * @name handle_stdin()
 * @brief Handles the user input to send messages.
 * 
 * @return int 
 */
int handle_stdin(){
    memset(outbuf,0,sizeof(outbuf));
    int charcount = get_string(outbuf,MAX_MSG_LEN);
    /* Checks the length of user message. */
    if(charcount == TOO_LONG){
        fprintf(stderr,"Sorry, limit your message to %d characters.\n", MAX_MSG_LEN);
    }
    /* Quits upon entering "bye" */
    else if(strcmp(outbuf,"bye") == 0){
        printf("Goodbye.\n");
        close(client_socket);
        exit(0);
    }
    /* Completes the sending of a message. */
    else{
        send(client_socket,outbuf,strlen(outbuf),0);
    }
}

/**
 * @name handle_client_socket()
 * @brief Handles receiving messages from clients via the server.
 * 
 * @return int 
 */
int handle_client_socket(){
    int numrec = recv(client_socket,inbuf,BUFLEN,0);
    /* Error: failed to recieve message. */
    if(numrec == -1){
        fprintf(stderr,"\nWarning: Failed to receive incoming message. %s.\n",strerror(errno));
    }
    /* Error: server connection was lost. */
    else if(numrec == 0){
        fprintf(stderr,"\nConnection to server has been lost.\n");
        close(client_socket);
        exit(0);
    }
    /* Error: serrver initiated shutdown. */
    else{
        inbuf[numrec] = 0;
        if(strcmp(inbuf,"bye") == 0){
            fprintf(stderr,"\nServer initiated shutdown.\n");
            close(client_socket);
            exit(0);
        }
        /* Recieve message without error. */
        printf("\n%s\n",inbuf);
    }
}
