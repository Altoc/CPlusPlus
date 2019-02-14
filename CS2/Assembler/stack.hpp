//stack implementation with link lists
//Ian Whitesel
//Summer 2018

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cassert>
#include "node.hpp"
#include "string/string.hpp"

template<typename T>
class Stack{
public:
	Stack();				//default ctor
	Stack(const Stack<T>& rhs);		//copy ctor
	void swap(Stack<T> rhs);		//const time swap
	Stack<T>& operator=(Stack<T> rhs);	//assignment overload
	~Stack();				//destructor
	
	void push(const T& item);	//increment stack and add new value
	T pop();			//return value and take it off stack	
	T& top() const;			//return current TOS
	bool isEmpty() const;		//check if empty
	bool isFull() const;		//check if full
private:
	Node<T> *tos;	//points to the node at the top of the stack
};

template<typename T>
Stack<T>::Stack(){				//default ctor
	tos = 0;	//set TOS to NULL, as no nodes have been added to stack
}

template<typename T>
Stack<T>::Stack(const Stack<T>& rhs){		//copy ctor
	Node<T> *bottom;
	Node<T> *temp = rhs.tos;
	
	tos = 0;	//set TOS to NULL
	
	while(temp != 0){		//while temp, which is pointing to rhs's top of the stack, does not equal NULL,
		if(tos == 0){			//check if TOS of lhs is equal to NULL,
			tos = new Node<T>(temp->data);	//if it is, set tos of lhs to a new Node of generic type, with the value of rhs's data accessed via temp pointer,
			bottom = tos;				//and set bottom pointer to that new TOS
		}else{							//else if,
			bottom->next = new Node<T>(temp->data);			//bottom, which is pointing to lhs's next pointer, which is pointing to the next nodes data, is equal to a new node of generic type, with the value of rhs's data via temp pointer
			bottom = bottom->next;				//and set bottom to the next pointer of lhs
		}
		temp = temp->next;				//after all that, set temp pointer to point to the next pointer of the node it was pointing to, moving it down to the next node
	}
}

template<typename T>
void Stack<T>::swap(Stack<T> rhs){		 //swap function
	Node<T> *temp;
	
	temp = tos;
	tos = rhs.tos;
	rhs.tos = temp;
}

template<typename T>
Stack<T>::~Stack(){				//destructor
	Node<T> *temp;			//create temp Node<T> pointer
	
	while(tos != 0){		//while there is still a value at TOS,
		temp = tos;		//point temp to TOS,
		tos = tos->next;	//point TOS to the next node,
		delete temp;		//and delete the node temp is pointing to
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> rhs){	//assignment operator overload
	swap(rhs);
	return *this;
}

template<typename T>
T& Stack<T>::top() const{			//top function
	return tos->data;
}

template<typename T>
T Stack<T>::pop(){				//pop function
	assert(tos != 0);
	T result = tos->data;	//create a variable 'result' and equate it to TOS's data

	Node<T> *temp = tos;	//create a temporary Node pointer and point it to TOS
	tos = tos->next;	//move TOS to the next node down

	delete temp;		//delete temp
	return result;		//return the deleted node's value
}

template<typename T>
void Stack<T>::push(const T& newItem){		//push function
	assert(isFull() == false);	//make sure stack is not yet full
	
	Node<T> *temp = new Node<T>(newItem);	//create a new Node with user value //create a temporary Node pointer, point it to a new Node of generic type with the value of newItem
	temp->next = tos;	//connect the new Node to top of stack //point temp's Node's next pointer to TOS
	tos = temp;	//set TOS to the new node, as it is on top now //point TOS to temp
}

template<typename T>
bool Stack<T>::isFull() const{			//check if stack full !!!!!!NEVER TEST THIS FUNCTION!!!!!!!
	using std::nothrow;
	Node<T> *temp = new(nothrow) Node<T>;	//request a new Node, if new request fails, dont crash program
	
	if(temp == 0)		//if the temp pointer is pointing to NULL, which it should not be if it was just created,
		return true;	//return true, as it is full
	else			//if it is NOT pointing to NULL,
		delete temp;	//delete temp,
	
	return false;		//and return false, as it was able to allocate a new node, thus not full
}

template<typename T>
bool Stack<T>::isEmpty() const{
	if(tos == 0)		//if there is no Node at TOS
		return true;	//return true, it is empty
	return false;		//else, return false, as there was a Node at TOS
}

#endif //STACK_H