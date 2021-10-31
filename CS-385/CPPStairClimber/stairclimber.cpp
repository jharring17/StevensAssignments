/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jack Harrington
 * Date        : October 2, 2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int numStairs; 

/**
 * * get_ways
 * Finds different combinations of ways to climb num_stairs 
 * stairs, moving up either 1, 2, or 3 stairs at a time.
 * 
 * @param num_stairs Number of stairs
 * @return vector< vector<int> > ways
 */
vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> ways;
    // Base case-> create a bigger empty vector your smaller vectors will go into
    if (num_stairs <= 0) {
        ways.push_back(vector<int>());
    } else {
        // Counter for each of your steps, you can only go 3 at a time
        for (int i = 1; i < 4; i++) {
            // Runs until you hit the last step or where (i = 1)
            if (num_stairs >= i) {
                // Temporary vector to hold your steps taking in the parent
                vector<vector<int>> result = get_ways(num_stairs - i);
                // Loop through each of your sub vectors in your results vector
                for (auto &child : result) {
                    child.insert(child.begin(), i);
                }
                // Adding all of your vectors individually to your ways array, which is the grandparent
                ways.insert(ways.end(), result.begin(), result.end());
            }
        }
    }
    return ways;
}

/**
 * * num_digits
 * Finds number of digits in an integer
 * 
 * @param num
 * @return counter
 */
int num_digits(int num) {
    // Check the number of digits in the user input
    int counter = 0;
    while (num != 0) {
        num = num / 10;
        counter++;
    }
    return counter;
}

/**
 * * display_ways
 * Displays the number of ways to climb stairs by iterating  
 * over the vectors and printing each combination.
 * 
 * @param vector< vector<int> > &ways 
 *
 */
void display_ways(const vector< vector<int> > &ways) {
    int mySize = ways.size();
    int max_width = num_digits(mySize);
    int i = 1;
    
    // Checks if the size is less than 1 and greater than 1 and displays appropriately
    if(mySize > 1) {
        cout << mySize << " ways to climb " << numStairs << " stairs." << endl;
    } else {
        cout << mySize << " way to climb " << numStairs << " stair." << endl;
    }

    // Loops through ways to get each of the arrays and will then print them based off of the specifics in the PDF
    for (auto &child : ways) {
        cout << right << setw(max_width) << i;
        i++;
        cout << ". [";

        // Loops through each of the numbers until you hit the second to last one because you cannot have a comma at the end
        for (unsigned int i = 0 ; i < child.size() - 1; i++) {
            cout << child[i] << ", ";
        }
        cout << child[child.size() - 1];
        cout << "]" << endl;
    }
}


int main(int argc, char * const argv[]) {
    // Checks the number of inputs
    istringstream iss;
    if (argc > 2 || argc < 2) {
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    // Checks to see if argv[1] is of type 'int' 
    iss.str(argv[1]);
    if (!(iss >> numStairs)) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
    // Checks to see if the number of stairs is a postive type 'int'
    } else if (numStairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    // Checks if the number of stairs is 1
    } else if (numStairs == 1) {
        cout << "1 way to climb 1 stair." << endl;
        cout << "1. [1]" << endl;
        return 0;
    }

    display_ways(get_ways(numStairs));
    return 0;
}