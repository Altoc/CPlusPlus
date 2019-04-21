/*
*	Ian Whitesel
*	CSIII Lab10_3
*	Spring 2019
*/

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using std::cout; using std::cin; using std::string; using std::endl;

class State;

class Process{
public:
	Process();

	Process* clone(){return new Process();}

	// behaviors
	void admitted();
	void interrupt();
	void exit();
	void dispatched();
	void wait();
	void continued();

	string report();

	// part of implementation of state pattern
	void changeState(State* s){state_=s;}
private:
	State* state_;
};

// absract state
class State{
public:
	virtual void admitted	(Process*){} 	// provides default implementation
	virtual void interrupt	(Process*){}  	// provides default implementation
	virtual void exit	(Process*){} 	// provides default implementation
	virtual void dispatched	(Process*){} 	// provides default implementation
	virtual void wait	(Process*){} 	// provides default implementation
	virtual void continued	(Process*){} 	// provides default implementation

	virtual string report() =0;

	void changeState(Process* c, State* s){
		c->changeState(s);
	}
};

class New: public State{
public:
	static State* instance(){
		static State* onlyInstance = new New;
		return onlyInstance;
	}
	void admitted(Process*) override;
	string report() override {return "New";}
};

class Ready: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}
	void dispatched(Process*) override;
	string report() override {return "Ready";}
};

class Running: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Running;
		return onlyInstance;
	}
	void interrupt(Process*) override;
	void exit(Process*) override;
	void wait(Process*) override;
	string report() override {return "Running";}
};

class Waiting: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Waiting;
		return onlyInstance;
	}
	void continued(Process*) override;
	string report() override {return "Waiting";}
};

class Terminated: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Terminated;
		return onlyInstance;
	}
	string report() override {return "Terminated";}
};

// state transitions member functions
// New
void New::admitted(Process *p) {
	changeState(p, Ready::instance());
}

// Ready
void Ready::dispatched(Process *p){
	changeState(p, Running::instance());
}

// Running
void Running::interrupt(Process *p) {
	changeState(p, Ready::instance());
} 
void Running::exit(Process *p) {
	changeState(p, Terminated::instance());
}
void Running::wait(Process *p) {
	changeState(p, Waiting::instance());
}

// Waiting
void Waiting::continued(Process *p){
	changeState(p, Ready::instance());
}

// Terminated
// Terminated has no state changes; it is the final state

// Process member functions
Process::Process(){
	state_=New::instance();
}

// handles/behaviors
void Process::admitted(){
	state_->admitted(this);
}
void Process::interrupt(){
	state_->interrupt(this);
}
void Process::exit(){
	state_->exit(this);
}
void Process::dispatched(){
	state_->dispatched(this);
}
void Process::wait(){
	state_->wait(this);
}
void Process::continued(){
	state_->continued(this);
}
string Process::report(){
	return state_->report();
}

void processAdvance(Process* p, std::queue<Process*> rq){
}

int main(){
	srand(time(nullptr));
	Process prototype_process;
	std::vector<Process*> processVec;
	std::queue<Process*> readyQueue;
	for(int i = 0; i <= 4; i++){
		processVec.push_back(prototype_process.clone());
	}
	int CPUCycleNum = 0;
	bool timeSliceBool = false;
	do{
		for(int j = 0; j < processVec.size(); j++){
			CPUCycleNum++;
			std::cout<<"CPU Cycle number "<<CPUCycleNum<<std::endl;
			std::cout<<"Process "<<j<<"'s state: "<<processVec[j]->report()<<std::endl;
		}
		std::cout<<"Advancing processes..."<<std::endl;
		for(int g = 0; g < processVec.size(); g++){
			if(processVec[g]->report() == "New"){
				processVec[g]->admitted();
				readyQueue.push(processVec[g]);	//enter ready queue
			} else if(processVec[g]->report() == "Ready" && timeSliceBool == false){
				processVec[g]->dispatched();
				timeSliceBool = true;
			} else if(processVec[g]->report() == "Running"){
				int runningRandNum = rand() % 3;
				switch(runningRandNum){
					case 0: processVec[g]->exit(); break;
					case 1: processVec[g]->interrupt(); break;
					case 2: processVec[g]->wait(); break;
				}
			} else if(processVec[g]->report() == "Waiting"){
				int waitingRandNum = rand() % 2;
				if(waitingRandNum == 0){
					processVec[g]->continued();	//back to ready queue
				}
			} else if(processVec[g]->report() == "Terminated"){
				delete processVec[g];
				processVec.erase(processVec.begin()+g);
			}
		}
		timeSliceBool = false;
	}while(processVec.size() != 0);
}