/*
*	Ian Whitesel
*	Project 3 pt. 2
*	Summer 2018
*/

#include <iostream>
#include <fstream>
#include "utilities.hpp"

int main(int argc, char *argv[]){			//initialize main with a argument values on command line
	std::ifstream readFrom(argv[1]);		//initialize an in-stream for second argument on command line, AKA file we are reading from
	std::ofstream writeTo(argv[2]);			//initialize an out-stream for third argument on command line, AKA file we are writing to
	char ch;					//create a character reader for reading from file
	String infix;					//create a string to hold the infix expression

	if(readFrom.is_open()){						//if file is open,
		if(!readFrom.eof())					//check if the file is at the end of the file already,
			readFrom.get(ch);				//if it is not, get the first character from file
		while(!readFrom.eof()){					//while the file has not ended,
			if(ch == '\n'){					
				//infix += ';';				//set the next to last index of infix to a semicolon, for reading purposes in convert func,
				infix += 0;				//and then add a size and add NULL to the end of string for general string reading purposes
				
				if(argc == 3){
					writeTo<<"Infix expression: "<<infix<<std::endl;			//write the infix
					writeTo<<"Postfix expression: "<<convertExprPost(infix)<<std::endl;	//convert the read string to the 3rd argument file on command line, I used myFile.txt for testing purposes
					writeTo<<"Prefix expression: "<<convertExprPre(infix)<<std::endl;	//convert the read string to prefix
					writeTo<<std::endl;
				}else if(argc == 2){
					std::cout<<"Infix expression: "<<infix<<std::endl;			//cout the infix
					std::cout<<"Postfix expression: "<<convertExprPost(infix)<<std::endl;	//cout the conversion
					std::cout<<"Prefix expression: "<<convertExprPre(infix)<<std::endl;	//convert the read string to prefix
					std::cout<<std::endl;
				}
									
				infix.empty();				//empties out the string to be filled again
			}else{						
				infix += ch;				//add the character to the string infix, and increase the size of infix,
			}						
									
			readFrom.get(ch);				//get the next character from the file
		}

	}else{
		std::cout<<"MAIN could not read from file."<<std::endl;
	}

	readFrom.close();				//close that file, fella

}
