/*
*	Ian Whitesel
*	Assembler pt. 3
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

				infix += 0;				//and then add a size and add NULL to the end of string for general string reading purposes
				
				if(argc == 3){
					
					writeTo<<"-----POSTFIX-----"<<std::endl;
					writeTo<<"Infix Expression: "<<infix<<std::endl;			//write out the String infix
					writeTo<<"Postfix Expression: "<<convertExprPost(infix)<<std::endl;	//convert the read string to the 3rd argument file on command line, I used myFile.txt for testing purposes
					writeTo<<std::endl;
					convertPostToAssembly(convertExprPost(infix), argc, writeTo);		//write out the conversion from postfix to assembly
					writeTo<<std::endl;							//add a line break, as requested by lab instructions
					
/*	PREFIX ASSEMBLER TO FILE HERE
					writeTo<<"-----PREFIX-----"<<std::endl;
					writeTo<<"Infix Expression: "<<infix<<std::endl;			//write out the String infix
					writeTo<<"Prefix Expression: "<<convertExprPre(infix)<<std::endl;	//convert the read string to prefix
					writeTo<<std::endl;
					convertPreToAssembly(convertExprPre(infix), argc, writeTo);		//write out the conversion from prefix to assembly
					writeTo<<std::endl;							//add a line break, as requested by lab instructions
*/

				}else if(argc == 2){

					std::cout<<"-----POSTFIX-----"<<std::endl;
					std::cout<<"Infix Expression: "<<infix<<std::endl;			//cout the String infix
					std::cout<<"Postfix Expression: "<<convertExprPost(infix)<<std::endl;	//if no file was supplied to write to on command line, print out results
					std::cout<<std::endl;
					convertPostToAssembly(convertExprPost(infix), argc, writeTo);		//cout the conversion from postfix to assembly
					std::cout<<std::endl;							//add a line break, as requested by lab instructions

/*	PREFIX ASSEMBLER TO CONSOLE HERE
					std::cout<<"-----PREFIX-----"<<std::endl;
					std::cout<<"Infix Expression: "<<infix<<std::endl;			//cout the String infix
					std::cout<<"Prefix Expression: "<<convertExprPre(infix)<<std::endl;	//write prefix version
					std::cout<<std::endl;
					convertPreToAssembly(convertExprPre(infix), argc, writeTo);		//cout the conversion from prefix to assembly
					std::cout<<std::endl;							//add a line break, as requested by lab instructions
*/
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