// Ian Whitesel
// main of lab11_3
#include <iostream>
#include <string>
#include "drink.hpp"

int main(){
	Barista *tp = new JuniorBarista(new SeniorBarista(new Manager));
	std::string result;
	char sizeChoice = '\0';
	char toppingChoice = '\0';
	do{
		std::cout<<"Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee?"<<std::endl;
		std::cin >> sizeChoice;
		Drink baseDrink;
		switch(sizeChoice){
			case 'l': result += Large(&baseDrink).getName() + " coffee";	break;
			case 'm': result += Medium(&baseDrink).getName() + " coffee";	break;
			case 's': result += Small(&baseDrink).getName() + " coffee";	break;
		}
		std::cout<<"Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce, or [n]ot?"<<std::endl;
		std::cin>>toppingChoice;
		switch(toppingChoice){
			case 's': result += " with " + Sprinkles(&baseDrink).getName() + ".";	break;
			case 'c': result += " with " + Caramel(&baseDrink).getName() + ".";	break;
			case 'f': result += " with " + Foam(&baseDrink).getName() + ".";		break;
			case 'i': result += " with " + Ice(&baseDrink).getName() + ".";		break;
		}
		tp->handleRequest(toppingChoice, result);
		result = "";
	} while (toppingChoice != 'n');
}