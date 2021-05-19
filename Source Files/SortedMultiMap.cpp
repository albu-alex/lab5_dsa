#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->length=0;
	this->tree.root->info.values = new TValue[INITIAL_CAPACITY];
	this->tree.root = nullptr;
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	return vector<TValue>();
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    return false;
}


int SortedMultiMap::size() const {
	return this->length;
}
///Complexity: Theta(1)

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
}
