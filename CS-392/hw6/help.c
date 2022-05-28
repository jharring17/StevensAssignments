/*
#############################################################################
#__/                         .- -. -.. .-. . .--                         \__#
#                          Andrew McCauley: CS 392                          #
#__   I pledge my honor that I have abided by the Stevens Honor System.   __#
#  \                   -- -.-. -.-. .- ..- .-.. . -.--                   /  #
#############################################################################
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define READ_END 0
#define WRITE_END 1
int main(int argc, char * argv[]){
    //checks whether or not to print usage
    if (argc == 1){
        write(1,"Usage: ./spfind -d <directory> -p <permissions string>\n",55);
        return EXIT_SUCCESS;
    }
    //Create pipes between child processes and to parent
    pid_t ret[2];
    int c1_c2[2];
    int c2_p[2];

    if (pipe(c1_c2) < 0 || pipe(c2_p) < 0){
        write(2, "Error: pipe failed.\n",20);
        return EXIT_FAILURE;
    }
    //First child process: run pfind and output in write end of c1_c2
    ret[0] = fork();
    if (ret[0] == 0) {
        if(dup2(c1_c2[WRITE_END],1) < 0){
            write(2, "Error: dup2 failed.\n",20);
            exit(EXIT_FAILURE);
        }
        close(c1_c2[READ_END]);
        close(c2_p[READ_END]);
        close(c2_p[WRITE_END]);
        char ** newargv = (char**)malloc(sizeof(char**) * (argc+1));
        newargv[0] = "./pfind";
        for(int i = 1; i < argc; i++){
            newargv[i] = argv[i];
        }
        newargv[argc] = NULL;
        char * cwd = getcwd(NULL,0);
        if(cwd==NULL){
            write(2, "Error: Couldn't get cwd\n",24);
            exit(EXIT_FAILURE);
        }
        //check if pfind works
        if(execvp("./pfind",newargv) < 0){
            write(2,"Error: pfind failed.\n",21);
            free(newargv);
            free(cwd);
            exit(EXIT_FAILURE);
        }
        free(newargv);
        free(cwd);
        exit(EXIT_SUCCESS);
    } //Check if fork failed 
    else if (ret[0] < 0){
        write(2, "Error: fork failed.\n",20);
        return EXIT_FAILURE;
    }
    //Second child process: take input from c1_c2 pipe, run sort on input, and output to c2_p pipe
    ret[1] = fork();
    if (ret[1] == 0) {
        if(dup2(c1_c2[READ_END],0) < 0 || dup2(c2_p[WRITE_END],1) < 0){
            write(2, "Error: dup2 failed.\n",20);
            exit(EXIT_FAILURE);
        }
        close(c1_c2[WRITE_END]);
        close(c2_p[READ_END]);
        //Create string to processes "stdout" (really pipe) file
        char pidstr[10] = {0};
        if (sprintf(pidstr,"%d",getpid()) < 0){
            write(2, "Error: sprintf failed.\n",23);
        }
        char * fullstr = malloc(11 + strlen(pidstr));
        if(fullstr == NULL){
            write(2,"Error: malloc failed.\n",22);
        }
        strcpy(fullstr,"/proc/");
        strcat(fullstr,pidstr);
        strcat(fullstr,"/fd/0");;
        char * sortarray[3] = {"sort",fullstr,NULL};
        //check if sort worked
        if(execvp("sort",sortarray) == -1){
            write(2, "Error: sort failed.\n",20);
            free(fullstr);
            exit(EXIT_FAILURE);
        }
        free(fullstr);
        exit(EXIT_SUCCESS);
    } // Check if fork failed
    else if(ret[1] < 0){
        write(2, "Error: fork failed.\n",20);
        return EXIT_FAILURE;
    }
    //Parent process: read sort's output and print to console
    close(c1_c2[READ_END]);
    close(c1_c2[WRITE_END]);
    close(c2_p[WRITE_END]);
    //wait for both child processes to finish
    while (wait(NULL) > 0);
    char c;
    //print to stdout
    while (read(c2_p[READ_END], &c, 1) > 0){
        printf("%c", c);
    }
    return EXIT_SUCCESS;
}