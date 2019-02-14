// Scientific Calculator
// Ian Whitesel
// 02/09/2018

#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout; using std::cin; using std::endl;

int main(){
    
	int choice;

	do {
	    
	cout << "Select Desired Math Operation: " << endl;
	cout << "Absolute Value - 1" << endl;
	cout << "Floor - 2" << endl;
	cout << "Power - 3" << endl;
	cout << "Square Root - 4" << endl;
	cout << "Cancel - Any Other Number" << endl;
	
	cin >> choice;
	
	switch (choice){
	
	case 1:{
	int abso_choice;
	cout << "You chose absolute value, enter your integer: " << endl;
	cin >> abso_choice;
	cout << "Result is: " << abs (abso_choice) << endl;
	break;
	}

	case 2:{
	double floor_choice;
	cout << "You chose floor, enter your decimal number: " << endl;
	cin >> floor_choice;
	cout << "Result is: " << floor (floor_choice) << endl;
	break;
	}
	
	case 3:{
	double power_x;
	double power_y;
	cout << "You chose power, enter your base: " << endl;
	cin >> power_x;
	cout << "Enter your exponent: " << endl;
	cin >> power_y;
	cout << "Result is: " << pow (power_x, power_y) << endl;
	break;
	}
	
	case 4:{
	double root_choice;
	cout << "You chose square root, enter your integer: " << endl;
	cin >> root_choice;
	cout << "Result is: " << sqrt (root_choice) << endl;
	break; 
	    }
	} 
} while ((choice == 1) || (choice == 2) || (choice == 3) || (choice == 4));

cout << "Thanks for using my calculator!" << endl;

}