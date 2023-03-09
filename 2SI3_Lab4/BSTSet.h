#ifndef BSTSET_H_
#define BSTSET_H_

#include "TNode.h"
#include <vector>
#include <cstddef>

class BSTSet
{
private:
	// must contain only one private field
	TNode* root = NULL;

public:
	// required constructors/destructor
	BSTSet();
	BSTSet(const std::vector<int>& input);
	~BSTSet();

	// required methods
	bool isIn(int v);
	void add(int v);
	bool remove(int v);
	void Union(const BSTSet& s);
	void intersection(const BSTSet& s);
	void difference(const BSTSet& s);
	int size();
	int height();
	void printNonRec(); // create and use class MyStack

	//additional methods
	int height_rec(TNode* p);
	int size_rec(TNode* p);
	void Union_rec(TNode* p);
	void diff_rec(TNode* p);
	void int_rec(TNode* p, BSTSet& s, BSTSet& n);
	void delete_rec(TNode* p);
	//void add_rec(int v, TNode* p);
	//bool remove_rec(int v, TNode* p);
	//TNode* minVal(TNode* p);


	// provided recursive print method
	void printBSTSet();

	// Used for testing
	TNode* getRoot()
	{
		return root;
	}

private:
	// provided helper methods
	void printBSTSet(TNode* t);
};

#endif /* BSTSET_H_ */
