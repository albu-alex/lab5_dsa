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
///Complexity: Theta(1)


void SortedMultiMap::add(TKey c, TValue v) {
	if(this->tree.root == nullptr) {//adding the first key of the tree
        this->tree.root = new Node();
	    this->tree.root->info.key = c;
	    this->tree.root->info.values = new TValue[INITIAL_CAPACITY];
        this->tree.root->info.values[this->tree.root->info.size] = v;
        this->tree.root->right = nullptr;
        this->tree.root->left = nullptr;
        this->tree.root->info.size++;
        this->length++;
        return;
    }
    if(this->tree.root->info.key == c){//adding a value to the values of the root
        if(this->tree.root->info.size == this->tree.root->info.capacity-1){
            this->resize(this->tree.root->info);
        }
        this->tree.root->info.values[this->tree.root->info.size] = v;
        this->tree.root->info.size++;
        this->length++;
        return;
    }
    Node* current_node = this->tree.root;
    Node* previous_node = new Node();
    while(current_node != nullptr && current_node->info.key != c){
        previous_node = current_node;
        if(this->relation(c, current_node->info.key))
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }
    Node* new_node = new Node();
    if(current_node == nullptr){
        new_node->info.values = new TValue[INITIAL_CAPACITY];
        if(this->relation(c, previous_node->info.key))
            previous_node->left = new_node;
        else
            previous_node->right = new_node;
        new_node->info.key=c;
        new_node->info.values[new_node->info.size] = v;
        new_node->info.size++;
        this->length++;
        return;
    }
    if(current_node->info.size == current_node->info.capacity-1){
        this->resize(current_node->info);
    }
    current_node->info.values[current_node->info.size] = v;
    current_node->info.size++;
    this->length++;
}
///Complexity: Best case:Theta(1), Worst case:Theta(height_of_tree+values_size) => Average case: O(height_of_tree+values_size)


void SortedMultiMap::resize(KeyValues &keyValues) {
    keyValues.capacity*=2;
    auto resized_array = new TValue[keyValues.capacity];
    for(int i=0;i<keyValues.capacity/2;i++)
        resized_array[i] = keyValues.values[i];
    delete[] keyValues.values;
    keyValues.values = resized_array;
}
///Complexity: Theta(capacity/2)


vector<TValue> SortedMultiMap::search(TKey c) const {
	Node* current_node = this->tree.root;
	vector<TValue> values;
	while(current_node != nullptr && current_node->info.key != c){
        if(this->relation(c, current_node->info.key))
            current_node = current_node->left;
        else
            current_node = current_node->right;
	}
	if(current_node != nullptr){
	    for(int i=0;i<current_node->info.size;i++)
	        values.push_back(current_node->info.values[i]);
	}
	return values;
}
///Complexity: Best case: Theta(1), Worst case: Theta(height_of_tree) => Average case: O(height_of_tree)


bool SortedMultiMap::remove(TKey c, TValue v) {
    Node* current_node = this->tree.root;
    Node* previous_node;
    while(current_node != nullptr && current_node->info.key != c){
        previous_node = current_node;
        if(this->relation(c, current_node->info.key))
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }
    if(current_node == nullptr)
        return false;
    if(current_node->left == nullptr && current_node->right == nullptr){
        if(current_node->info.size > 1){
            int i=0;
            while(i<current_node->info.size && v != current_node->info.values[i])
                i++;
            if(i==current_node->info.size)
                return false;
            while(i<current_node->info.size-1) {
                current_node->info.values[i] = current_node->info.values[i + 1];
                i++;
            }
            current_node->info.size--;
            this->length--;
            return true;
        }
        if(current_node->info.values[0] != v)
            return false;
        current_node = previous_node;
        this->length--;
        if(this->length == 0)
            this->tree.root = nullptr;
        return true;
    }
    if(current_node->left != nullptr && current_node->right!= nullptr){
        if(current_node->info.size > 1){
            int i=0;
            while(i<current_node->info.size && v != current_node->info.values[i])
                i++;
            if(i==current_node->info.size)
                return false;
            while(i<current_node->info.size-1) {
                current_node->info.values[i] = current_node->info.values[i + 1];
                i++;
            }
            current_node->info.size--;
            this->length--;
            return true;
        }
        Node* node_to_be_removed = current_node;
        current_node = current_node->left;
        while(current_node != nullptr)
            current_node = current_node->right;
        node_to_be_removed = current_node;
        current_node = nullptr;
        this->length--;
        return true;
    }
    if(current_node->info.size > 1){
        int i=0;
        while(i<current_node->info.size && v != current_node->info.values[i])
            i++;
        if(i==current_node->info.size)
            return false;
        while(i<current_node->info.size-1) {
            current_node->info.values[i] = current_node->info.values[i + 1];
            i++;
        }
        current_node->info.size--;
        this->length--;
        return true;
    }
    if(current_node->info.values[0] != v)
        return false;
    if(current_node == this->tree.root){
        if(this->tree.root->left != nullptr)
            this->tree.root = this->tree.root->left;
        else
            this->tree.root = this->tree.root->right;
        this->length--;
        return true;
    }
    if(current_node->left != nullptr)
        current_node = current_node->left;
    else
        current_node = current_node->right;
    this->length--;
    return true;
}
///Complexity: Best case: Theta(1), Worst case:Theta(height_of_tree+values_size) => Average complexity: O(height_of_tree+values_size)


int SortedMultiMap::size() const {
	return this->length;
}
///Complexity: Theta(1)

int SortedMultiMap::trimValues(int maxSize) {
    int elements_removed = 0;
    auto stack = new Node*[this->length];
    int stack_index = -1;
    Node* current_node = this->tree.root;
    while(current_node != nullptr){
        stack_index++;
        if(current_node->info.size > maxSize){
            elements_removed += current_node->info.size - maxSize;
            current_node->info.size = maxSize;
        }
        stack[stack_index] = current_node;
        current_node = current_node->left;
    }
    if(stack_index != -1)
        current_node = stack[stack_index];
    else
        current_node = nullptr;
    while(current_node != nullptr && stack_index !=-1){
        current_node = stack[stack_index];
        stack_index--;
        if(current_node->right != nullptr){
            while(current_node != nullptr){
                stack_index++;
                if(current_node->info.size > maxSize){
                    elements_removed += current_node->info.size - maxSize;
                    current_node->info.size = maxSize;
                }
                stack[stack_index] = current_node;
                current_node = current_node->left;
            }
        }
    }
    return elements_removed;
}
///Complexity: Theta(N)

bool SortedMultiMap::isEmpty() const {
	return this->length==0;
}
///Complexity: Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
///Complexity: Theta(1)

SortedMultiMap::~SortedMultiMap() {
    Node* current_node = this->tree.root;
    auto stack = new Node*[this->length];
    int stack_index = -1;
    while(current_node != nullptr){
        stack_index++;
        stack[stack_index] = current_node;
        current_node = current_node->left;
    }
    if(stack_index != -1)
        current_node = stack[stack_index];
    else
        current_node = nullptr;
    while(current_node != nullptr && stack_index !=-1){
        current_node = stack[stack_index];
        delete stack[stack_index];
        stack_index--;
        if(current_node->right != nullptr){
            while(current_node != nullptr){
                stack_index++;
                stack[stack_index] = current_node;
                current_node = current_node->left;
            }
        }
    }
}
///Complexity: Theta(N)
