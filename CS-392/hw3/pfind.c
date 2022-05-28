/************************************************************************************************************
# Name          : pfind.c
# Author        : Jack Harrington
# Date          : March 6, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of pfind in c. 
*************************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

/* pfind function declaration. */
void pfind(char* dir, char* pString);

int main(int argc, char const *argv[]) {
    /* Makes a string for user inputted string. */
    char* usrInput = (char *)argv[2];

    /* Checks the number of elements in the user inputted string. */
    if (strlen(usrInput) != 9) {
        printf("Error: Permission string '%s' is invalid.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    /* usrInput formatting: (rwxrwxrwx) */
    /* Checks for valid user input, */
    for (int i = 0; i < strlen(usrInput); i++) {
        switch(usrInput[i]) {
            /* Case for input 'r'. */
            case 'r' :
            if (i == 0 || i == 3 || i == 6) {
                break;
            } else {
                printf("Error: Permission string '%s' is invalid.\n", argv[2]);
                exit(EXIT_FAILURE);

            }
            break;

            /* Case for input 'w'. */
            case 'w' :
            if (i == 1 || i == 4 || i == 7) {
                break;
            } else {
                printf("Error: Permission string '%s' is invalid.\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            break;
            
            /* Case for input 'x'. */
            case 'x' :
            if (i == 2 || i == 5 || i == 8) {
                break;
            } else {
                printf("Error: Permission string '%s' is invalid.\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            break;

            /* Case for '-'. */
            case '-' :          /* Postition in string does not matter. */
            break;

            /* Else case. */
            default :
            printf("Error: Permission string '%s' is invalid.\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }
   
    /* Call of the pfind function. */
    pfind((char *)argv[1], (char *)argv[2]);
    return 0;
}

/**
 * 
 * @name pfind 
 * @brief Recurses through directories and prints files with matching permissions.
 * 
 * @param dir - user entered directory. 
 * @param pString - searched permission string.
 * @return char* - string of files.
 */
void pfind(char* dir, char* pString) {
    /* Makes the directory pointer. */
    DIR* dp = opendir(dir);
    
    /* Checks if the passed directory exists. */
    if (dp == NULL) {
        printf("Error: Cannot open directory '%s'. Permission denied.\n", dir);
        exit(EXIT_FAILURE);
    }
    
    /* Struct declarations. */
    struct stat statBuffer;
    struct stat *buffer = &statBuffer;
    struct dirent *dirPointer;
    
    chdir(dir);
    while((dirPointer = readdir(dp)) != NULL){
        if (strcmp(dirPointer -> d_name, ".") != 0 && strcmp(dirPointer -> d_name, "..") != 0) {
            stat(dirPointer -> d_name, buffer);
            if (S_ISDIR(buffer -> st_mode)) {
                pfind(dirPointer -> d_name, pString);
                chdir("..");
            } else {
                /* File permissions. */
                char * str = (char*)malloc(9);
                for (int i = 0; i < 9; i++) {
                    str[i] = '-';
                }
                if (S_IRUSR & buffer -> st_mode) {
                    str[0] = 'r';
                }
                if (S_IWUSR & buffer -> st_mode) {
                    str[1] = 'w';
                }
                if (S_IXUSR & buffer -> st_mode) {
                    str[2] = 'x';
                }
                if (S_IRGRP & buffer -> st_mode) {
                    str[3] = 'r';
                }
                if (S_IWGRP & buffer -> st_mode) {
                    str[4] = 'w';
                }
                if (S_IXGRP & buffer -> st_mode) {
                    str[5] = 'x';
                }
                if (S_IROTH & buffer -> st_mode) {
                    str[6] = 'r';
                }
                if (S_IWOTH & buffer -> st_mode) {
                    str[7] = 'w';
                }
                if (S_IXOTH & buffer -> st_mode) {
                    str[8] = 'x';
                }
                
                /* Print directory string. */
                if (strcmp(str, pString) == 0) {
                    char cwd[1000];
                    getcwd(cwd,1000);
                    printf("%s/%s\n", cwd, dirPointer -> d_name);
                }
                free(str);
            }
        }
    }
    closedir(dp);
}
