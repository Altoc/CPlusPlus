//Node impletmentation for stacks and queues
//Ian Whitesel
//Summer 18

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

template<typename T>
class Node{
public:
	Node(){next = NULL;}						//default ctor
	Node(const T& userData){data = userData;next = NULL;}		//user value ctor	

	T data;			//variable to hold content of a node
	Node<T> *next;		//points to the next node in the list
};

#endif //NODE_HPP