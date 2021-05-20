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
	if(this->tree.root == nullptr) {//adding the first key of the tree
        this->tree.root->info.key = c;
        this->tree.root->info.values[this->tree.root->info.size] = v;
        this->tree.root->right = nullptr;
        this->tree.root->left = nullptr;
        this->tree.root->info.size++;
        this->length++;
        return;
    }
    if(this->tree.root->info.key == c){//adding a value to the values of the root
        this->tree.root->info.values[this->tree.root->info.size] = v;
        this->tree.root->info.size++;
        this->length++;
        return;
    }
    Node* current_node = this->tree.root;
    while(current_node->info.key != c && current_node!= nullptr){
        if(this->relation(c, current_node->info.key))
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }
    //if(current_node == nullptr)
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
