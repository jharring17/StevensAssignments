/*******************************************************************************
 * Name    : unique.cpp
 * Author  : Jack Harrington
 * Version : 1.0
 * Date    : Feb 18, 2020
 * Description : Determines if an array is composed of unique characters.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <ctype.h>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // no duplicates are found; false otherwise.
    // have to use the unsigned or the size_t before the i
    for (unsigned int i = 0; i < s.length(); i++) {
        // set a temp val
        int temp = s[i];
        if (islower(temp) == false) {
            // return false if you find a lower case
            return false;
        }
    }
    // return true if string is uppercase
    return true;
}


bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    int temp = 0;
    for( unsigned int i = 0; i < s.length(); i++ ) {
        // initializes myBit to get spaces from 'a'
        int myBit = s[i] - 'a';
        // returns false if there is a one in the space
        if((temp & (1 << myBit)) > 0){
            return false;
        }
        // bitwise or operation and left shift of one
        temp = ((1 << myBit) | temp);
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    // argument check
    if(argc != 2){
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }
    // checks case: the string is all lowercase
    if(is_all_lowercase(argv[1]) == false){
        cout << "Error: String must contain only lowercase letters." << endl;
        //checks case: duplicate letters are in the string
    } else if(all_unique_letters(argv[1]) == false){
            cout << "Duplicate letters found." << endl;
        } else {
        // all letters are unique
            cout << "All letters are unique." << endl;
        }
     return 0;
}
