/************************************************************************************************************
# Name          : spfind.c
# Author        : Jack Harrington
# Date          : April 20, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of pfind with pipes. 
*************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char * argv[]){
    /* Checks argument count. */
    if (argc == 1){
        write(1,"Usage: ./spfind -d <directory> -p <permissions string>\n",55);
        return EXIT_SUCCESS;
    }
    
    /* Creates pipes between parent and children (same as in class). */
    pid_t ret[2];
    int c1_c2[2];
    int c2_p[2];

    /* If (pipe < 0) then report error. */
    if (pipe(c1_c2) < 0 || pipe(c2_p) < 0){
        fprintf(stderr, "Error: Cannot create pipe.\n");
        return EXIT_FAILURE;
    }

    /* ------First Child------ */
    ret[0] = fork();
    if (ret[0] == 0) {
        /* Error check the pipe. */
        if(dup2(c1_c2[WRITE_END],1) < 0){
            fprintf(stderr, "Error: dup2 failed.\n");
            exit(EXIT_FAILURE);
        }
        /* Close unnecessary ends of pipes (same as in class). */
        close(c1_c2[READ_END]);
        close(c2_p[READ_END]);
        close(c2_p[WRITE_END]);
        /* Run pfind in write end of c1_c2. */
        char ** newargv = (char**)malloc(sizeof(char**) * (argc+1));
        newargv[0] = "./pfind";
        for(int i = 1; i < argc; i++){
            newargv[i] = argv[i];
        }
        newargv[argc] = NULL;
        char * cwd = getcwd(NULL,0);
        /* Gets amd checks current working directory. */
        if(cwd == NULL){
            fprintf(stderr, "Error: Couldn't get cwd.\n");
            exit(EXIT_FAILURE);
        }
        /* If pfind fails.*/
        if(execvp("./pfind",newargv) < 0){
            fprintf(stderr,"Error: pfind failed.\n");
            free(newargv);
            free(cwd);
            exit(EXIT_FAILURE);
        }
        free(newargv);
        free(cwd);
        exit(EXIT_SUCCESS);
    }
    /* If the fork fails. */
    else if (ret[0] < 0){
        fprintf(stderr, "Error: fork failed.\n");
        return EXIT_FAILURE;
    }

    /* ------Second Child------ */
    ret[1] = fork();
    if (ret[1] == 0) {
        if(dup2(c1_c2[READ_END],0) < 0 || dup2(c2_p[WRITE_END],1) < 0){
            fprintf(stderr, "Error: dup2 failed.\n");
            exit(EXIT_FAILURE);
        }
        /* Close unnecessary ends of pipes (same as in class). */
        close(c1_c2[WRITE_END]);
        close(c2_p[READ_END]);
        char pidstr[10] = {0};
        if (sprintf(pidstr,"%d",getpid()) < 0){
            fprintf(stderr, "Error: sprintf failed.\n");
        }
        char * fullstr = malloc(11 + strlen(pidstr));
        if(fullstr == NULL){
            fprintf(stderr,"Error: malloc failed.\n");
        }
        strcpy(fullstr,"/proc/");
        strcat(fullstr,pidstr);
        strcat(fullstr,"/fd/0");
        char * sorted[3] = {"sort", fullstr, NULL};
        /* Checks if sorted worked. */
        if(execvp("sort", sorted) == -1){
            fprintf(stderr, "Error: sort failed.\n");
            free(fullstr);
            exit(EXIT_FAILURE);
        }
        free(fullstr);
        exit(EXIT_SUCCESS);
    } 
    /* Check for failed fork.*/
    else if(ret[1] < 0){
        fprintf(stderr, "Error: fork failed.\n");
        return EXIT_FAILURE;
    }

    /* Close unnecessary ends of pipes (same as in class). */
    close(c1_c2[READ_END]);
    close(c1_c2[WRITE_END]);
    close(c2_p[WRITE_END]);
    
    /* Reaps the child processes. */
    while (wait(NULL) > 0);
    
    /* Print to terminal. */
    char c;
    while (read(c2_p[READ_END], &c, 1) > 0){
        printf("%c", c);
    }
    return EXIT_SUCCESS;
}