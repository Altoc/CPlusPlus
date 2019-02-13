/*
	*Ian Whitesel
	*String Function Declarations
	*CS23001
	*Project 2
*/

//////////////////////////////////////////////////////////////////////////////
//File:        string-interface.hpp  
//       
//Version:     1.0
//Date:        Fall 2017
//Author:      Dr. J. Maletic
//
//Description: Interface definition of String class for use with test oracle.
//             For use with Project 2, milestone 2, 3, 4.
//
// To use the supplied test oracles you will need to use this interface and namings.
// You must also have all of these methods and functions defined for your string class.
//
// You can NOT add any attributes/members.  If you do the test oracles will not work.
//
// You need to implement all of the methods and funcitons declared here.
//

#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <vector>

const int STRING_SIZE = 256;	//default max size

////////////////////////////////////////////////////
// CLASS INV: str[length()] == 0             &&
//            length()      == capacity()    &&
//            capacity()    == stringSize - 1
//
//
class String {
public:
            String        ();                               //Empty string
            String        (char ch);                        //String('x')
            String        (const char chArray[]);           //String("abc")
            String        (const String &s);                //Copy Constructor
            String        (int);                            //String(10) - size of 10.
            ~String       ();                               //Destructor
    void    swap          (String &rhs);                    //Constant time swap
    String& operator=     (String rhs);                     //Assignment Copy
    char&   operator[]    (int);                            //Accessor/Modifier
    char    operator[]    (int)                     const;  //Accessor
    int     capacity      ()                        const;  //Max chars that can be stored (not including null)
    int     length        ()                        const;  //Actual number of chars in string
    String  operator+     (const String&)           const;  //String + String Overload
    String& operator+=    (const String&);		    //String += Overload
    bool    operator==    (const String&)           const;  //String == String Overload
    bool    operator<     (const String&)           const;  //String < String Overload
    String  substr        (int start, int end)      const;  //The sub-string from staring position to ending position
    int     findch        (int start, char ch)      const;  //Find location of charater starting at a position
    int     findstr       (int start, const String& string) const;  //Find location of str starting at a position
    std::vector<String> split(char splitter) 	    const;  //returns a vector of substrings split by splitter
    void    empty();					    //empties a string

    friend  std::ostream& operator<<(std::ostream&, const String&);
    friend  std::istream& operator>>(std::istream&, String&);

private:
            String        (int, const char[]);              //String(10, "abc") - Size 10 with "abc"
    void    resetCapacity (int len);                        //Resets capacity to be N

    char    *str;                                           //Pointer to char[]
    int     stringSize = 0;	                            //Size includes NULL terminator
};

String  operator+       (const char lhs[], const String& rhs);	//ch[] + String
String  operator+       (const String& lhs, const char rhs[]);	//String + ch[]
String  operator+       (char lhs, const String& rhs);		//ch + String
String  operator+       (const String& lhs, char rhs);		//String + ch

bool    operator==      (const char lhs[], const String& rhs);	//ch[] == String
bool    operator==      (const String& lhs, const char rhs[]);	//String == ch[]
bool    operator==      (char lhs, const String& rhs);		//ch == String
bool    operator==      (const String& lhs, char rhs);		//String == ch

bool    operator<       (const char lhs[], const String& rhs);	//ch[] < String
bool    operator<       (const String& lhs, const char rhs[]);	//String < ch[]
bool    operator<       (char lhs, const String& rhs);		//ch < String
bool    operator<       (const String& lhs, char rhs);		//String < ch

bool    operator<=      (const String&, const String&);		//String <= String
bool    operator!=      (const String&, const String&);		//String != String
bool    operator>=      (const String&, const String&);		//String >= String
bool    operator>       (const String&, const String&);		//String > String

#endif //STRING_HPP