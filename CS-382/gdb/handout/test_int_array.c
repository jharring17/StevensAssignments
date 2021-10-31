#include "terrible_dynamic_size_array_unsorted.h"


int main(void) {

	struct int_array arraytest;
	init(&arraytest);

	if (arraytest.count == 0) printf("Empty array created\n");
	else printf("Error in array creation\n");

	clear(&arraytest);

	if (arraytest.count == 0) printf("Array cleared of data\n");
	else printf("Error in clear function\n");

	for(unsigned int i = 0; i < 25; i += 2) {
		if(arraytest.count < DEFAULT_CAPACITY) {
			add(&arraytest, i);
			print_array(&arraytest);
		}
		else {
			add(&arraytest, i);
			print_array(&arraytest);
		}
	}
	for(unsigned int i = 1; i < 25; i += 2) {
		if(arraytest.count < DEFAULT_CAPACITY) {
			add(&arraytest, i);
			print_array(&arraytest);
		}
		else {
			add(&arraytest, i);
			print_array(&arraytest);
		}
	}
	if (arraytest.capacity == 2 * DEFAULT_CAPACITY)
		printf("Resize function works properly\n");
	else printf("Resize not working properly\n");

	if (contains(&arraytest, 6)) printf("Number 6 present in Array\n");
	else printf("Number 6 not in Array Contains not working properly\n");

	if (contains(&arraytest, 30))
		printf("Number 30 present in Array Contains not working properly\n");
	else printf("Number 30 not in Array\n");

	if (remove_elem(&arraytest, 23) && arraytest.count == 24)
		printf("Number 23 removed from Array\n");
	else printf("Number 23 not in Array error in remove_elem\n");

	if (remove_elem(&arraytest, 24) && arraytest.count == 23)
		printf("Number 24 removed from Array\n");
	else printf("Number 24 not in Array error in remove_elem\n");

	if (remove_elem(&arraytest, 0) && arraytest.count == 22)
		printf("Number 0 removed from Array\n");
	else printf("Number 0 not in Array error in remove_elem\n");

	if (remove_elem(&arraytest, 35)) printf("Error in remove function\n");
	else printf("Number not in Array\n");

	destr(&arraytest);

	if(arraytest.count == 0) printf("Array destroyed\n");
	else printf("Error in destroy\n");

	return 0;
}
