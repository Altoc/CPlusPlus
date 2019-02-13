/*	
	*Ian Whitesel
	*Big Int function definitions
	*CS23001
	*Project 1
*/


#include <iostream>
#include "bigint.hpp"

//+++++++++++++++CONSTRUCTOR DEFINITIONS+++++++++++++++++

bigint::bigint(){ 							//////////Default Constructor/////////
	iniToZero();
}

bigint::bigint(int num){ 						/////////Integer Constructor/////////
	iniToZero();		//initialize array to 0
	
	int j = num;		//get the 'size' of the integer
	while(j != 0){
		j = j / 10;
		numSize++;
	}
	
	for(int i = 0; i < BIG_INT_SIZE; i++){	//fills bigint array with integer digits
		bigIntArray[i] = (num % 10);
		num = (num / 10);
	}
}

bigint::bigint(const char fakeNum[]){ 					/////////Character Constructor/////////
	iniToZero();			//initialize array to 0
	
	int j = 0;	
	while(fakeNum[j] != '\0'){	//sets numSize to number of digits in fakeNum
		j++;
		numSize++;
	}
	
	int numHolder;			//fills bigIntArray with digits from fakeNum array backwards, as to be compatible with outstream operator overload
	for(int i = 0; i < numSize; i++){
		numHolder = 0;
		numHolder = fakeNum[i] - '0';
		bigIntArray[numSize - i - 1] = numHolder;
	}
}

//++++++++++++++OVERLOAD FUNCTION DEFINITIONS++++++++++++++

std::ostream& operator<<(std::ostream& outStream, const bigint& rhs){		/////////Outstream Overload///////// 
	bool endOfZero = false;						//a switch to determine when to start printing after leading zeros
	
	for(int i = 0;i < BIG_INT_SIZE; i++){				//iterates over rhs array, printing out values backwards excluding leading zeros
		if(endOfZero == true && i != 0 && i % 50 == 0){		//if line reaches 50 characters, end line
			outStream<<std::endl;
		}
		if(rhs.bigIntArray[BIG_INT_SIZE - i - 1] != 0){		//if a non leading zero is encountered, begin printing array
			endOfZero = true;
		}
		if(endOfZero == true){					//begin printing array at first nonleading zero
			outStream<<rhs.bigIntArray[BIG_INT_SIZE - i - 1];
		}
	}

	if(endOfZero == false)						//if no non-zero is encountered, print 0;
		outStream<<0;
	
	return outStream;
}

std::istream& operator>>(std::istream& inStream, bigint& rhs){		//////////Instream Overload/////////
	char tmpChar;
	char tmpArray[BIG_INT_SIZE];
	
	if(!inStream.eof())
		inStream >> tmpChar;
	
	int i = 0;
	while(tmpChar != ';' && !inStream.eof()){
		tmpArray[i] = tmpChar;
		inStream >> tmpChar;
		i++;
	}
	
	rhs = bigint(tmpArray);	
	return inStream;
}

bool operator==(const bigint& lhs, const bigint& rhs){			/////////Comparing bigint and bigint overload/////////
	for(int i = 0;i < BIG_INT_SIZE;i++){	//iterates through lhs and rhs arrays, checking to see if they are not equal
		if(lhs.bigIntArray[i] != rhs.bigIntArray[i])
			return false;
	}
	return true;				//if all elements are equal, return true
}

bool operator==(const bigint& lhs, const int& rhs){			/////////Comparing bigint and int overload/////////
	bigint newBigInt(rhs);		//convert int rhs to bigint rhs
	
	return(lhs == newBigInt);	//compare the two bigints using previously defined operator==
}

bool operator==(const int& lhs, const bigint& rhs){			/////////Comparing int and bigint overload/////////
	return(rhs == lhs);		//compare int and bigint using the previously defined bigint and int operator
}

bigint operator+(const bigint& lhs, const bigint& rhs){			////////Addition operator overload//////////
	int carry = 0, tmp = 0;
	bigint newArray;
	int i = 0;
	while(i < BIG_INT_SIZE){
		tmp = carry + lhs.bigIntArray[i] + rhs.bigIntArray[i];
		carry = tmp / 10;
		tmp = tmp % 10;
		newArray.bigIntArray[i] = tmp;
		i++;
	}
	return newArray;
}

int &bigint::operator[](int digit){					////////Non-Constant Subscript operator overload////////
	return bigIntArray[digit];
}

int bigint::operator[](int digit) const{				////////Constant Subscript operator overload////////
	return bigIntArray[digit];
}

//++++++++++++++FUNCTION DEFINITIONS++++++++++++++++++++++

void bigint::iniToZero(){						/////////Initialize bigIntArray to zero definition/////////
	for(int i = 0; i < BIG_INT_SIZE; i++){	//iterates through bigIntArray and fills it with 0's
		bigIntArray[i] = 0;
	}
}

/*
void bigint::findNumSize(){
	bool endOfZero = false;
	
	numSize = 0;
	
	for(int i = 0; i < BIG_INT_SIZE; i++){
		if(bigIntArray[BIG_INT_SIZE - i - 1] != 0){		//if a non leading zero is encountered, begin counting numSize
			endOfZero = true;
		if(endOfZero == true)
			numSize++;
		}
	}
}
*/
