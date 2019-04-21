// drink class to be used in Coffee Shack lab
// Ian Whitesel

#include <iostream>
#include <string>

enum class DrinkType {small, medium, large};

class Drink{
public:
   Drink(DrinkType type=DrinkType::small, int price=100):
                 type_(type), price_(price){}
   virtual int getPrice() const;
   virtual std::string getName() const;
private: 
   int price_;
   DrinkType type_;
};

int Drink::getPrice() const{
	return price_;
}

std::string Drink::getName() const{
	return "";
}

class Large : public Drink{
public:
   Large(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 200;
   }
   std::string getName() const override{
	return "large" + drink_->getName();
   }
private:
   const Drink *drink_;
};

class Medium : public Drink{
public:
   Medium(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 100;
   }
   std::string getName() const override{
	return "medium" + drink_->getName();
   }
private:
   const Drink *drink_;
};

class Small : public Drink{
public:
   Small(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 0;
   }
   std::string getName() const override{
	return "small" + drink_->getName();
   }
private:
   const Drink *drink_;
};

class Sprinkles : public Drink{
public:
   Sprinkles(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 50;
   }
   std::string getName() const override{
	return drink_->getName() + " sprinkles";
   }
private:
   const Drink *drink_;
};

class Caramel : public Drink{
public:
   Caramel(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 20;
   }
   std::string getName() const override{
	return drink_->getName() + " caramel";
   }
private:
   const Drink *drink_;
};

class Foam : public Drink{
public:
   Foam(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 40;
   }
   std::string getName() const override{
	return drink_->getName() + " foam";
   }
private:
   const Drink *drink_;
};

class Ice : public Drink{
public:
   Ice(const Drink* drink):
		drink_(drink){}
   int getPrice() const override{
	return drink_->getPrice() + 10;
   }
   std::string getName() const override{
	return drink_->getName() + " ice";
   }
private:
   const Drink *drink_;
};

int main(){
	std::string result;
	int resultNum;
	Drink baseDrink;
	char sizeChoice = '\0';
	std::cout<<"Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee?"<<std::endl;
	std::cin>>sizeChoice;
	switch(sizeChoice){
		case 'l': resultNum += Large(&baseDrink).getPrice(); result += Large(&baseDrink).getName() + " coffee with ";		break;
		case 'm': resultNum += Medium(&baseDrink).getPrice(); result += Medium(&baseDrink).getName() + " coffee with ";		break;
		case 's': resultNum += Small(&baseDrink).getPrice(); result += Small(&baseDrink).getName() + " coffee with ";		break;
	}
	char toppingChoice = '\0';
	while(toppingChoice != 'n'){
		std::cout<<"Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce, or [n]ot?"<<std::endl;
		std::cin>>toppingChoice;
		switch(toppingChoice){
			case 's': resultNum += Sprinkles(&baseDrink).getPrice(); result += Sprinkles(&baseDrink).getName();	break;
			case 'c': resultNum += Caramel(&baseDrink).getPrice(); result += Caramel(&baseDrink).getName();		break;
			case 'f': resultNum += Foam(&baseDrink).getPrice(); result += Foam(&baseDrink).getName();		break;
			case 'i': resultNum += Ice(&baseDrink).getPrice(); result += Ice(&baseDrink).getName();			break;
		}
	}
	std::string patronName;
	std::cout<<"Can I get your name?"<<std::endl;
	std::cin>>patronName;
	result = patronName + ", your " + result + " is ready. It will be " + std::to_string(resultNum);
	std::cout<<result<<std::endl;
}