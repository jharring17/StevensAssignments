/*
#############################################################################
#__/                         .- -. -.. .-. . .--                         \__#
#                          Andrew McCauley: CS 392                          #
#__   I pledge my honor that I have abided by the Stevens Honor System.   __#
#  \                   -- -.-. -.-. .- ..- .-.. . -.--                   /  #
#############################################################################
*/
#include "std392io.h"
int output(char* filename, char format, void* data){
    int fd;
    //Determines whether or not to print to console
    if (strcmp(filename,"") == 0){
        fd = 1;
    }
    //Opens file, creating new one if needed.
    else{
        fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP);
    }
    //Checks whether data is NULL or not
    if (data == NULL){
        errno = EIO;
        return -1;
    }
    //If format is an integer
    if (format == 'd'){
        int num = *((int*)data);
        int dif = num;
        int numlen = 0;
        int isnegative = 0;
        //checks if negative number is given
        if (num < 0){
            num *= -1;
            isnegative = 1;
        }
        //Number of digits in provided number
        while(dif != 0){
            dif = dif / 10;
            numlen++;
        }
        //Takes care of special case where number given is 0
        if(num == 0){
            numlen++;
        }
        //makes array to put digits in
        char * temp = (char*)malloc(numlen + 1);
        dif = num;
        temp[numlen] = 0;
        //converts ints to chars
        for(int i = numlen - 1; i >= 0; i--){
            char currnum = (dif % 10) + '0';
            temp[i] = currnum;
            dif = dif / 10;
        }
        //Adds negative sign if number is negative
        if(isnegative == 1){
            char * newtemp = malloc(numlen + 2);
            newtemp[0] = '-';
            strcat(newtemp,temp);
            free(temp);
            temp = newtemp;
        }
        //Checks if null (error in input), freeing temp array as needed
        if(strcmp(temp,"") == 0){
            free(temp);
            errno = EIO;
            return -1;
        }
        //Prints int
        write(fd, temp, strlen(temp));
        write(fd,"\n", 1);
        free(temp);
    }else if(format == 'f'){
        float num = *((float*)data);
        int strl = 0;
        int negative = 0;
        //Checks if float is negative
        if(num < 0){
            negative = 1;
            num *= -1;
        }
        float tempnum = num;
        //gets number of digits
        int numdigits = 0;
        float ten = 10;
        while(tempnum >= 1){
            tempnum = tempnum/ten;
            numdigits++;
            strl++;
        }
        char * temp = (char*)malloc(strl + 8);
        //converts number to string
        gcvt(num,6 + numdigits,temp);
        int addzeros = 0;
        if(temp[strl] == 0){
            temp[strl] = '.';
            addzeros = 1;
        }
        //fills in extra zeros if needed
        for(int i = strl + 1; i < strl + 7; i++){
            if(addzeros == 1){
                temp[i] = '0';
            }else{
                if(temp[i] == 0){
                    temp[i] = '0';
                    addzeros = 1;
                }
            }
        }
        //Adds negative sign if needed
        if(negative == 1){
            char * newtemp = (char*)malloc(strl + 9);
            strcpy(newtemp,"-");
            strcat(newtemp,temp);
            free(temp);
            temp = newtemp;
        }
        //cleans up
        write(fd, temp, strlen(temp));
        write(fd,"\n", 1);
        free(temp);
    }else if (format == 's'){
        //converts data into string
        char *ptr = (char *)data;
        size_t len = strlen(ptr);
        //prints string
        write(fd,ptr,len);
        write(fd,"\n", 1);
    }else{
        //incorrect case given
        errno = EIO;
        return -1;
    }
    return 0;
}


int input(char* filename, char format, void* data){
    //null data, then do nothing
    if(data == NULL){
        return 0;
    }
    int fd;
    //determines whether or not to use keyboard input.
    if (strcmp(filename,"") == 0){
        fd = 0;
    } else{
        //checks if file is already opened
        int alreadyopen = -1;
        int pid = getpid();
        int pidlen = 0;
        while(pid != 0){
            pid = pid / 10;
            pidlen++;
        }
        pid = getpid();
        char * pidstr = (char*)malloc(pidlen + 1);
        for(int i = pidlen - 1; i >= 0; i--){
            int pidnum = pid % 10;
            pid = pid / 10;
            pidstr[i] = pidnum + '0';
        }
        pidstr[pidlen] = 0;
        //constructs string to path with all fds for current process
        char * fullstr = malloc(pidlen + 11);
        strcpy(fullstr,"/proc/");
        strcat(fullstr,pidstr);
        strcat(fullstr,"/fd/");
        DIR * dp = opendir(fullstr);
        //checks if directory can correctly be opened (which it should)
        if (dp == NULL){
            free(pidstr);
            free(fullstr);
            errno = EIO;
            return -1;
        }
        //Gets stats of file given to get inode
        struct stat stbuf1;
        struct stat *buf1 = &stbuf1;
        stat(filename,buf1);
        ino_t inode1 = buf1->st_ino;
        //Sets up buffer to be used in while loop
        struct stat stbuf2;
        struct stat *buf2 = &stbuf2;
        struct dirent *dirp;
        while((dirp = readdir(dp)) != NULL){
            if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0 && strcmp(dirp->d_name,"0") != 0 && strcmp(dirp->d_name,"1") != 0 && strcmp(dirp->d_name,"2") != 0 ){;
                //gets stats from file descriptor and compares inode with file provided
                fstat(atoi(dirp->d_name),buf2);
                ino_t inode2 = buf2->st_ino;
                //if file is already opened, sets alreadyopen to file descriptor, which fd will become later
                if (inode1 == inode2){
                    alreadyopen = atoi(dirp->d_name);
                    break;
                }
            }
        }
        free(fullstr);
        free(pidstr);
        closedir(dp);
        if (alreadyopen != -1){
            fd = alreadyopen;
        }else{
            fd = open(filename,O_RDONLY);
        }
    }
    if (fd == -1){
        errno = ENOENT;
        return -1;
    }
    char * arr = malloc(128);
    memset(arr, 0, 128);
    char letter[1];
    size_t index = 0;
    size_t arrsize = 128;
    ssize_t result;
    //Reads line
    while(1){
        //Read character in current line
        result = read(fd, letter, 1);
        //If end of line or EOF, break to print or return EOF if nothing to print
        if (letter[0] == '\n' || result == 0){
            if(strlen(arr) == 0){
                free(arr);
                return -1;
            }
            break;
        }
        arr[index] = letter[0];
        index++;
        //If array is full, resize by 128 bytes
        if (index == arrsize){
            arrsize += 128;
            char * temp = malloc(arrsize);
            strcpy(temp,arr);
            free(arr);
            arr = temp;
            memset(arr+arrsize-128, 0, 128);
        }
    }
    if(format == 's'){
        //copy array to data pointer
        strcpy((char*)data, arr);
    }else if (format == 'd'){
        //convert string to int
        int properlyformatted = 1;
        *((int*)data) = atoi(arr);
    }else if (format == 'f'){
        //convert string to float
        *((float*)data) = atof(arr);
    }else{
        //incorrect case given, do nothing with arr
        free(arr);
        errno = EIO;
        return -1;
    }
    free(arr);
    return 0;
}


int clean(){
    //gets process id, and converts it to string
    int pid = getpid();
    int pidlen = 0;
    while(pid != 0){
        pid = pid / 10;
        pidlen++;
    }
    pid = getpid();
    char * pidstr = (char*)malloc(pidlen + 1);
    for(int i = pidlen - 1; i >= 0; i--){
        int pidnum = pid % 10;
        pid = pid / 10;
        pidstr[i] = pidnum + '0';
    }
    pidstr[pidlen] = 0;
    //constructs string to path with all fds for current process
    char * fullstr = (char*)malloc(pidlen + 11);
    strcpy(fullstr,"/proc/");
    strcat(fullstr,pidstr);
    strcat(fullstr,"/fd/");
    DIR * dp = opendir(fullstr);
    //checks if directory can correctly be opened (which it should)
    if (dp == NULL){
        free(pidstr);
        free(fullstr);
        errno = EIO;
        return -1;
    }
    //Closes all file descriptors except console-related ones (stdin, stdout, stderr), and excludes "." and ".."
    struct dirent *dirp;
    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name,".") != 0 && strcmp(dirp->d_name,"..") != 0 && strcmp(dirp->d_name,"0") != 0 && strcmp(dirp->d_name,"1") != 0 && strcmp(dirp->d_name,"2") != 0 ){;
            close(atoi(dirp->d_name));
        }
    }
    closedir(dp);
    free(pidstr);
    free(fullstr);
    return 0;
}
