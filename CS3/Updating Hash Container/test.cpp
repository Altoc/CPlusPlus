/*
*	Ian Whitesel
*	CSIII Lab7
*	Spring 2019
*/

#include "hashmap.h"
#include <iostream>
#include <string>
#include <cassert>

int main(){
	{std::cout<<"Insert Test 1..."<<std::endl;
		hashmap<int, int> myHash;
		myHash.insert(pair<int,int>(4, 40));
		assert(myHash.find(4) != nullptr);
	}std::cout<<"Insert Test 1 Passed"<<std::endl;
	{std::cout<<"Insert Test 2..."<<std::endl;
		hashmap<int, char> myHash;
		myHash.insert(pair<int, char>(4, 'a'));
		assert(myHash.find(4) != nullptr);
	}std::cout<<"Insert Test 2 Passed"<<std::endl;
	{std::cout<<"Insert Test 3..."<<std::endl;
		hashmap<int, std::string> myHash;
		myHash.insert(pair<int,std::string>(4, "dog"));
		assert(myHash.find(4) != nullptr);
	}std::cout<<"Insert Test 3 Passed"<<std::endl;
	{std::cout<<"operator[] Test 1..."<<std::endl;
		hashmap<int, int> myHash;
		myHash[9] = 10;
		assert(myHash.find(9) != nullptr);
		assert(myHash.find(9)->second == 10);
	}std::cout<<"operator[] Test 1 Passed"<<std::endl;
	{std::cout<<"operator[] Test 2..."<<std::endl;
		hashmap<int, int> myHash;
		myHash[9] = 10;
		myHash[9] = 11;
		assert(myHash.find(9) != nullptr);
		assert(myHash.find(9)->second == 11);
	}std::cout<<"operator[] Test 2 Passed"<<std::endl;
	{std::cout<<"Erase Test 1..."<<std::endl;
		hashmap<int, int> myHash;
		myHash.insert(pair<int, int>(1, 100));
		assert(myHash.find(1) != nullptr);
		myHash.insert(pair<int, int>(2, 101));
		myHash.insert(pair<int, int>(3, 102));
		myHash.insert(pair<int, int>(4, 103));
		myHash.erase(1);
		assert(myHash.find(1) == nullptr);
	}std::cout<<"Erase Test 1 Passed"<<std::endl;
	{std::cout<<"Rehash Test 1..."<<std::endl;
		hashmap<int, int> myHash;
		myHash.insert(pair<int, int>(2, 110));
		myHash.insert(pair<int, int>(3, 102));
		myHash.insert(pair<int, int>(4, 103));
		myHash.rehash(200);
	}std::cout<<"Rehash Test 1 Passed"<<std::endl;
}