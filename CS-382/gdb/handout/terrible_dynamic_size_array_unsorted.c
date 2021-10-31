#include "terrible_dynamic_size_array_unsorted.h"


void init(struct int_array* arr) {
	arr->count 		= 	0;
	arr->capacity 	= 	DEFAULT_CAPACITY;
	arr->data 		= 	(int*)malloc(sizeof(int) * arr->capacity);
}

void clear(struct int_array* arr) {
	destr(arr);
	init(arr);
}

void destr(struct int_array* arr) {
	free(arr->data);
	arr->count = 0;
}

void print_array(struct int_array* arr) {
	for (unsigned int i = 0; i < arr->count; ++i)
		printf("%d ", arr->data[i]);
	printf("\n");
}

// Bug: Does not identify 6 or 30 in the array 
int contains(struct int_array* arr, int target) {

	unsigned int i;
    
    // Line below contained an extra semicolon
	for (i = 0; i < arr->capacity; ++i)
	{
		if (arr->data[i] == target)
			return TRUE;
	}
	// Returns false even if the value is in the array 
	return FALSE;
}

void resize(struct int_array* arr) {

	arr->capacity *= 2;
	int* new_data = (int*)malloc(sizeof(int) * arr->capacity);
	
	for (unsigned int i = 0; i < arr->count; ++i)
	{
		new_data[i] = arr->data[i];
	}

    // Must deallocate arr->data to free data and then assign it	
	free(arr->data);
    arr->data = new_data;
}

// Bug: adds an extra zero at the beginning of the array
// int payload has an incorrect value
void add(struct int_array* arr,  int payload) {

	if ((arr->count == arr->capacity))

		resize(arr);
    // arr->count changed to arr->count++
	arr->data[arr->count++] = payload;
}

int remove_elem(struct int_array* arr,  int target) {

	unsigned int i = 0;

    // '==' is required for comparison
	if (arr->count == 0)

		return FALSE;

	while (i < arr->count && arr->data[i] != target)  i++;

    // Line below contained an extra semicolon
	if (i == arr->count)

		return FALSE;

	arr->data[i] = arr->data[arr->count];

	arr->count--;
	
	return TRUE;
}
