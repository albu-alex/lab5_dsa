#include "SMMIterator.h"
#include "SortedMultiMap.h"

///Inorder iterator(left - root - right)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->tree = this->map.tree;
	this->stack = new Node*[this->map.length];
	this->stack_index = -1;
	this->values_index = 0;
	this->current_node = this->map.tree.root;
	while(this->current_node != nullptr){
        this->stack_index++;
	    this->stack[this->stack_index] = this->current_node;
	    this->current_node = this->current_node->left;
	}
	if(this->stack_index != -1){
	    this->current_node = this->stack[this->stack_index];
	}
	else
	    this->current_node = nullptr;
}
///Complexity: Best case: Theta(1), Worst case:Theta(N) => Average case: O(N)

void SMMIterator::first(){
    this->stack_index = -1;
    this->values_index = 0;
    this->current_node = this->map.tree.root;
    while(this->current_node != nullptr){
        this->stack_index++;
        this->stack[this->stack_index] = this->current_node;
        this->current_node = this->current_node->left;
    }
    if(this->stack_index != -1){
        this->current_node = this->stack[this->stack_index];
    }
    else
        this->current_node = nullptr;
}
///Complexity: Best case: Theta(1), Worst case:Theta(N) => Average case: O(N)

void SMMIterator::next(){
	if(!this->valid())
	    throw exception();
    if(this->values_index < this->current_node->info.size - 1){
	    this->values_index++;
	    return;
	}
	this->values_index = 0;
	Node* node = this->stack[this->stack_index];
    this->stack_index--;
    if(node->right != nullptr){
        node = node->right;
        while(node != nullptr){
            this->stack_index++;
            this->stack[this->stack_index] = node;
            node = node->left;
        }
    }
    if(this->stack_index != -1)
        this->current_node = this->stack[this->stack_index];
    else
        this->current_node = nullptr;
}
///Complexity: Best case: Theta(1), Worst case:Theta(N) => Average case: O(N)

bool SMMIterator::valid() const{
	if(current_node == nullptr)
	    return false;
	return true;
}
///Complexity: Theta(1)

TElem SMMIterator::getCurrent() const{
	if(!valid())
	    throw exception();
	return TElem{this->current_node->info.key, this->current_node->info.values[this->values_index]};
}
///Complexity: Theta(1)

