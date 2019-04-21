// drink class & Barista/customer classes
// Ian Whitesel

#include <vector>
#include <set>
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

class Observer{
public:
   Observer(class Subject* s);
   virtual void notify() const = 0;
};

class Subject{
public: 
   void registerObserver(Observer *o)
                       {views_.insert(o);}
   void deregisterObserver(Observer *o)
                       {views_.erase(o);}
   void notifyObservers() const {
      for(auto e: views_) e->notify();}
private:
   std::set <Observer *> views_;
};

class Barista;

class Customer: public Observer {
public:
   Customer(const std::string &, Barista*);
   void notify() const override;
   char getDrinkSize(){return drinkSize;}
   int getNumOfToppings(){return numOfToppings;}
   std::vector<char> getToppings(){return toppings;}
private:
   char drinkSize;
   std::vector<char> toppings;
   int numOfToppings;
   std::string name_;
   Barista *s_;
};

class Barista: public Subject {
public:
   Barista(/*const std::string &name*/)/*: name_(name)*/ {}
   void orderUp(std::string drink)
               {drink_=drink; notifyObservers();}
   const std::string& getDrink() const {return drink_;}
private:
   std::string drink_;
};