//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        07/08/2018
// Author:      Ian Whitesel
//
// Description: Class implementation for a log entry.
//
//

////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <fstream>

#include "string.hpp" 
#include "logentry.hpp"

//////////////////////////////////////////////////////////+++LOGENTRY FUNCTION DEFINITIONS+++
//////////////////////////////////////////////////////////LogEntry(String s) ctor
// REQUIRES:  
// ENSURES: 
//
LogEntry::LogEntry(String str) {
	std::vector<String> vec = str.split(' ');	//create a vector of Strings, divided at ' '
	
	if(vec.size() != 10){				//if vector size is not our desired size of 10, set blank logentry:
		host = "Invalid Entry";			//set host
		date = Date("00/000/0000");		//set date
		time = Time("00:00:00");		//set time
		request = "Invalid Entry";		//set request
		status = "Invalid Entry";		//set status
		number_of_bytes = 00;			//set number of bytes
	}else if(vec.size() == 10){			//if vector is the desired size of 10,
		host = vec[0];				//set host to first vector
		date = Date(vec[3].substr(1, 11));	//set date to the first part of the 4th vector, and convert it to int via Date ctor
		time = Time(vec[3].substr(13, 20));	//set time to the second part of the 4th vector, and convert it to int via Time ctor
		request = vec[5] + " " + vec[6] + " " + vec[7];	//set request to the addition of 6th, 7th, and 8th vectors
		status = vec[8];			//set status to ninth vector
		number_of_bytes = stringToInt(vec[9]);	//set number of bytes to tenth vector, and convert it to integer
	}
}

//////////////////////////////////////////////////////////parse Function Definition
// REQUIRES:  
// ENSURES: 
//
std::vector<LogEntry> parse(std::istream& in) {
    	std::vector<LogEntry> result;		//create a vector of LogEntrys
	char *chArray = NULL; 			//create a C array pointer
	char ch = '\0';				//create character to read characters from file
	
	int i = 0;				//set iterator i to 0
	
	if(!in.eof())				//if not at end of file,
		in.get(ch);			//read a character from file
	
	while(!in.eof()){				//while file has not ended,
		//std::cerr<<"iteration: "<<i<<", ch: "<<ch<<std::endl;
		
		if(ch == '\n'){				//when a line is finished,
			String tempString(chArray);	//create a String with the C array as a parameter,
			
			std::cerr<<"tempString: "<<tempString<<std::endl;
			
			LogEntry log(tempString);	//initialize a logentry log to the read tempString,
			result.push_back(log);		//add that log to the vector of logentries,
			i = 0;				//reset i so that C array can continue to fill itself,
			
			std::cerr<<"Deallocating chArray..."<<std::endl;
			
			delete [] chArray;		//deallocate memory from chArray,
			chArray = NULL;			//set chArray to NULL
			in.get(ch);			//get the next character
		}else{
			if(chArray == NULL){		//if chArray has not been initialized to a new array,
				chArray = new char[150];	//assign it a new array with plenty of space for file lines
				//std::cerr<<"CH ARRAY NEW CHAR ASSIGNMENT!"<<std::endl;
			}
			chArray[i] = ch;		//set tempString at index i to last read character,
			in.get(ch);			//get the next character,
			i++;				//then increment iterator i
		}
	}
	delete [] chArray;	//delete C array
	
	return result;		//return the vector of logentrys
}

//////////////////////////////////////////////////////////Output Overload Definition
std::ostream& operator<<(std::ostream& out, const LogEntry& log){
	out<<"Host: "<<log.host<<std::endl;				//output variables of a logentry object
	out<<"Date: "<<log.date<<std::endl;
	out<<"Time: "<<log.time<<std::endl;
	out<<"Request: "<<log.request<<std::endl;
	out<<"Status: "<<log.status<<std::endl;
	out<<"Number of Bytes: "<<log.number_of_bytes<<std::endl;
	out<<"-----------------------------"<<std::endl;
		
	return out;							//return the ostream
}

//////////////////////////////////////////////////////////output_all Function Definition
// REQUIRES:
// ENSURES:
//
void output_all(std::ostream& out, const std::vector<LogEntry> &logs) {
	for(int i = 0; i < logs.size(); i++){	//loop while iterator i is less than the size of logs
		out<<logs[i];			//output each logs each loop
	}
	std::cout<<out;				//cout the out
}

//////////////////////////////////////////////////////////by_host Function Definition
// REQUIRES:  
// ENSURES: 
//
void by_host(std::ostream& out, const std::vector<LogEntry> &logs) {
	for(int i = 0; i < logs.size(); i++){	//loop while iterator i is less than the size of logs
		out<<logs[i].host<<std::endl;	//output log host
	}
	std::cout<<out;				//cout the out
}

//////////////////////////////////////////////////////////byte_count Function Definition
// REQUIRES:  
// ENSURES: 
//
int byte_count(const std::vector<LogEntry> &logs) {
	int result = 0;						//create int result
	
	for(int i = 0; i < logs.size(); i++){			//loop while iterator i is less than the size of logs
		result = result + logs[i].number_of_bytes;	//add bytes to result
	}
	return result;						//output total result
}

//////////////////////////////////////////////////////////+++DATE FUNCTION DEFINITIONS+++
//////////////////////////////////////////////////////////Date(const String&) ctor
Date::Date(const String& str){
	month = str.substr(3, 5);		//set month to substring
	day = str.substr(0, 1);			//set day to substring
	year = stringToInt(str.substr(7, 10));	//set year to substring and convert to int
}

//////////////////////////////////////////////////////////Output operator overload
std::ostream& operator<<(std::ostream& out, const Date& date){
	out<<date.month<<"/"<<date.day<<"/"<<date.year;	//output date in proper format
	return out;					//return the out
}

//////////////////////////////////////////////////////////+++TIME FUNCTION DEFINITIONS+++
//////////////////////////////////////////////////////////Time(const String&) ctor
Time::Time(const String& str){
	hour = stringToInt(str.substr(0, 1));		//set all values to substrings set to convert to integer
	minute = stringToInt(str.substr(3, 4));
	second = stringToInt(str.substr(6, 7));
}

//////////////////////////////////////////////////////////Output operator overload
std::ostream& operator<<(std::ostream& out, const Time& time){
	out<<time.hour<<":"<<time.minute<<":"<<time.second;	//output time in proper format
	return out;						//return the out
}

//////////////////////////////////////////////////////////++FREE FUNCTION DEFINITIONS+++
//////////////////////////////////////////////////////////stringToInt Definition
int stringToInt(const String& str){

	std::cerr<<"number passed to stringToInt: "<<str<<std::endl;

	int num = 0;				//num will hold the total number
	int converter = 0;			//converter will hold the next index to add to num

	int i = 0;				//set iterator i to 0

	if(str[i] == '-')			//if byte count is '-'
		return 0;			//interpret it as 0

	while(str[i] != NULL){		//while the string has not ended,
		converter = str[i] - '0';		//set converter to index i of string and convert to int,

		num = (num + converter) * 10;	//multiply num + converter by 10
		
		i++;				//increment iterator i
	}
	return num / 10;			//return num divided by 10, as it was unnessascarily multiplied by 10 at last iteration
}
