/*
*	Ian Whitesel
*	BMR Calculator
*	Spring 2018
*/
#include <iostream>

using std::cout; using std::cin; using std::endl;

double bmr_man(double weight, double height, double age){
    return 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age);
}

double bmr_woman(double weight, double height, double age){
    return 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age);
}

int main(){

cout << "Man or woman? m/w" << endl;
char sex;
cin >> sex;
cout << "Enter weight in pounds, height in feet, then inches, and then age in years: " << endl;
double weight;
double height_feet;
double height_inch;
double age;
cin >> weight; cin >> height_feet; cin >> height_inch; cin >> age;
const int donut = 195;
double height = (height_feet * 12) + height_inch;
if(sex == 'm'){
    
    cout << "Your BMR is " << bmr_man(weight, height, age) << " " << "and you can eat " << bmr_man(weight, height, age) / donut << " " << "donuts per day" << endl;
    
}
else if(sex == 'w'){
    
    cout << "Your BMR is " << bmr_woman(weight, height, age) << " " << "and you can eat " << bmr_woman(weight, height, age) / donut << " " << "donuts per day" << endl;

}
cout << "bye";
}