/*
*	Ian Whitesel
*	CSIII Lab10_2
*	Spring 2019
*/

#include <iostream>
#include <string>

using std::cout; using std::cin; using std::string; using std::endl;

class State;

class Process{
public:
	Process();

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
private:
	// here and elsewhere should be stated private constructor/assignment
	// to correctly implement singleton, skipped to simplify code
};

class Ready: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}
	void dispatched(Process*) override;
	string report() override {return "Ready";}
private:
	// here and elsewhere should be stated private constructor/assignment
	// to correctly implement singleton, skipped to simplify code
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
private:
	// here and elsewhere should be stated private constructor/assignment
	// to correctly implement singleton, skipped to simplify code
};

class Waiting: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Waiting;
		return onlyInstance;
	}
	void continued(Process*) override;
	string report() override {return "Waiting";}
private:
	// here and elsewhere should be stated private constructor/assignment
	// to correctly implement singleton, skipped to simplify code
};

class Terminated: public State{
public:
	static State* instance(){
		static State* onlyInstance = new Terminated;
		return onlyInstance;
	}
	string report() override {return "Terminated";}
};

/* Examples:
void Hungry::eat(Character *c){
	changeState(c, Full::instance());
}
void Hungry::skipLunch(Character *c){
	changeState(c, Dead::instance());
}
*/
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

int main(){
	Process process_1;
	cout << "process_1 is " << process_1.report() << endl;

	while(process_1.report() != "Terminated"){
		cout << "admit[a] | interrupt[i] | exit[e] | dispatch[d] | wait[w] | continue[c]";
		char action; cin >> action;
		switch(action){
			case 'a': process_1.admitted(); break;
			case 'i': process_1.interrupt(); break;
			case 'e': process_1.exit(); break;
			case 'd': process_1.dispatched(); break;
			case 'w': process_1.wait(); break;
			case 'c': process_1.continued(); break;
		}
		cout << "process_1 is " << process_1.report() << endl;
	}

	// demonstrates that two Processes may be in two different states
	Process process_2;
	cout << "process_1 is " << process_1.report() << " while "
	<< "process_2 is " << process_2.report() << endl;
}