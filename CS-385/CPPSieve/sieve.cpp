/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jack Harrington
 * Date        : September 14, 2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that i have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // Print statements for number of primes
    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    
    // Binds max_prime_ to be used in the max_prime_width function
    int max_prime_ = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i] == true) {
            max_prime_ = i;
        }
    }
    
    // Function determines appropriate spacing for values in the array 
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    // If all the primes fit on the same line
    if (num_primes_ <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i] == true) {
                if(i == max_prime_) {
                    cout << i << endl;
                } else {
                    cout << i << " ";
                }
            }
        }
    // If all primes do not fit on the same row
    } else {
        int counter = 1;
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i] == true) {
                // checks if counter is larger than the number of allowable primes per row 
                if (counter >= primes_per_row) {
                    cout << setw(max_prime_width) << i << endl;
                    counter = 1;
                } else {
                    if ( i == max_prime_) {
                        cout << setw(max_prime_width) << i;
                        counter++;
                    } else {
                        cout << setw(max_prime_width) << i << " ";
                        counter++;
                    }
                }
            }
        }
    }
}


int PrimesSieve::count_num_primes() const {
    // Counts the number of primes in the array corresponding with the boolean value true
    int counter = 0;
    for (int i = 2; i < limit_  + 1; i++) {
        if (is_prime_[i] == true) {
            counter++;
        }
    }
    return counter;
}

void PrimesSieve::sieve() {
    // Initializes vaiables and first two items in the array
    int i, j, k;
    is_prime_[0] = false;
    is_prime_[1] = true;

    // sets all of the values in the array to true 
    for (k = 0; k <= limit_; k++) {
        is_prime_[k] = true;
    }

    // Preforms the Sieve Algorithm
    for (i = 2; i <= floor(sqrt(limit_)); i++) {
        if (is_prime_[i] == true) {
            for (j = (i * i); j <= limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // Check the number of digits in the user input
    int counter = 0;
    while (num != 0) {
        num = num / 10;
        counter++;
    }
    return counter;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    sieve.display_primes();
    return 0;
}
