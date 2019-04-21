/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab 5
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cstdlib>

class Student{
public:
	Student(std::string firstName, std::string lastName, std::string fileName){
		firstName_ = firstName;
		lastName_ = lastName;
		lstCourses_.push_back(fileName);
	}

	std::string getName() const{
		return (firstName_ + ' ' + lastName_);
	}

	std::list<std::string> getCourses(){
		return lstCourses_;
	}

	void addCourses(std::list<std::string> coursesToAdd){
		lstCourses_.merge(coursesToAdd);
		lstCourses_.unique();
	}

	friend bool operator== (Student left, Student right){
		return left.lastName_ == right.lastName_ && left.firstName_ == right.firstName_;
	}
	
	friend bool operator< (Student left, Student right){
		return left.lastName_ < right.lastName_ ||
		(left.lastName_ == right.lastName_ && left.firstName_ < right.firstName_);
	}
	
private:
	std::string firstName_;
	std::string lastName_;
	std::list<std::string> lstCourses_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readRoster(std::list<Student>& roster, std::string fileName);
void print(std::map<Student, std::list<std::string>> mapStudents);
void combineNames(std::list<Student>& roster);

int main(int argc, char* argv[]){

	if (argc <= 1){
		std::cout << "usage: " << argv[0] << " list of courses, dropouts last" << std::endl;
		exit(1);
	}
	
	// vector of courses of students
	std::vector <std::list<Student>> courseStudents; 
	
	for(int i=1; i < argc-1; ++i){
		std::list<Student> roster;
		readRoster(roster, argv[i]);  
		courseStudents.push_back(move(roster)); 
	}
	
	std::list<Student> dropouts; 
	readRoster(dropouts, argv[argc-1]); 
	
	std::list<Student> allStudents;  // master list of students
	
	for(auto& lst : courseStudents) 
		allStudents.splice(allStudents.end(),lst);
	
	allStudents.sort(); // sorting master list
		
	for (const auto& str : dropouts)  // removing individual dropouts
		allStudents.remove(str);

	combineNames(allStudents);
	
	allStudents.unique(); // eliminating duplicates
	
	std::map<Student, std::list<std::string>> mapStudents;
	for(auto& i : allStudents){
		//mymap.insert ( std::pair<char,int>('a',100) );
		mapStudents.insert(std::pair<Student, std::list<std::string>>(i, i.getCourses())); //i, i.getCourses());
	}
	
	std::cout<<"All Students"<<std::endl<<"first name, last name, courses enrolled"<<std::endl;
	print(mapStudents);
}

void combineNames(std::list<Student>& roster){
	for(auto& i : roster){
		for(auto& j : roster){
			if(i.getName() == j.getName()){
				i.addCourses(j.getCourses());	//Have to change for std::list
			}
		}
	}
}

void readRoster(std::list<Student>& roster, std::string fileName){
	std::ifstream course(fileName);

	std::string first, last;
	while(course >> first >> last){		
		roster.push_back(Student(first, last, fileName));
	}
	course.close();
}

void print(std::map<Student, std::list<std::string>> mapStudents){
	for(auto& i : mapStudents){
		std::string courses;
		for(auto& j : i.second){
			courses.append(' ' + j);
		}
		std::cout<<i.first.getName()<<courses<<std::endl;
	}
}