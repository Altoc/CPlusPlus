/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab 4 pt. 1
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

void readRoster(std::list<std::string>& roster, std::string fileName);

void sortRoster(std::list<std::string>& roster, std::string fileName);

void printRoster(const std::list<std::string>& roster);

int main(int argc, char* argv[]){
	
	if(argc <= 1){
		std::cout<<"Include files to be read"<<std::endl;
	}
	
	std::vector<std::list<std::string>> courseStudents;
	
	for(int i=1; i < argc-1; i++){
		std::list<std::string> roster;
		readRoster(roster, argv[i]);
		//std::cout<<"\n"<<argv[i]<<"\n"<<std::endl;
		//printRoster(roster);
		
		courseStudents.push_back(move(roster));
	}
	
	//add drop outs to student list
	std::list<std::string> dropouts;
	readRoster(dropouts, argv[argc-1]);
	
	//complete list of everyone
	std::list<std::string> allStudents;
	
	//transfer course students to all students
	for(auto& lst : courseStudents){
		allStudents.splice(allStudents.end(), lst);
	}
	
	//sort all students alphabetically
	allStudents.sort();
	
	//remove duplicates from all students list
	allStudents.unique();
	
	//remove dropouts from all students list
	for(const auto& str: dropouts){
		allStudents.remove(str);
	}
	
	for(int i=1; i < argc-1; i++){
		sortRoster(allStudents, argv[i]);
	}

	std::cout<<"All Students: "<<std::endl;	
	printRoster(allStudents);
}

void sortRoster(std::list<std::string>& roster, std::string fileName){
	std::ifstream course(fileName);

	std::list<std::string> tmp;

	std::string first, last;	
	while(course >> first >> last){
		tmp.push_back(first + ' ' + last);
	}
	
	for(auto& rosterStr : roster){
		int endOfName = 0;
		int spaceCounter = 0;
		for(int i = 0; i < rosterStr.size(); i++){
			if(rosterStr[i] == ' '){
				spaceCounter++;
			}
			if((rosterStr[i] == ' ') && (spaceCounter == 2)){
				endOfName = i;
			}
		}

		std::string rosterSubStr = rosterStr.substr(0, endOfName);

		for(auto& tmpStr : tmp){
			if(rosterSubStr == tmpStr){
				rosterStr.append(' ' + fileName);
			}
		}
	}
	course.close();
}

void readRoster(std::list<std::string>& roster, std::string fileName){
	std::ifstream course(fileName);

	std::string first, last;
	while(course >> first >> last){
		roster.push_back(move(first + ' ' + last + ' '));
	}
	course.close();
}

void printRoster(const std::list<std::string>& roster){
	for(const auto& str : roster){
		std::cout<<str<<std::endl;
	}
}