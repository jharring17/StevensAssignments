/*
* Author: Jack Harrington
* Date: September 8, 2021 
* File: pointers.cpp
* Version: 1.0
* Description: basic work with pointers
*/

#include <iostream>

using namespace std; 

void display_array(int array[], int length) { // array of integers 
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// same as the function above
void display_array_ptr(int *array, int length) {
    for (int *p = array; p < array + length; p++) { // p++ looks to the next item 4 bytes away
        cout << *p << " ";
    }
    cout << endl;
}



int main() {
    int x = 0;
    int *values = new int[x];
    for (int i = 0; i < x; i++) {
         return *(values + 1);
        // values[i] = i; same as line above
    }
    delete [] values;

    display_array(values, x);
    display_array_ptr(values, x);

    return 0;
}