/*
	*Ian Whitesel
	*Big Int function declarations
	*CS23001
	*Project 1
*/


#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>

const int BIG_INT_SIZE = 100;

class bigint{
public:
	bigint(); 			//default constructor
	bigint(int num); 		//constructor to initialize an int to a bigint
	bigint(const char fakeNum[]); 	//contructor to initialize a char to a bigint
	
	friend std::ostream& operator<<(std::ostream& outStream, const bigint& rhs); 	//overloaded outstream
	friend std::istream& operator>>(std::istream& inStream, bigint& rhs);		//overloaded instream
	friend bool operator==(const bigint& lhs, const bigint& rhs); 			//overloaded comparing operator for 2 bigints
	friend bool operator==(const bigint& lhs, const int& rhs); 			//overloaded comparing operator for bigint and int
	friend bigint operator+(const bigint& lhs, const bigint& rhs);			//overloaded addition operator for bigint + bigint
	
	int& operator[](int);		//non-constant subscript overload
	int operator[](int) const;	//constant subscript overload
	
	void iniToZero();	//Initializes array to 0
	//void findNumSize();	//finds the numsize of a bigint
private:
	int bigIntArray[BIG_INT_SIZE];
	int numSize = 0;
};

#endif /* BIGINT_H_ */
