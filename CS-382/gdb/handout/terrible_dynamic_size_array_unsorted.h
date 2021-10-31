#include <stdio.h>
#include <stdlib.h>

#define TRUE 	1
#define FALSE 	0
#define DEFAULT_CAPACITY 20

struct int_array {
	int* data;
	unsigned int count;
	unsigned int capacity;
};

int  contains(struct int_array* arr, int target);
int  remove_elem(struct int_array* arr,  int target);
void init(struct int_array* arr);
void destr(struct int_array* arr);
void resize(struct int_array* arr);
void clear(struct int_array* arr);
void add(struct int_array* arr,  int payload);
void print_array(struct int_array* arr);
