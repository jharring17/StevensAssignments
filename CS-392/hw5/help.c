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

#define BLUE    "\x1b[34:1m"
#define DEFAULT "\x1b[0m"
#define NUM_STRINGS 50
#ifndef MAX_BUF
#define MAX_BUF 200
#endif

int main() {
    char path[MAX_BUF];
    char input[100];
    char *arr[NUM_STRINGS];

    while(1) {
        getcwd(path, MAX_BUF);
        printf("%s[%s]> %s", BLUE, path, DEFAULT);
        scanf("%s", input);
    
        int i = 0;
        char * token = strtok(input, " ");
        while ( token != NULL ) {
            strcpy(arr[i], token);
            token = strtok(NULL, " ");
            i++;
        }
        
    
    
    
    
    
    
    
    
    
    }




return 0;
}