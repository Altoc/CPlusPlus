// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014

/*
*	Ian Whitesel
*	CSIII Lab 7
*	Spring 2019
*/

#include <iostream>
#include <iterator>
#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
	DefaultHash(size_t numBuckets = defaultNumBuckets);
	size_t hash(const T& key) const;
	size_t numBuckets() const { return numBuckets_; }

private:
	// default number of buckets in the hash
	static const size_t defaultNumBuckets = 101; 
	size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}

// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
	size_t res = 0;
	for (size_t i = 0; i < sizeof(key); ++i) {
		const unsigned char b = *(reinterpret_cast<const unsigned char *>(&key) + i);
		res += b;
	}
	return res % numBuckets_;
}

////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, 
	  typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{
public:
	typedef pair<const Key, Value> Element;
	// constructor
	// invokes constructors for comparison and hash objects
	hashmap(const Compare& comp = Compare(), const Hash& hash = Hash());

	void rehash(size_t n);

	Element* find(const Key& x);      					// returns pointer to element with key x,
   	                                  						// nullptr if not found
	pair<Value, bool> insert(const Element& x);		    		// inserts the key/value pair 
	pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> erase(const Key& x);         				// erases element with key x, if exists
	Value& operator[] (const Key& x); 					// returns reference on value of element with key,
											// inserts if does not exist private:
private:
	// helper function for various searches
	typename list<Element>::iterator
	findElement(const Key& x, const size_t bucket);

	size_t size_;   // number of elements in the container
	Compare comp_;  // comparison functor, equal_to by default
	Hash hash_;     // hash functor 

	// hash contents: vector of buckets
	// each bucket is a list containing key->value pairs
	vector<list<Element>> elems_;
};

////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// CONSTRUCTOR
// Construct elems_ with the number of buckets.
template <typename Key, 
	  typename Value, 
	  typename Compare, 
	  typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(const Compare& comp, const Hash& hash): 
size_(0), comp_(comp), hash_(hash) {
	elems_ = vector<list<Element>>(hash_.numBuckets());
}

// FIND ELEMENT
// helper function
template <typename Key, 
	  typename Value, 
          typename Compare, 
	  typename Hash>
typename list<pair<const Key, Value>>::iterator 			// return type
hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

	// look for the key in the bucket
	for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
		if (comp_(it->first, x))
			return it;

	return elems_[bucket].end(); 					// element not found
}

// FIND
// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, 
	  typename Value, 
	  typename Compare, 
	  typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {
	size_t bucket = hash_.hash(x);
	auto it=findElement(x, bucket);    				// use the findElement() helper   

	if (it != elems_[bucket].end()) 				// found the element. Return a pointer to it.
		return &(*it); // dereference the iterator to list 	// then take the address of list element
	else 								// didn't find the element -- return nullptr
		return nullptr;
}

// INSERT
// finds the element with key x, inserts an element with that key if none exists yet.
// Returns a reference to the value corresponding to that key.
template <typename Key,
	  typename Value,
	  typename Compare,
	  typename Hash>
pair<Value, bool> hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
	size_t bucket = hash_.hash(x.first);
	auto it = findElement(x.first, bucket);    			// try to find the element

	pair<Value, bool> result;
	result.first = x.second;

	if (it == elems_[bucket].end()) {				// if not found, insert a new one
		++size_;
		elems_[bucket].push_back(x);
		result.second = true;
	} else {							// if already in hashmap, return it
		result.second = false;
	}

	return(result);
}

// ERASE
// removes the Element with key x, if it exists
template <typename Key, 
	  typename Value, 
	  typename Compare, 
	  typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    				// try to find the element
	pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> result;
	if (it != elems_[bucket].end()) {    				// the element exists, erase it
		elems_[bucket].erase(it);
		--size_;
		std::advance(it, 1);
		result.first = &(*it);
		result.second = true;
		return result;
	}
	result.second = false;
	return result;
}

// OPERATOR[] OVERLOAD
// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, 
	  typename Value, 
	  typename Compare, 
	  typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {
//	std::cerr<<"["<<x<<"] overload called"<<std::endl;
	pair<Value, bool> check = insert(make_pair(x, Value()));
	Element* found = find(x);
	return found->second;
}

template <typename Key, 
	  typename Value, 
	  typename Compare, 
	  typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n){
	//elems_ = vector<list<Element>>(hash_.numBuckets());
	std::cerr<<"curr: "<<hash_.numBuckets()<<std::endl
	<<"n: "<<n<<std::endl;
	if(n <= hash_.numBuckets()){
		std::cerr<<"smaller"<<std::endl;
	} else {
		Hash newHash(n);
		vector<list<Element>> result = vector<list<Element>>(newHash.numBuckets());
		elems_.clear();
		move(elems_.begin(), elems_.end(), back_inserter(result));
		result.clear();
		std::cerr<<"larger"<<std::endl;
		std::cerr<<"new: "<<hash_.numBuckets()<<std::endl;
	}
}