/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab 2
*/

#include<iostream>
#include "lab2.hpp" 

//////////////////////////////////////WordOccurrence
WordOccurrence::WordOccurrence(const std::string &str){
	word = str;
	num = 1;
}

WordOccurrence::WordOccurrence(char *CStyleString){
	std::string str = CStyleString;
	word = str;
}

bool WordOccurrence::operator==(const WordOccurrence& rhs){
	return(getWord() == rhs.getWord());
}

bool WordOccurrence::matchWord(const std::string &str){
	return(str == word);
}

void WordOccurrence::increment(){
	num++;
}

std::string WordOccurrence::getWord() const{
	return word;
}

int WordOccurrence::getNum() const{
	return num;
}

///////////////////////////////////////WordList
//default ctor
WordList::WordList(){
	size = 0;
	wordArray = new WordOccurrence[size];
}

//copy ctor
WordList::WordList(const WordList &original){
	size = original.getSize();
	wordArray = new WordOccurrence[size];
	for(int i = 0; i < size; i++){
		wordArray[i] = original.wordArray[i];
	}
}

WordList::WordList(const WordList &original, const int userSize){
	size = userSize;
	wordArray = new WordOccurrence[size];
	for(int i = 0; i < original.getSize(); i++){
		wordArray[i] = original.wordArray[i];
	}
}

//destructor
WordList::~WordList(){
	delete [] wordArray;
}

//swap
void WordList::swap(WordList &rhs){
	WordOccurrence *tmp = wordArray;
	wordArray = rhs.wordArray;
	rhs.wordArray = tmp;
	
	int sizeTmp = size;
	size = rhs.size;
	rhs.size = sizeTmp;
}

//overloaded assignment
WordList& WordList::operator=(WordList rhs){
	swap(rhs);
	return *this;
}

int WordList::getSize() const{
	return size;
}

void WordList::addWord(const std::string &str){
	bool foundCopy = false;
	for(int i = 0; i < size; i++){
		if(wordArray[i] == str){
			foundCopy = true;
			wordArray[i].increment();
		}
	}
	if(foundCopy == false){
		WordList tmp(*this, size + 1);
		tmp.wordArray[size] = str;
		*this = tmp;
	}
}

void WordList::sort(){
	for(int i = 0; i < size - 1; i++){
		for(int j = i + 1; j < size; j++){
			if(wordArray[j].getNum() > wordArray[i].getNum()){
				std::cerr<<"swapping  "<<wordArray[j].getWord()<<" with "<<wordArray[j + 1].getWord()<<std::endl;
				WordOccurrence *tmp = &wordArray[i];
				wordArray[i] = wordArray[j];
				wordArray[j] = *tmp;
			}
		}
	}
}

void WordList::print(){
	//this->sort();
	for(int i = 0; i < size; i++){
		std::cout<<wordArray[i].getWord()<<'\t'<<" | "<<wordArray[i].getNum()<<std::endl;
	}
}

///////////////////////////////////////friend funcs
//WordList Friends

bool equal(const WordList& lhs, const WordList& rhs){
	if(lhs.getSize() != rhs.getSize()){
		return false;
	}else{
		for(int i = 0; i < lhs.getSize(); i++){
			if(lhs.wordArray[i].getWord() != rhs.wordArray[i].getWord()){
				return false;
			}
		}
	}
	return true;
}