#ifndef CS_LOGENTRY_H_
#define CS_LOGENTRY_H_

////////////////////////////////////////////////////////////
//
// File:        logentry.hpp 
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class definition for a log entry.
//
//
//

////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

#include "string.hpp" 

////////////////////////////////////////////////////////////
class Date { 
public:
	Date(){};			//void ctor
	Date(const String& str);	//ctor w/ String

	friend std::ostream& operator<<(std::ostream&, const Date&);	//outstream overload
private:
    String  day, month;
    int	year = 0;
};

////////////////////////////////////////////////////////////
class Time {
public:
	Time(){};			//void ctor
	Time(const String& str);	//ctor w/ String
	friend std::ostream& operator<<(std::ostream&, const Time&);	//outstream overload
private:
	int hour, minute, second;
};

////////////////////////////////////////////////////////////
class LogEntry {
public:
	LogEntry() {};	//Default ctor
	LogEntry(String);	//ctor w/ String supplied
	
	friend std::ostream& operator<<(std::ostream&, const LogEntry &);	//output operator overload
	friend void          output_all(std::ostream&, const std::vector<LogEntry> &);
	friend void          by_host   (std::ostream&, const std::vector<LogEntry> &);
	friend int           byte_count(const std::vector<LogEntry>&);
private:
    String  host;
    Date    date;
    Time    time;
    String  request;
    String  status;
    int     number_of_bytes;
};


////////////////////////////////////////////////////////////
//
// Free functions
//

std::vector<LogEntry>   parse       (std::istream&);
int			stringToInt (const String& str);
#endif
