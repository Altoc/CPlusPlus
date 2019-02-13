/*
	*Ian Whitesel
	*String function definitions
	*CS23001
	*Project 2
*/


#include <iostream>
#include "string.hpp"
#include <vector>

//////////////////////////////////////////////////////CONSTRUCTOR DEFINITIONS/////
String::String(){								//Default Constructor
	stringSize = 1;			//set stringSize to 1
	str = new char[stringSize];	//create new array of stringSize
	
	str[0] = '\0';			//assign first index to NULL
}

String::String(char ch){							//Char Constructor
	stringSize = 2;			//set stringSize to 2

	str = new char[stringSize];	//create new array of stringSize

	str[0] = ch;			//set first index to char
	str[1] = '\0';			//set next index to NULL
}

String::String(const char chArray[]){						//Char Array Constructor	
	int j = 0;			//iterator j = 0
	
	while(chArray[j] != '\0'){	//while chArray at index j has not reached end of string,
		stringSize++;		//increase stringSize,
		j++;			//and increase iterator j
	}

	stringSize++;			//add one more to stringSize for NULL

	str = new char[stringSize];	//create new array of stringSize
	int i = 0;			//iterator i = 0
	
	while(chArray[i] != '\0'){	//while the character array has not ended,
		str[i] = chArray[i];	//copy values from chArray to str,
		i++;			//and increment iterator i
	}
	
	str[i] = '\0';			//set final index to NULL		
}

String::String(const String &s){						//Copy Constructor
	stringSize = s.stringSize;	//set stringSize to s's stringSize
	
	str = new char[stringSize];	//create new array of stringSize
	
	int i = 0;			//iterator i = 0
	
	while(s.str[i] != '\0'){	//while s.str[i] is not NULL,
		str[i] = s.str[i];	//copy values from s.str to str,
		i++;			//and increment iterator i
	}

	str[i] = '\0';			//set final index to NULL
}

String::~String(){								//Destructor
	delete [] str;			//delete str in the coolest way possible
}

//////////////////////////////////////////////////////MEMBER FUNCTION DEFINITIONS/////
void String::swap(String &rhs){							//Swap function
	char *tmp = str;		//create a temporary char pointer, point it to str
	str = rhs.str;			//point str to rhs.str
	rhs.str = tmp;			//point rhs.str to tmp
	
	int temp = stringSize;		//save stringSize original value
	stringSize = rhs.stringSize;	//set stringSize to rhs.stringSize
	rhs.stringSize = temp;		//set rhs.stringSize to the original value
}

String& String::operator=(String rhs){						//String = String Assignment Overload
	swap(rhs);			//swap str and rhs.str via swap function
	
	return *this;			//return the result
}

char& String::operator[](int index){						//Non-constant Subscript Overload
	return str[index];		//return the value of str[index]
}

char String::operator[](int index) const{					//Constant Subscript Overload
	return str[index];		//return the value of str[index]
}

int String::capacity() const{							
	return stringSize - 1;		//total number of possible assignable indexes is stringSize -1 due to NULL
}

int String::length() const{							
	int len = 0;			//set len to 0
	
	while(str[len] != '\0'){	//while str at index len has not reached end of string,
		len++;			//increment len
	}
	
	return len;			//return len as length, as length is number of used indexes in a string
}

String String::operator+(const String &rhs) const{				//String + String Concatenation
	int newSize = stringSize + rhs.stringSize;	//create a newSize of lhs.stringSize and rhs.stringSize
	String result(newSize);				//initialize a new String with the newSize, String(int) adds one to size for NULL
	result.stringSize = newSize;			//set result's stringSize to the new Size
	
	int i = 0;					//iterator i = 0
	
	while(str[i] != '\0'){				//while str at index i has not reached end of String,
		result.str[i] = str[i];			//copy str at index i to result's str at index i,
		i++;					//and increment iterator i
	}
	
	int j = 0;					//iterator j = 0
	
	while(rhs.str[j] != '\0'){			//while rhs.str at index i has not reached end of String,
		result.str[i] = rhs.str[j];		//copy values of rhs.str at index j to result.str at index i,
		j++;					//increment iterator j,
		i++;					//increment iterator i
	}
	
	result[i] = '\0';				//assign final index to NULL to end string
	
	return result;					//return the result
}

String& String::operator+=(const String& rhs){					//String += operator overload
	stringSize--;			//reduce stringSize by one, to remove one extra index created by both string's NULL
	return(*this = *this + rhs);	//lhs = lhs + rhs by calling concatenation
}

bool String::operator==(const String& rhs) const{				//String == String Comparative
	int i = 0;		//set iterator i = 0

	while((str[i] != '\0')&&(rhs.str[i] != '\0')&&(str[i] == rhs.str[i])) 	//while neither operand has ended, and while their indexes are of equal value,
		i++;								//iterate through until a difference is found

	if(str[i] > rhs.str[i])		//if lhs > rhs
		return false;
	if(str[i] < rhs.str[i])		//if lhs < rhs
		return false;
	if((str[i] == '\0') && (rhs.str[i] == '\0'))		//if both operands are at NULL, they never found a difference and are true
		return true;
	return false;			//return false if somehow none of those checks applied
}

bool String::operator<(const String& rhs) const{				//String < String Less Than overload
	int i = 0;			//set iterator i = 0
	
	while((str[i] != '\0')&&(rhs.str[i] != '\0')&&(str[i] == rhs.str[i])) 	//while neither operand has ended, and while their indexes are of equal value,
		i++;								//iterate through until a difference is found

	if(str[i] >= rhs.str[i])	//if lhs is anything except < rhs
		return false;
	if(str[i] < rhs.str[i])		//if lhs's value is less than rhs's value
		return true;
	if(str[i] == '\0')		//if lhs is shorter than rhs
		return true;

	return false;			//if a difference is never found, or rhs.str < str, then false
}

String String::substr(int start, int end) const{				//Find String within String then extract and return it
	String result((end - start) + 1);	//initialize string result with an int value of the capacity of the substring + 1 for NULL
	int i = start;				//set iterator i to start
	int j = 0;				//set iterator j to 0
	
	if(start <= end){					//if start is less than or equal to end,
		while((j <= (end - start))&&(i <= end)){	//and while iterator j is less than or equal to the length of the substr && i is less than or equal to end,
			result[j] = str[i];			//set result.str at index j to str at index i,
			i++;					//increment the iterators,
			j++;
		}
		result[j] = NULL;
		
		return result;					//and when j > the length of the substr, return result
	}else{
		return '\0';					//if start > end, return NULL
	}
}

int String::findch(int start, char ch) const{					//start searching for ch at index start and return the index ch was at
	int i = start;				//set iterator i = start

	while((str[i] != '\0')){		//while str has not reached end of string,
		if(str[i] == ch){		//check if str at index i is equal to ch,
			return i;		//if it is, return the index i,
		}else{				
			i++;			//else, increment i and keeping looking
		}
	}
	return -1;				//if it is never found, return -1
}

int String::findstr(int start, const String& string) const{			//start searching for string at index start and return the index string was at
	int i = start;						//set iterator i = start
	int end = string.stringSize - 1;			//define an ending iterator equal to callingfunctions capacity
	
	while(i < stringSize){					//while iterator i < stringSize,
		if(substr(i, (end - 1 + i)) == string){		//check if substring of calling function is equal to string,
			return i;				//if so, return index i,
		}else{
			i++;					//otherwise increment i and give it another go
		}
	}
	
	return -1;						//if it is never found, return -1	
}

std::vector<String> String::split(char splitter) const{				//Return a vector of subtrings split by splitter
	std::vector<String> result;
	int i = 0;
	int next = 0;
	
	while(i < stringSize){
		next = findch(i, splitter);
		if(next == -1){
			result.push_back(substr(i, (stringSize - 2)));
			i = stringSize;
		}else{
			next++;
			result.push_back(substr(i, (next - 2)));
			i = next;
		}
	}
	return result;
}
//////////////////////////////////////////////////////FRIEND FUNCTION DEFINITIONS/////
std::istream& operator>>(std::istream& in, String& rhs){			//In-Stream Operator Overload
	in>>rhs.str;
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& rhs){			//Out-Stream Operator Overload
	out<<rhs.str;
	return out;
}

/////////////////////////////////////////////////////PRIVATE MEMBER FUNCTION DEFINITIONS/////
String::String(int size){							//variable size ctor
	stringSize = size + 1;			//set StringSize to variable size

	str = new char[stringSize];		//create new array of stringSize
	
	for(int i = 0; i <= size; i++){		//set all indexes to NULL
		str[i] = '\0';
	}
}

String::String(int size, const char chArray[]){					//variable size and chArray ctor
	stringSize = size + 1;
	str = new char[stringSize];	//create new array of stringSize
	int i = 0;			//iterator i = 0

	while((chArray[i] != '\0')){	//while the character array has not ended,
		str[i] = chArray[i];	//copy values from chArray to str,
		i++;			//and increment iterator i
	}
	
	str[i] = '\0';			//set final index to NULL
}

void String::resetCapacity(int len){						//reset capacity of string while keeping contents inside
	stringSize = len + 1;		//sets stringSize to len + 1, as capacity is stringSize - 1
}

//////////////////////////////////////////////////////FREE FUNCTION DEFINITIONS/////
String operator+(const char lhs[], const String& rhs){				//char[] + String Overload
	String ch(lhs);		//constructor to change lhs to a String
	return(ch + rhs);	//return String + String
}

String operator+(const String& lhs, const char rhs[]){				//String + char[] Overload
	String ch(rhs);		//convert rhs to String
	return(lhs + ch);	//return String + String
}

String operator+(char lhs, const String& rhs){					//char + String Overload
	String ch(lhs);
	return(ch + rhs);
}

String operator+(const String& lhs, char rhs){					//String + char Overload
	String ch(rhs);		//convert rhs to String
	return(lhs + ch);	//return String + String
}
bool operator==(const char lhs[], const String& rhs){				//char[] == String Overload
	String ch(lhs);		//constructor to change lhs to a String
	return(ch == rhs);
}

bool operator==(const String& lhs, const char rhs[]){				//String == char[] Overload
	return(rhs == lhs);
}

bool operator==(char lhs, const String& rhs){					//char == String Overload
	String ch(lhs);		//constructor to change lhs to a String
	return(ch == rhs);
}

bool operator==(const String& lhs, char rhs){					//String == char Overload
	return(rhs == lhs);
}

bool operator<(const char lhs[], const String& rhs){				//char[] < String Overload
	String ch(lhs);		//constructor to change lhs to a String
	return(ch < rhs);
}

bool operator<(const String& lhs, const char rhs[]){				//String < char[] Overload
	return!(rhs < lhs);
}

bool operator<( const char lhs, const String& rhs){				//char < String Overload
	String ch(lhs);		//constructor to change lhs to a String
	return(ch < rhs);	//String < String
}

bool operator<(const String& lhs, const char rhs){				//String < char Overload
	return!(rhs < lhs);
}

bool operator<=(const String& lhs, const String& rhs){				//String <= String Overload
	if(lhs > rhs)
		return false;
	else
		return true;
}

bool operator!=(const String& lhs, const String& rhs){				//String != String Overload
	if(lhs == rhs)
		return false;
	else
		return true;
}

bool operator>=(const String& lhs, const String& rhs){				//String >= String Overload
	if(lhs < rhs)
		return false;
	else
		return true;
}

bool operator>(const String& lhs, const String& rhs){				//String > String Overload
	return(rhs < lhs);
}