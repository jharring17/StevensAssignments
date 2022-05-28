/************************************************************************************************************
# Name          : mergesort.c
# Author        : Jack Harrington
# Date          : February 18, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Implementation of mergesort using pointers in c. 
*************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include "mergesort.h"                  /* Contains function declarations */

/* Definitions for comparisons */
#define EQUAL (0)
#define A_GREATER (1)
#define B_GREATER (-1)

/**
 * @name int_cmp
 * @brief Integer comparison function
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int int_cmp(const void* a, const void* b){
    /* Comparison of ints 'a' and 'b' */
    if(*(int*)a == *(int*)b) {             /* when a == b */ 
        return EQUAL;
    }
    else if (*(int*)a > *(int*)b) {        /* when a > b */
        return A_GREATER;
    } 
    else {                                 /* when b > a */
        return B_GREATER; 
    }
}

/**
 * @name dbl_cmp
 * @brief Double comparison function
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int dbl_cmp(const void* a, const void* b){
    if(*(double*)a == *(double*)b){         /* when a == b */
        return EQUAL;
    }
    else if(*(double*)a > *(double*)b){     /* when a > b */
        return A_GREATER;
    }                                       
    else {                                  /* when b > a */
        return B_GREATER; 
    }
}

/**
 * @name doMerge
 * @brief Helper function for mergesort algorithm
 * 
 * @param array 
 * @param left 
 * @param middle 
 * @param right 
 * @param len 
 * @param elem_sz 
 * @param comp 
 */
void doMerge(void* array, int left, int middle, int right, size_t len, size_t elem_sz, int (*comp)(const void*, const void*)){
    int x, y, z;

    /* If input is int */
    if(elem_sz == sizeof(int)) {
        int *result = (int*) array; 
        int* temp = (int*) malloc(len * sizeof(int));

        for (x = left, y = (middle + 1), z = left; x <= middle && y <= right; z++) {
            if (comp((char*)array + (x* elem_sz), (char*)array + (y * elem_sz)) <= 0) {
                temp[z] = result[x++];
            } else {
                temp[z] = result[y++];
            }
        }
        while (x <= middle) {
            temp[z++] = result[x++];
        }
        while (y <= right) {
            temp[z++] = result[y++];
        }
        for (z = left; z <= right; z++) {
            result[z] = temp[z];
        }
        free(temp);

    } else {
        /* If input is double */
        double* result = (double*) array; 
        double* temp = (double*) malloc(len * sizeof(double));

        for(x = left, y = (middle + 1), z = left; x <= middle && y <= right; z++) {
            if(comp((char*)array + (x* elem_sz), (char*)array + (y * elem_sz)) <= 0) {
                temp[z] = result[x++];
            } else {
                temp[z] = result[y++];
            }
        }
        while(x <= middle) {
            temp[z++] = result[x++];
        }
        while(y <= right) {
            temp[z++] = result[y++];
        }

        for(z = left; z <= right ; z++) {
            result[z] = temp[z];
        }
        free(temp);
    }
}

/**
 * @name sort
 * @brief Sorts the given array
 * 
 * @param array 
 * @param len 
 * @param elem_sz 
 * @param l 
 * @param r 
 * @param comp 
 * @return * void 
 */
void sort(void* array, size_t len, size_t elem_sz, int l, int r, int (*comp)(const void*, const void*)){
    int temp;
    
    if (l < r) {
        temp = ((l + r) / 2);
        sort(array, len, elem_sz, l, temp, comp);
        sort(array, len, elem_sz, temp + 1, r, comp);
        doMerge(array, l, temp, r, len, elem_sz, comp);
    } 
    else {
        return;
    }
}

/**
 * @name mergesort
 * @brief Performs mergesort utilizing above helper functions
 * 
 * @param array 
 * @param len 
 * @param elem_sz 
 * @param comp 
 */
void mergesort(void*  array, size_t len, size_t elem_sz, int (*comp)(const void*, const void*)){
    sort(array, len, elem_sz, 0, len-1, comp);
}

