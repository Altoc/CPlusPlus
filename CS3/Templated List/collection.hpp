/*
*	Ian Whitesel
*	CSIII Lab 3
*	Spring 2019
*/

#include<iostream>
#include"list.h"

template <typename T>
class Collection{
public:
	Collection();				//default ctor
	void addItem(const T& item);			//takes an item as the argument and adds it to the collection, does not check for duplicates.
	void removeItem(const T& item);		//takes an item as the argument and removes all instances of this item from the collection.
	T lastItem() const;			//returns the last item added to the collection.
	T firstItem() const;			//returns the first item in the collection.
	void printCollection();			//prints all items in the collection. The printout does not have to be in order.

	template <typename U>
	friend bool equal(const Collection<U>& lhs, const Collection<U>& rhs);

private:
	node<T>* ptr_;				//pointer to current node
	node<T>* firstPtr_;			//pointer to first node in list
	node<T>* lastPtr_;			//pointer to last node in list
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Collection<T>::Collection(){
	ptr_ = NULL;
	firstPtr_ = NULL;
	lastPtr_ = NULL;
};

template <typename T>
void Collection<T>::addItem(const T& item){
	node<T> *itemNode = new node<T>;
	(itemNode)->setData(item);
	if((ptr_ == NULL) && (firstPtr_ == NULL) && (lastPtr_ == NULL)){
		ptr_ = itemNode;
		firstPtr_ = ptr_;
		lastPtr_ = ptr_;
	} else {
		ptr_ = itemNode;
		(lastPtr_)->setNext(ptr_);	//point to new node
		(ptr_)->setLast(lastPtr_);	//point new node's lastPtr to the old last node
		lastPtr_ = itemNode;		//make the new last node be pointed at by lastnodeptr
	}
};

template <typename T>
void Collection<T>::removeItem(const T& item){
	ptr_ = firstPtr_;
	while(ptr_ != lastPtr_){
		if((ptr_)->getData() == item){
			(ptr_)->getLast()->setNext((ptr_)->getNext());
			(ptr_)->getNext()->setLast((ptr_)->getLast());
			delete ptr_;
		}
		ptr_ = (ptr_)->getNext();	//move to next pointer
	}
};

template <typename T>
T Collection<T>::lastItem() const{
	//std::cerr<<(lastPtr_)->getData()<<std::endl;
	return (lastPtr_)->getData();
};

template <typename T>
T Collection<T>::firstItem() const{
	//std::cerr<<(firstPtr_)->getData()<<std::endl;
	return (firstPtr_)->getData();
};

template <typename T>
void Collection<T>::printCollection(){
	if(firstPtr_ == NULL){
		std::cout<<"Collection is empty."<<std::endl;
	} else {
		ptr_ = firstPtr_;
		std::cerr<<"Printing collection: "<<std::endl;
		do{
			std::cout<<(ptr_)->getData()<<std::endl;
			ptr_ = (ptr_)->getNext();
		}while(ptr_ != NULL);
		std::cerr<<"Done printing collection"<<std::endl;
	}
};

template <typename U>
bool equal(const Collection<U>& lhs, const Collection<U>& rhs){
	node<U>* lhsPtr = lhs.firstPtr_;
	node<U>* rhsPtr = rhs.firstPtr_;
	while((lhsPtr != NULL) && (rhsPtr != NULL)){
		std::cerr<<"Left ptr: "<<(lhsPtr)->getData()<<std::endl;
		std::cerr<<"Right ptr: "<<(rhsPtr)->getData()<<std::endl;
		if((lhsPtr)->getData() != (rhsPtr)->getData()){
			return false;
		}
		if(((lhsPtr)->getNext() == NULL) && (rhsPtr)->getNext() != NULL){
			return false;
		}
		if(((lhsPtr)->getNext() != NULL) && (rhsPtr)->getNext() == NULL){
			return false;
		}
		lhsPtr = (lhsPtr)->getNext();
		rhsPtr = (rhsPtr)->getNext();
	}
	return true;
};