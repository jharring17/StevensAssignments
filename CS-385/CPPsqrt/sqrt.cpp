/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Jack Harrington
 * Version : 1.0
 * Date    : September 8, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// declaration of sqrt function
double sqrt(double num, double epsilon);

int main (int argc, char* argv[]) {
    double num, epsilon; 
    
    istringstream iss;
	if (argc > 3 || argc < 2){ // checks to see if number of command line arguments is 2 or 3
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if (!(iss >> num)){ // checks to see if first number is a double
		cerr << "Error: Value argument must be a double." << endl;
		return 1;

	} else if (num < 0){ // checks to see if the first number is less than 0
        cerr << numeric_limits<double>::quiet_NaN() << endl; 
        return 1;

    } else if (num == 0 || num == 1) { // returns input if equal to 0 or 1
        cout << fixed << setprecision (8) << num << endl;
        return 1;
    }

	// clears iss
	iss.clear();

	if (argc == 2) {
		epsilon = 1.0e-7;
	} else {
		iss.str(argv[2]);
		if (!(iss >> epsilon)){ // checks to see if second number is an double
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;

		} else if (epsilon <= 0) { // checks to see if epsilon is greater than 0 
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}
	// print statement
	double solution = sqrt(num, epsilon);
    cout << fixed << setprecision(8) << solution << endl; 
}

double sqrt(double num, double epsilon){ // takes the sqrt of given input
    double next_guess, last_guess;
	last_guess = num;
	next_guess = 0;
	next_guess = (last_guess + num / last_guess) / 2;
	while (abs(last_guess - next_guess) > epsilon) {
		last_guess = next_guess;
		next_guess = (last_guess + num / last_guess) / 2;
	}
    return next_guess;
}