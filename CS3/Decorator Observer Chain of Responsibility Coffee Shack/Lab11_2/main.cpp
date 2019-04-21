// Ian Whitesel
// main of lab11_2
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include "drink.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>

std::string prepareDrink(Customer cust){
	char sizeChoice = cust.getDrinkSize();
	int numOfToppings = cust.getNumOfToppings();
	std::vector<char> toppingChoice = cust.getToppings();
	std::string result;
	Drink baseDrink;
	switch(sizeChoice){
		case 'l': result += Large(&baseDrink).getName();	break;
		case 'm': result += Medium(&baseDrink).getName();	break;
		case 's': result += Small(&baseDrink).getName();	break;
	}
	for(int i = 0; i < numOfToppings; i++){
		switch(toppingChoice[i]){
			case 's': result += Sprinkles(&baseDrink).getName();	break;
			case 'c': result += Caramel(&baseDrink).getName();	break;
			case 'f': result += Foam(&baseDrink).getName();		break;
			case 'i': result += Ice(&baseDrink).getName();		break;
		}
	}
	return "coffee with " + result + " is ready.";
}

int main(){
	srand(time(nullptr));
	Barista barista_1;
	Customer customer_1("Joe", &barista_1), customer_2("Green Goblin", &barista_1),
		 customer_3("Mary", &barista_1), customer_4("Daniel", &barista_1);
	barista_1.registerObserver(&customer_1);
	barista_1.registerObserver(&customer_2);
	barista_1.registerObserver(&customer_3);
	barista_1.registerObserver(&customer_4);
	std::string drink_1 = prepareDrink(customer_1), drink_2 = prepareDrink(customer_2),
		 drink_3 = prepareDrink(customer_3), drink_4 = prepareDrink(customer_4);
	
	std::vector<Customer> customers;
	customers.push_back(customer_2);
	customers.push_back(customer_3);
	customers.push_back(customer_4);
	std::random_shuffle (customers.begin(), customers.end());

	std::queue<std::string> orders;
	std::cout<<"Taking an order..."<<std::endl;
	orders.push(prepareDrink(customer_1));	//taking an order
	std::vector<Customer> customers_helped;
	customers_helped.push_back(customer_1);
	int choiceSelector = 0;
	int ordersTaken = 1;
	int ordersCompleted = 0;
	while(ordersCompleted < 4){
		choiceSelector = rand() % 2;
		if(choiceSelector == 0 && ordersTaken < 4){
			std::cout<<"Taking an order..."<<std::endl;
			orders.push(prepareDrink(customers.front()));
			customers_helped.push_back(customers.front());
			customers.erase(customers.begin());
			ordersTaken++;
		} else if(ordersTaken > ordersCompleted) {
			std::cout<<"Preparing a drink..."<<std::endl;
			barista_1.orderUp(prepareDrink(customers_helped.front()));
			for(int i = 0; i < customers_helped.size(); i++){
				if(prepareDrink(customers_helped[i]) == orders.front()){
					barista_1.deregisterObserver(&customers_helped[i]);
				//	customers_helped.erase(customers_helped.begin());
					orders.pop();
					ordersCompleted++;
					std::cout<<"This is my drink, thanks!"<<std::endl;
				}
			}
		}
	}
}