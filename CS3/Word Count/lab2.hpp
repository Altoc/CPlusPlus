/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab 2
*/
#ifndef LAB2_H
#define LAB2_H

#include<iostream>
#include<string>

class WordOccurrence {
public:
    WordOccurrence(){word = ""; num = 0; printed = false;};	//default ctor
    WordOccurrence(const std::string &str);
    WordOccurrence(char* CStyleString);
    bool operator==(const WordOccurrence&);
    bool matchWord(const std::string &str); 			// returns true if word matches stored
    void increment(); 						// increments number of occurrences
    std::string getWord() const; 
    int getNum() const;
private:
    std::string word;
    int num;
    bool printed;
};

class WordList{
public:
    WordList();							//default ctor
    WordList(const WordList &original);				//copy ctor
    WordList(const WordList &original, const int userSize);
    ~WordList();						//destructor
    void swap(WordList &rhs);					//swap
    WordList& operator=(WordList rhs);				//operator = overload

    friend bool equal(const WordList& lhs, const WordList& rhs);

    int getSize() const;
    void addWord(const std::string &str);
    void sort();
    void print();
private:
    WordOccurrence *wordArray; 					// a dynamically allocated array of WordOccurrences
                                				// may or may not be sorted
    int size;
};

#endif //LAB2_H