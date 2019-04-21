//	Ian Whitesel
//	CSIII Lab3
//	Spring 2019

#include <iostream>
#include "collection.hpp"
#include <cassert>

int main(){
	{	//default ctor
		std::cerr<<"Testing Default CTOR"<<std::endl;

		Collection<int> myCollection;
		//assert(myCollection.firstItem() == NULL);
		//assert(myCollection.lastItem() == NULL);		

		std::cerr<<"Default CTOR passed"<<std::endl;
	}
	{	//add item
		std::cerr<<"Testing add item"<<std::endl;

		Collection<int> myCollection;
		myCollection.addItem(1);
		assert(myCollection.firstItem() == 1);
		assert(myCollection.lastItem() == 1);
		
		myCollection.addItem(2);
		assert(myCollection.firstItem() == 1);
		assert(myCollection.lastItem() == 2);
		
		myCollection.addItem(3);
		assert(myCollection.firstItem() == 1);
		assert(myCollection.lastItem() == 3);

		std::cerr<<"add item passed"<<std::endl;
	}
	{	//print collection
		std::cerr<<"Testing print collection"<<std::endl;

		Collection<int> myCollection;
		myCollection.addItem(1);
		myCollection.addItem(2);
		myCollection.addItem(3);
		myCollection.printCollection();

		std::cerr<<"print collection passed"<<std::endl;
	}
	{
		//remove item
		std::cerr<<"Testing remove item"<<std::endl;

		Collection<int> myCollection;
		myCollection.addItem(1);
		myCollection.addItem(2);
		myCollection.addItem(3);
		
		myCollection.removeItem(2);
		
		myCollection.printCollection();
		assert(myCollection.firstItem() == 1);
		assert(myCollection.lastItem() == 3);
	
		std::cerr<<"remove item passed"<<std::endl;
	}
	{	//equal friend func
		std::cerr<<"Testing equal(coll, coll)"<<std::endl;

		Collection<int> myCollection;
		myCollection.addItem(1);
		myCollection.addItem(2);
		myCollection.addItem(3);

		Collection<int> myCollectione;
		myCollectione.addItem(1);
		myCollectione.addItem(2);
		myCollectione.addItem(3);

		assert(equal(myCollection, myCollectione));
		
		myCollection.addItem(4);
		
		assert(!equal(myCollection, myCollectione));

		std::cerr<<"equal(coll, coll) passed"<<std::endl;
	}
}