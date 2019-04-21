/*
*	Ian Whitesel
*	CSIII Spring 2019 
*	01/15/2019
*	Lab 1
*/

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char * argv[]){
	if(argc != 3){
		std::cerr<<"You must use 2 arguments"<<std::endl;
	} else {
		std::ifstream file1;
		std::ifstream file2;
		file1.open(argv[1]);
		if(file1.is_open()){
			file2.open(argv[2]);
			if(file2.is_open()){
				std::string line1;
				std::string line2;
				int loopCounter = 0;
				while((!file1.eof()) || (!file2.eof())){
					loopCounter++;
					std::getline(file1, line1);
					std::getline(file2, line2);
					int lineSize = 0;
					if(line1 < line2){
						lineSize = line2.size();
					} else {
						lineSize = line1.size();
					}
					for(auto i = 0; i < lineSize; ++i){
						if(line1[i] != line2[i]){
							std::string loopStr = std::to_string(loopCounter);
							std::string line1Output = "file 1: " + loopStr + ": ";
							std::string line2Output = "file 2: " + loopStr + ": ";
							if((line1 == "") || (line2 == "")){
								std::cerr<<"Detected empty string"<<std::endl;
								std::string spacer(line1Output.size(), ' ');
								std::cout<<line1Output<<line1<<std::endl;
								std::cout<<line2Output<<line2<<std::endl;
								std::cout<<spacer<<'^'<<std::endl;
							} else {
								std::string spacer(line1Output.size() + i, ' ');
								std::cout<<line1Output<<line1<<std::endl;
								std::cout<<line2Output<<line2<<std::endl;
								std::cout<<spacer<<'^'<<std::endl;
							}
						}
					}
				}
				file2.close();
			} else {
				std::cout<<"Could not open file2"<<std::endl;
			}
			file1.close();
		} else {
			std::cout<<"Could not open file1"<<std::endl;
		}
	}
}