/*
 * mypoint.cpp
 *
 *  Created on: Feb 1, 2019
 *  Author: Brian
 */
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class MyPoint {
public:
	// Constructor that uses an initializer list.
	MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { }

	// Methods that do not modify member variables should be declared const.
	void print_coords() const {
		cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
			 << setprecision(2) << z_ << ")" << endl;
	}

	// Mutator (setter).
	void set_x(int x) {
		x_ = x;
	}

	// Accessor (getter), declared const.
	int get_x() const {
		return x_;
	}

private:
	// Member variables (fields). Use the trailing _ for these variables.
	int x_, y_;
	float z_;
}; // semicolon is required!

// Pass by reference, and using an iterator (which is an object
// that can be used essentially as if it were a pointer):
void display_points(const vector<MyPoint> &points) {
	for(auto it = points.cbegin(); it != points.cend(); it++) {
		it->print_coords(); // Same as: (*it).print_coords();
	}
}

void display_points_v2(const vector<MyPoint> &points) {
	for(size_t i = 0; i < points.size(); i++) {
		points[i].print_coords();
	}
}

int main() {
	int x, y;

	// Objects allocated on the stack:
	MyPoint point1(5, 7, 1.9823412);
	MyPoint point2(1, 2, 3);
	MyPoint point3(4, 5, 6);
	// Method call 
	point2.print_coords();

	// Vector is an array with a dynamic size (can be changed)
	vector<MyPoint> points;

	// Push back adds MyPoint points to the vector
	points.push_back(point1);
	points.push_back(point2);
	points.push_back(point3);

	vector<MyPoint> points_above_two;
	// For-each loop (using a reference so there is no copy):
	for(const auto &point : points) { // over the points vector using the point variable 
	// auto is the datatype for the point variable based on the type of the vector
		if(point.get_x() > 2) {
			points_above_two.push_back(point);
		}
	}

	// This is a function call 
	display_points(points_above_two);

	// Practice using standard in (STDIN)
	cout << "Input x: ";
	cin >> x;

	cout << "Input y: ";
	cin >> y;

	// Object allocated on the heap:
	MyPoint *point4 = new MyPoint(x, y, 7);
	// Calling the method using the pointer to the object.
	point4->print_coords(); // Same as: (*point4).print_coords();
	delete point4;

	return 0;
}
