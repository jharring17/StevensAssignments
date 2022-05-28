/************************************************************************************************************
# Name          : std392io.c
# Author        : Jack Harrington
# Date          : March 26, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of an input/output library. 
*************************************************************************************************************/
#include "std392io.h"

/**
 * @brief std392io.c output function
 * 
 * @param filename - name of provided file 
 * @param format - string or integer data format
 * @param data - provided data
 * @return * int 
 */
int output(char* filename, char format, void* data){
    int fd;
    
    /* Checks if there is a provided file. */
    if (strcmp(filename,"") == 0){
        fd = 1;
    }
    /* Opens and creates new file. */
    else{
        fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);
    }
    
    /* Checks for null data. */
    if (data == NULL){
        errno = EIO;
        return -1;
    }
    
    /* --------------Formatting Data--------------*/ 
    
    /* Integer formatted data. */
    if (format == 'd'){
        int num = *((int*)data);
        int dif = num;
        int numlen = 0;
        int isnegative = 0;
        
        if (num < 0){
            num *= -1;
            isnegative = 1;
        }

        /* Gets the number of digits. */
        while(dif != 0){
            dif = dif / 10;
            numlen++;
        }
        
        /* Increments num when 0. */
        if(num == 0){
            numlen++;
        }

        /* Creates temp storage arrray. */
        char * temp = (char*)malloc(numlen + 1);
        dif = num;
        temp[numlen] = 0;
       
        /* Preforms int to char conversion. */
        for(int i = numlen - 1; i >= 0; i--){
            char currnum = (dif % 10) + '0';
            temp[i] = currnum;
            dif = dif / 10;
        }

        /* Adds negative if needed. */
        if(isnegative == 1){
            char * newtemp = malloc(numlen + 2);
            newtemp[0] = '-';
            strcat(newtemp,temp);
            free(temp);
            temp = newtemp;
        }
        
        if(strcmp(temp,"") == 0){
            free(temp);
            errno = EIO;
            return -1;
        }

        write(fd, temp, strlen(temp));
        write(fd,"\n", 1);
        free(temp);
    
    /* String formatted data. */
    }else if (format == 's') {
        /* Typecast data to string. */
        char *ptr = (char *)data;
        size_t len = strlen(ptr);
        write(fd,ptr,len);
        write(fd,"\n", 1);
    
    /* If incorrect format given. */
    }else{
        errno = EIO;
        return -1;
    }
    return 0;
}

/**
 * @brief std392io.c input function
 * 
 * @param filename - name of provided file 
 * @param format - string or integer data format
 * @param data - provided data 
 * @return int 
 */
int input(char* filename, char format, void* data){
    /* If no data exists. */
    if(data == NULL){
        return 0;
    }
    /* If data exists. */
    else {
        int fd;
        if (strcmp(filename,"") == 0){
            fd = 0;
        } 
        else{
            /* Checks if the file is open. */
            int openstatus = -1;
            int pid = getpid();
            int pidLength = 0;

            /* Used to get file stats. */
            struct stat stbuf1;
            struct stat *buf1 = &stbuf1;
            stat(filename,buf1);
            ino_t inode1 = buf1->st_ino;
            struct stat stbuf2;
            struct stat *buf2 = &stbuf2;
            struct dirent *dirp;
            
            while(pid != 0){
                pid = pid / 10;
                pidLength++;
            }
            pid = getpid();
            char * pidstr = (char*)malloc(pidLength + 1);
            for(int i = pidLength - 1; i >= 0; i--){
                int pidnum = pid % 10;
                pid = pid / 10;
                pidstr[i] = pidnum + '0';
            }
            pidstr[pidLength] = 0;
            
            /* Makes the path string. */
            char * pathString = malloc(pidLength + 11);
            strcpy(pathString, "/proc/");
            strcat(pathString, pidstr);
            strcat(pathString, "/fd/");
            DIR * dp = opendir(pathString);
            
            //checks if directory can correctly be opened (which it should)
            if (dp == NULL){
                free(pidstr);
                free(pathString);
                errno = EIO;
                return -1;
            }
            
            while((dirp = readdir(dp)) != NULL){
                if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0 && strcmp(dirp->d_name,"0") != 0 && strcmp(dirp->d_name,"1") != 0 && strcmp(dirp->d_name,"2") != 0 ){;
                    fstat(atoi(dirp->d_name),buf2);
                    ino_t inode2 = buf2->st_ino;
                    if (inode1 == inode2){
                        openstatus = atoi(dirp->d_name);
                        break;
                    }
                }
            }
            free(pathString);
            free(pidstr);
            closedir(dp);
            if (openstatus != -1){
                fd = openstatus;
            }else{
                fd = open(filename,O_RDONLY);
            }
        }

        char * array = malloc(128);
        memset(array, 0, 128);
        char letter[1];
        size_t index = 0;
        size_t arrsize = 128;
        ssize_t result;
        if (fd == -1){
            errno = ENOENT;
            return -1;
        }
        
        while(1){
            result = read(fd, letter, 1);
            if (letter[0] == '\n' || result == 0){
                if(strlen(array) == 0){
                    free(array);
                    return -1;
                }
                break;
            }
            array[index] = letter[0];
            index++;
            /* Resize the array. */
            if (index == arrsize){
                arrsize += 128;
                char * temp = malloc(arrsize);
                strcpy(temp,array);
                free(array);
                array = temp;
                memset(array + arrsize-128, 0, 128);
            }
        }

        /* Format string case. */
        if(format == 's'){
            strcpy((char*)data, array);
        }
        /* Format integer case. */
        else if (format == 'd'){
            //convert string to int
            int properlyformatted = 1;
            *((int*)data) = atoi(array);
        }
        /* Incorrect format case. */
        else{
            free(array);
            errno = EIO;
            return -1;
        }
        free(array);
    }
    return 0;
}

/**
 * @brief std392io.c clean function
 * 
 * @return int 
 */
int clean(){
    int pid = getpid();
    int pidLength = 0;
    while(pid != 0){
        pid = pid / 10;
        pidLength++;
    }
    /* Gets the length of the PID. */
    pid = getpid();
    char * PIDstr = (char*)malloc(pidLength + 1);
    for(int i = pidLength - 1; i >= 0; i--){
        int pidnum = (pid % 10);
        pid = (pid / 10);
        PIDstr[i] = pidnum + '0';
    }
    PIDstr[pidLength] = 0;

    /* Creates the path for the file. */
    char * fullstr = (char*)malloc(pidLength + 11);
    strcpy(fullstr, "/proc/");
    strcat(fullstr, PIDstr);
    strcat(fullstr, "/fd/");
    DIR * dp = opendir(fullstr);
    
    /* Checks if valid dir. */
    if (dp == NULL){
        free(PIDstr);
        free(fullstr);
        errno = EIO;
        return -1;
    }

    /* Closes all descriptors. */
    struct dirent *dirp;
    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0 && strcmp(dirp->d_name,"0") != 0 && strcmp(dirp->d_name,"1") != 0 && strcmp(dirp->d_name,"2") != 0 ){;
            close(atoi(dirp->d_name));
        }
    }
    /* Closes and frees all allocated memory. */
    closedir(dp);
    free(PIDstr);
    free(fullstr);
    return 0;
}