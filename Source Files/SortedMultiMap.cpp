#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->length=0;
	this->tree.root = nullptr;
	this->relation=r;
}


void SortedMultiMap::add(TKey c, TValue v) {
	///Possible cases:
	///1)When root is nullptr(size=0)
	///2)When we only have the root(size=1)
	///3)If key already exists
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	return vector<TValue>();
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	///Possible cases:
	///1)When we only have the root
	///2)When we remove the only element associated to a key
	///3)When we remove an element associated to a key
	///4)When we remove the only element associated to a root
    return false;
}


int SortedMultiMap::size() const {
	return this->length;
}
///Complexity: Theta(1)

bool SortedMultiMap::isEmpty() const {
	return this->length==0;
}
///Complexity: Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
}
