/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab2 test file
*/

#include <iostream>
#include "lab2.hpp"
#include <cassert>

int main(){
{
	std::cout<<"WordOccurrence Default Ctor, GetWord, GetNum"<<std::endl;
	WordOccurrence word;
	//std::cerr<<"word: "<<word.getWord()<<std::endl;
	assert(word.getWord() == "");
	//std::cerr<<"num of occurrences: "<<word.getNum()<<std::endl;
	assert(word.getNum() == 0);
}
{
	std::cout<<"Word Occurrence word ctor, Match Word"<<std::endl;
	//std::cerr<<"Before 1st decl"<<std::endl;
	WordOccurrence word_1;
	//std::cerr<<"Before 1st ini"<<std::endl;
	WordOccurrence word_2("dog");
	assert(!word_1.matchWord("dog"));
	assert(word_2.matchWord("dog"));
}
{
	std::cerr<<"Word Occurrence increment"<<std::endl;
	std::string str = "dog";
	WordOccurrence word(str);
	assert(word.getNum() == 1);
	word.increment();
	assert(word.getNum() == 2);
	word.increment();
	assert(word.getNum() == 3);
}
{
	std::cerr<<"Word List Default Ctor, GetSize"<<std::endl;
	WordList list;
	//std::cerr<<"list size: "<<list.getSize()<<std::endl;
	assert(list.getSize() == 0);
}
/*
{
	std::cerr<<"Word List Copy Ctor"<<std::endl;
	WordList list;
	assert(list.getSize() == 0);
}
*/
{
	std::cerr<<"Word List addWord, print"<<std::endl;
	WordList list;
	list.addWord("Dogs");
	list.print();
	assert(list.getSize() == 1);
	list.addWord("Cats");
	list.print();
	assert(list.getSize() == 2);
	list.addWord("Frogs");
	list.print();
	assert(list.getSize() == 3);
	list.addWord("Frogs");
	list.print();
	assert(list.getSize() == 3);
	list.addWord("Frogs");
	list.print();
	assert(list.getSize() == 3);
	list.addWord("Logs");
	list.print();
	assert(list.getSize() == 4);
}
std::cout<<"All Tests Passed"<<std::endl;
}