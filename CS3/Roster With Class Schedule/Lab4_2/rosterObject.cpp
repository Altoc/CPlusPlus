/*
*	Ian Whitesel
*	CSIII Spring 2019
*	Lab 4 pt. 2
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <cstdlib>

class Student{
public:
	Student(std::string firstName, std::string lastName, std::string fileName){
		firstName_ = firstName;
		lastName_ = lastName;
		VecCourses_.push_back(fileName);
	}

        std::string print() const {
		std::string courses = "";
		for(int i = 0; i < VecCourses_.size(); i++){
			courses += (' ' + VecCourses_[i]);
		}
		std::string result = firstName_ + ' ' + lastName_ + ' ' + courses;
		return result;
	}

	std::string getName() const{
		return (firstName_ + lastName_);
	}

	std::vector<std::string> getCourses(){
		return VecCourses_;
	}

	void addCourses(std::vector<std::string> coursesToAdd){
		for(int i = 0; i < coursesToAdd.size(); i++){
			bool checker = false;
			for(int j = 0; j < VecCourses_.size(); j++){
				if(coursesToAdd[i] == VecCourses_[j]){
					checker = true;
				}
			}
			if(checker == false){
				VecCourses_.push_back(coursesToAdd[i]);
			}
		}
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
	std::vector<std::string> VecCourses_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readRoster(std::list<Student>& roster, std::string fileName);
void printRoster(const std::list<Student>& roster);
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
	
	printRoster(allStudents);
}

void combineNames(std::list<Student>& roster){
	for(auto& i : roster){
		for(auto& j : roster){
			if(i.getName() == j.getName()){
				i.addCourses(j.getCourses());
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

void printRoster(const std::list<Student>& roster){
	for(const auto& student : roster)
		std::cout << student.print() << std::endl;
}