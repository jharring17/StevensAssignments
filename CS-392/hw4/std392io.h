/************************************************************************************************************
# Name          : std392io.h
# Author        : Jack Harrington
# Date          : March 26, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Header file for std392io.c
*************************************************************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

int output(char*, char, void*);
int input(char*, char, void*);
int clean();
