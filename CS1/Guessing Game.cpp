// Guessing Game
// Ian Whitesel
// 02/09/2018

#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout; using std::cin; using std::endl;

int main(){
	srand(time(nullptr));
	
	int answer;
	int guess;
    
	cout << "I have selected a number between 1-1000, what is it?" << endl;
	
    answer = rand() % 1000 + 1;
	cin >> guess;
	
	while(guess != answer){
	for(guess = guess; guess < answer;)
	{
	    cout << "Wrong, it is larger, what is it?" << endl; cin >> guess;
	    }
	    
    for(guess = guess; guess > answer;)
	{
	    cout << "Wrong, it is smaller, what is it?" << endl; cin >> guess;
	    }
    }
    cout << "Correct!!" << endl;
}