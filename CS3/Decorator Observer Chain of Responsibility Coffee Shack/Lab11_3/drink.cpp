//Ian Whitesel
//drink.cpp
#include <string>
#include "drink.hpp"

int Drink::getPrice() const{
	return price_;
}

std::string Drink::getName() const{
	return "";
}

Observer::Observer(Subject *s){
   s->registerObserver(this);
}

Customer::Customer(const std::string &name, Barista* s):
      name_(name), s_(s), 
      Observer(static_cast<Subject*>(s)){
	int drinkSizeSelector = rand() % 3;
	switch(drinkSizeSelector){
		case 0: drinkSize = 's'; break;
		case 1: drinkSize = 'm'; break;
		case 2: drinkSize = 'l'; break;
	}
	numOfToppings = rand() % 5;
	for(int i = 0; i < numOfToppings; i++){
		int toppingsSelector = rand() % 4;
		switch(toppingsSelector){
			case 0: toppings.push_back('s'); break;
			case 1: toppings.push_back('i'); break;
			case 2: toppings.push_back('c'); break;
			case 3: toppings.push_back('f'); break;
		}
	}
	numOfToppings = toppings.size();
}

void Customer::notify() const {
   std::cout << "Customer " << name_ << " checks if "
	<< "Barista made their drink..." << std::endl;
}