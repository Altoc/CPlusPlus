/*
*	Ian Whitesel
*	Star Patterns Definitions
*	Spring 2018
*/

#include "star.hpp"
#include <iostream>

using std::cout; using std::cin; using std::endl;

void filledSquare(int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			cout << "*";
		}
		cout << endl;
	}
}

void hollowSquare(int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (row == 0 || row == dimension - 1 || col == 0 || col == dimension - 1)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}

void diagonalLine(int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (row == col)
				cout << "*";
			if (row != col)
				cout << " ";
		}
		cout << endl;
	}
}

void bottomTriangle(int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (row <= col)
				cout << "*";
		}
		cout << endl;
	}
}

void topTriangle(int dimension) {
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			if (row <= col)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}