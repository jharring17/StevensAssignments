/************************************************************************************************************
# Name          : sort.c
# Author        : Jack Harrington
# Date          : February 18, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of sort using pointers in c. 
*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "mergesort.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    char *file;
    int opt;
    int check = 0; 
    int checkFiles = 0;
    int iCount = 0; 
    int dCount = 0; 
    
    /* Iterates through user inputted flag options */
    while((opt = getopt(argc, argv, ":id")) != -1) {
        switch(opt) {
            /* Flag 'i' case */
            case 'i': 
                iCount++; 
                if(argv[optind] != NULL && argv[optind + 1] != NULL) {
                    checkFiles = 1;
                } 
                else if(argv[optind] == NULL) {
                    check = 1;
                } 
                else {
                    file = (char*) malloc(strlen(argv[optind]) * sizeof(char));
                    strcpy(file, argv[optind]);
                    fp = fopen(file, "r");
                }
                break;
            
            /* Flag 'd' case */
            case 'd': 
                dCount++; 
                if(argv[optind] != NULL && argv[optind + 1] != NULL) {
                    checkFiles = 1;
                } 
                else if(argv[optind] == NULL) {
                    check = 1;
                } 
                else {
                    file = (char*) malloc(strlen(argv[optind]) * sizeof(char));
                    strcpy(file, argv[optind]);
                    fp = fopen(file, "r");
                }
                break;
            
            /* Unknown flag case */
            case '?':
                printf("Error: unkown option '-%c' recieved.\nUsage: ./sort [-i|-d] filename\n-i: Specifies the file contains ints.\n-d: Specifies the file contains doubles.\nfilename: The file to sort.\n", optopt);
                return EXIT_FAILURE;
        }
    }

    /* Check too many flags */
    if(iCount + dCount > 1 ){
        fprintf(stderr, "Error: Too many flags specified.\n");
        return EXIT_FAILURE;
    }
    /* Check for too many files */
    if(checkFiles){
        fprintf(stderr, "Error: Too many files specified.\n");
        return EXIT_FAILURE;
    }

    /* Check for no file input */
    if(check){
        fprintf(stderr, "Error: No input file specified.\n");
        return EXIT_FAILURE;
    }

    /* Check for no arguments */
    if(argc == 1){ 
        printf("Usage: ./sort [-i|-d] filename\n-i: Specifies the file contains ints.\n-d: Specifies the file contains doubles.\nfilename: The file to sort.\n");
        return EXIT_FAILURE;
    }

    /* Check if filename exists */
    if(fp == NULL){
        fprintf(stderr, "Error: Cannot open '%s'. %s.\n", file, strerror(errno));
        free(file);
        return EXIT_FAILURE;
    }


    int lc = 0;
    char c;
    for(c = getc(fp); c != EOF; c = getc(fp)){
        if(c == '\n'){
            lc++;
        }
    }

    if(iCount) {
        fclose(fp);
        fp = fopen(file, "r");
        int* arr = (int*) malloc(lc * sizeof(int));
        for(int i = 0; i < lc; i++){
            fscanf(fp, "%d", &arr[i]);
        }
        mergesort(arr, lc, sizeof(int), int_cmp);
        for(int i = 0; i < lc; i++){
            printf("%d\n", arr[i]);
        }
        free(arr);
    } 
    else if (dCount) {
        double* arr = (double*) malloc(lc * sizeof(double));
        fclose(fp);
        fp = fopen(file, "r");
        for(int i = 0; i < lc; i++){
            fscanf(fp, "%lf", &arr[i]);
        }
        mergesort(arr, lc, sizeof(double),dbl_cmp);
        
        for(int i = 0; i < lc; i++){
            printf("%lf\n", arr[i]);
        }
        free(arr);
    }

    free(file);
    fclose(fp);
    return EXIT_SUCCESS;
}