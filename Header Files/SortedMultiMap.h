#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
#define NULL_KEY -11111
#define INITIAL_CAPACITY 11
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class KeyValues{
public:
    TKey key;
    TValue *values;
    int capacity=INITIAL_CAPACITY;
    int size=0;
};


class Node{
public:
    KeyValues info;
    Node* left;
    Node* right;
};


class BST{///Binary Search Tree
public:
    Node* root;
};

class SortedMultiMap {
	friend class SMMIterator;
    private:
		BST tree;
		int length;
		Relation relation;

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // This is used in order to resize the dynamic array of values of a key
    void resize(KeyValues& keyValues);

    //limits the number of values for a key to maxSize.
    // From the keys with more than maxSize values, some values (does not matter which ones) will be removed until the number of associated values will be equal to maxSize.
    // If a key has less than maxSize values, they will not be changed. The limitation does not have to be respected after the call to the function (so new pairs can be added).
    // Returns the total number of removed values.
    int trimValues(int maxSize);


    // destructor
    ~SortedMultiMap();
};
