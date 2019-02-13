#include <iostream>
#include <fstream>
#include "bigint.hpp"

int main(){
	std::ifstream file {"data1-1.txt"};					//open data1-1.txt
	
	if(!file.is_open()){							//if it fails to open, notify user and end program
		std::cerr<<"Unable to open file"<<std::endl;
		exit(1);
	}else{
		bigint lhs, rhs;						//initialize operands
				
		while(!file.eof()){						//add lhs to the instream, file will read until non-integer
			file>>lhs;						
			if(!file.eof())
				file>>rhs;
		}
	
		file.close();

	std::cout << "lhs: " << lhs << std::endl;
	std::cout << "rhs: " << rhs << std::endl;
	std::cout << lhs << " + " << rhs << " = " << lhs+rhs << std::endl;
	}
}