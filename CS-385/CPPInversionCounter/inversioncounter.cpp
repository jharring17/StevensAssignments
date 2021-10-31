/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Jack Harrington
 * Version     : 1.0
 * Date        : October 30, 2021
 * Description : Counts the number of inversions in an array.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long counter = 0;
    for( int i = 0; i < length - 1; i++) {
        for(int j = i + 1; j < length; j++) {
            if( array[i] > array[j]) {
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // Hint: Use mergesort!
    long output;
    int *scratch = new int[length];
    int low = 0;
    int high = length-1;
    output =  mergesort(array, scratch, low, high);
    delete [] scratch;
    return output;
}

static long mergesort(int array[], int scratch[], int low, int high){
    if(low < high){
        long counts = 0;
        int mid = low + (high - low) / 2;
        counts = counts + mergesort(array, scratch, low, mid);
        counts = counts + mergesort(array, scratch, mid+1, high);
        int L = low;
        int H = mid + 1;
        for( int k = low; k <= high; k++){
            if( L <= mid && ( H > high || array[L] <= array[H])) {
                scratch[k] = array[L];
                L = L + 1;
            } else {
                scratch[k] = array[H];
                H = H + 1;
                counts = counts + ( mid + 1 - L);
            }
        } for( int k = low; k <= high; k++) {
            array[k] = scratch[k];
        }
        return counts;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if( argc > 2) {
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    if(argc == 2 && string(argv[1]) != "slow") {
         cout << "Error: Unrecognized option " << "'" << argv[1] << "'." << endl;
         return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int length = values.size();
    if (length == 0) {
        cerr << "Error: Sequence of integers not received.\n";
        return 1;
    }

    if( argc==2 && string(argv[1]) == "slow" ){
        cout << "Number of inversions: " << count_inversions_slow(&values[0], length);
    } else {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], length);
    }
    return 0;
}
