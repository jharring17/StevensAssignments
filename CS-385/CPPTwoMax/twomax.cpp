/*
 * twomax.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: Jack Harrington
 */

#include <iostream>
#include <sstream>

using namespace std;

// Creates max function that prints larger of two integers
int max(int m, int n){
	if (m > n){
		cout << m << endl;
	}else {
		cout << n << endl;
	}
	return 0;
}
// creates a main function that accepts command line input
int main(int argc, char*argv[]){
	int m, n;
	istringstream iss;

	// checks to see if number of command line inputs is equal to 3
	if (argc != 3){
		cerr << "Usage: " << argv[0] << "<integer m> <integer n>" << endl;
		return 1;
	}

	// checks to see if first number is an integer
	iss.str(argv[1]);
	if (!(iss >> m)){
		cerr << "Error: first arg is not a valid integer." << endl;
		return 1;
	}

	// clears iss
	iss.clear();

	// checks to see if second number is an integer
	iss.str(argv[2]);
		if (!(iss >> n)){
			cerr << "Error: second arg is not a valid integer." << endl;
			return 1;
		}

	// print statements
	cout << "M is: " << m<< endl;
	cout << "N is: " << n<< endl;
	cout << "max(" << m << "," << n << ") is " << max(m,n) << endl;
	return 0;
}

