/*
*	Ian Whitesel
*	Star Patterns Main
*	02/16/2018
*/

#include <iostream>
#include "star.hpp"

using std::cout; using std::cin; using std::endl;

int main() {
	char selection;
	do {
		int dimension;

		cout << "Please select shape: " << endl << "Square - s" << endl << "Diagonal Line - d" << endl << "Triangle - t" << endl;

		cin >> selection;

		if (selection == 's') {
			char square_selection;
			cout << "Filled or Hollow square? f/h " << endl;
			cin >> square_selection;
			if (square_selection == 'f') {
				cout << "Please input desired number dimension: " << endl;
				cin >> dimension;
				filledSquare(dimension);
			}
			 else if (square_selection == 'h') {
				cout << "Please input desired number dimension: " << endl;
				cin >> dimension;
				hollowSquare(dimension);
			}
		}
		else if (selection == 'd') {
			cout << "Please input desired number dimension: " << endl;
			cin >> dimension;
			diagonalLine(dimension);
		}
		else if (selection == 't') {
			char triangle_selection;
			cout << "Top or bottom triangle? t/b " << endl;
			cin >> triangle_selection;
			if (triangle_selection == 't') {
				cout << "Please input desired number dimension: " << endl;
				cin >> dimension;
				topTriangle(dimension);
			}
			else if (triangle_selection == 'b') {
				cout << "Please input desired number dimension: " << endl;
				cin >> dimension;
				bottomTriangle(dimension);
			}
		}
	} while (selection == 's' || selection == 'd' || selection == 't');
	cout << "See ya later!" << endl; 
}