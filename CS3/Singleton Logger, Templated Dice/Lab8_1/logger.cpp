//	Ian Whitesel
//	CSIII Lab8
//	Spring 2019

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

class Logger{
public:
	static Logger* instance();		//returns pointer to single instance

	void report(const std::string&);		//append argument string to a file that is openned when logger is first accessed
//std::string getStr(){return singletonStr_;}//temp func for testing and understanding
	void closeFile(){fout.close();}
private:
	Logger();	//defined later for atexit()

	//prevent copying with these 2:
	Logger(const Logger&){}	
	Logger& operator=(const Logger&){}

	static void cleanUp();	//for object destruction

	static Logger* ptrToOnlyInstance_;	//pointer to the single instance
	static std::ofstream fout;
};

Logger* Logger::ptrToOnlyInstance_ = nullptr;	//ini pointer to its instance

std::ofstream Logger::fout;

Logger* Logger::instance(){			//return pointer to the instance
	if(ptrToOnlyInstance_ == nullptr){
		fout.open("log.txt");
		ptrToOnlyInstance_ = new Logger;
	}
	return ptrToOnlyInstance_;
}

Logger::Logger(){
	atexit(cleanUp);
}

void Logger::cleanUp(){
	//std::cerr<<"clean up called"<<std::endl;
	fout.close();
	delete ptrToOnlyInstance_;
	ptrToOnlyInstance_ = nullptr;
}

void Logger::report(const std::string& str){		//report function
	fout << str;
}

int main(){
	Logger::instance() -> report("My first demonstration of report \n");
	Logger::instance() -> report("My second demonstration of report \n");
}