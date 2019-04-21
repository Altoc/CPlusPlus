/*
*	Ian Whitesel
*	CSIII Lab 2
*	01/28/2019
*/

#include<iostream>
#include"lab2.hpp"
#include<fstream>
#include<cctype>
#include<string>

const int ARR_SIZE = 50;

int main(int argc, char * argv[]){
	if(argc != 2){
		std::cerr<<"Invalid amount of files on command line. Please enter two valid file types"<<std::endl;
	} else {
		std::ifstream file;
		file.open(argv[1]);
		if(file.is_open()){
			WordList list;			
			char ch;
			std::string str;

			while(!file.eof()){
				file.get(ch);
				if(std::isalnum(ch)){
					str += ch;
				} else if( (isspace(ch)) || (ispunct(ch)) ){
					list.addWord(str);
					//std::cerr<<"|"<<str<<"|"<<std::endl;
					str.clear();
				}
			}
			file.close();
			std::cout<<"Word Count: "<<std::endl;
			list.print();
		} else {
			std::cerr<<"Could not open file"<<std::endl;
		}
	}
}