/************************************************************************************************************
# Name          : minishell.c
# Author        : Jack Harrington
# Date          : March 30, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of minishell. 
*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>
#include <limits.h>

#define BLUE    "\x1b[34:1m"
#define DEFAULT "\x1b[0m"
#define NUM_STRINGS 50
#ifndef MAX_BUF
#define MAX_BUF 200
#endif

volatile sig_atomic_t interrupter = 0;

/* Signal handler call. */
void sig_handler(int sig) {
    fprintf(stdout,"\n");
    interrupter = 1;
}

int main() {
    /* Prints blue minishell in terminal. */
    char path[MAX_BUF];
    char input[1024];
    char *token;
    char *arr[NUM_STRINGS];

    /* Installs the signal handler. */
    struct sigaction action;
    action.sa_handler = sig_handler;
    if(sigaction(SIGINT, &action, NULL) == -1){
        fprintf(stderr,"Error: Cannot register signal handler. %s.\n",strerror(errno));
    }

    /* Continues the print for the minishell. */
    while(1) {  
        getcwd(path, MAX_BUF);
        fprintf(stdout,"%s[%s%s%s]> ", DEFAULT, BLUE, path, DEFAULT);
        fflush(stdout);
        fgets(input, 1024, stdin);

        /* Checks if got current working directory. */
        char * dir = getcwd(NULL,0);
        if(dir == NULL){
            fprintf(stderr,"Error: Cannot get current working directory. %s.\n",strerror(errno));
        }
        free(dir);

        if(input == NULL && errno != 0){
            if(interrupter == 1){
                interrupter = 0;
                continue;
            }
            fprintf(stderr,"Error: Failed to read from stdin. %s. \n", strerror(errno));
        }

        /* Makes a string of tokens with delimter: " " */
        int i = 0;
        token = strtok(input, " ");
        while ( token != NULL ) {
            arr[i] = token;
            token = strtok(NULL, " ");
            i++;
        }     
        
        /* Used to handle the '\n' at the end of comparison strings. */
        arr[i-1] = strtok(arr[i-1], "\n");
        arr[i] = NULL;

        /* Implementation of 'exit' command. */
        if (strcmp(arr[0], "exit") == 0) {
            break;
        }

        /* Implementation of 'cd' command. */
        else if ((strcmp(arr[0], "cd")) == 0) {

            /* Checks the number of args for cd. */
            if (i > 2) {
                fprintf(stderr, "Error: too many arguments to cd.\n");
                continue;
            }
            /* Cannot get the pwuid or user input was "~" */
            else if (arr[1] == NULL || (strcmp(arr[1], "~") == 0) || (strcmp(arr[1], "~\n") == 0)) {
                uid_t uid = getuid();
                struct passwd *pw = getpwuid( uid );
                if (pw == NULL) {
                    fprintf(stderr,"Error: Cannot get passwd entry. %s.\n",strerror(errno));
                }else{
                    chdir(pw->pw_dir);
                }
                continue;
            }
            /* If the user entered correct "cd" fields. */
            else {
                int result = chdir(arr[1]);
                if(result == -1) {
                    fprintf(stderr,"Error: Cannot change directory to \'%s\'. %s.\n",arr[1], strerror(errno));
                }
                continue;
            }
        }

        /* Exec commands and fork(). */
        else {
            pid_t id;
            if((id = fork()) == 0){
                int ex = execvp(arr[0], arr);
                if (ex == -1) {
                    fprintf(stderr,"Error: exec() failed. %s.\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                else {
                    exit(EXIT_SUCCESS);
                }
            }
            else if(id < 0) {
                fprintf(stderr,"Error: fork() failed. %s.\n",strerror(errno));
            }
            pid_t w = wait(&id);
            if(w == -1){
                fprintf(stderr,"Error: wait() failed. %s.\n",strerror(errno));
            }
        }
    }
    return EXIT_SUCCESS;
}