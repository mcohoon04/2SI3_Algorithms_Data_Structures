#include "BSTSet.h"
#include "MyStack.h"
#include <iostream>
#include <vector>
using namespace std;

BSTSet::BSTSet()
{
	//set root to NULL to represent an empty set
	root = NULL;
}

BSTSet::BSTSet(const std::vector<int>& input)
{
	if(sizeof(input)==0){
		root = NULL;
	}
	else{
		for(auto i:input){
			add(i);
		}
	}
}
void BSTSet::delete_rec(TNode* p){
	if(p!=NULL){
		delete_rec(p->left);
		delete_rec(p->right);
		delete(p);
	}
}
BSTSet::~BSTSet()
{
	delete_rec(root);
}

bool BSTSet::isIn(int v)
{
	//runt time: log n
	TNode* p = root;
	while(p!=NULL){
		if(p->element>v){
			p=p->left;
		}
		else if(p->element<v){
			p=p->right;
		}
		else if(p->element==v){
			return true;
		}
	}
    return false; //change this after completing this function
}

void BSTSet::add(int v)
{
	//time h
	if(isIn(v)==false){
		TNode* p = root;
		TNode* t = NULL;
		TNode* newNode = new TNode(v, NULL, NULL);
		//adds element v to BST
		if(p==NULL){
			root = newNode;
		}
		else{
			while(p!=NULL){
				t=p;
				if(p->element>v){
					p=p->left;
				}
				else if(p->element<v){
					p=p->right;
				}
			}

			if(v<t->element){
				t->left=newNode;
			}
			else if(v>t->element){
				t->right=newNode;
			}
		}
	}
}

bool BSTSet::remove(int v)
{
	//time h
	TNode* current = root;
	TNode* prev = NULL;

	while(current!=NULL && current->element!=v){
		prev=current;
		if(v>current->element){
			current=current->right;
		}
		else{
			current=current->left;
		}
	}
	//Not in tree
	if(current==NULL){
		return false;
	}
	//left child only
	else if(current->right == NULL){
		if(prev==NULL){
			root=current->left;
			delete(current);
			return true;
		}
		else{
			//create node to replace current after deletion
			if(prev->right==current){
				prev->right=current->left;
			}
			else{
				prev->left=current->left;
			}
			delete(current);
			return true;
		}
	}
	//right child only
	else if(current->left == NULL){
			if(prev==NULL){
				root=current->right;
				delete(current);
				return true;
			}
			else{
				//create node to replace current after deletion
				if(prev->right==current){
					prev->right=current->right;
				}
				else{
					prev->left=current->right;
				}
				delete(current);
				return true;
			}
	}
	//two children
	else{
		TNode* prevMin = NULL;
		TNode* Min;

		//find succesor to current node after deletion
		//this will be min value in the right branch of current node
		Min = current->right;
		while(Min->left!=NULL){
			prevMin=Min;
			Min=Min->left;
		}

		//check if prev to Min is current node
		//In this case replace current with the first node to left
		if(prevMin==NULL){
			current->right=Min->right;
		}
		else{
			prevMin->left=Min->right;
		}
		//set current data to successor data and delete successor
		current->element=Min->element;
		delete(Min);
		return true;
	}
    return false;
}

void BSTSet::Union_rec(TNode* p)
{
	if(p!=NULL){
		this->add(p->element);
		Union_rec(p->left);
		Union_rec(p->right);
	}
}

void BSTSet::Union(const BSTSet& s)
{
	if(s.root!=NULL){
		Union_rec(s.root);
	}
}

void BSTSet::int_rec(TNode* p, BSTSet& s, BSTSet& n){
	if(p!=NULL){
		if(s.isIn(p->element)){
			n.add(p->element);
		}
		int_rec(p->left, s,n);
		int_rec(p->right, s,n);
	}
}

void BSTSet::intersection(const BSTSet& s)
{
	if(s.root!=NULL && root!=NULL){
		BSTSet* p = new BSTSet();
		BSTSet* n = new BSTSet();
		n->root = s.root;
		int_rec(root, *n, *p);
		this->root=p->root;
	}
	else{
		root=NULL;
	}

}

void BSTSet::diff_rec(TNode* p)
{
	if(p!=NULL){
			this->remove(p->element);
			diff_rec(p->left);
			diff_rec(p->right);
		}
}

void BSTSet::difference(const BSTSet& s)
{
	if(s.root!=NULL){
		diff_rec(s.root);
	}
}

int BSTSet::size_rec(TNode* p){
	//checks if the pointer is now NUll
	if(p==NULL){
		return 0;
	}
	int sLeft = size_rec(p->left);
	int sRight = size_rec(p->right);
	return sLeft+sRight+1;
}
int BSTSet::size()
{
    return size_rec(root);
}

int BSTSet::height_rec(TNode* p){
	//checks if the pointer is now NUll
	if(p==NULL){
		return 0;
	}
	int hLeft = height_rec(p->left);
	int hRight = height_rec(p->right);
	return max(hLeft,hRight)+1;
}

int BSTSet::height()
{
    return height_rec(root)-1; //change this after completing this function
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	MyStack* n = new MyStack(this->size());
	TNode* p = root;
	while(n->isEmpty()==false || p!=NULL){
		while(p!=NULL){
			n->push(p->element);
			p=p->left;
		}
		int v=n->pop();
		std::cout<<std::to_string(v)<<",";
		p=root;
		while(p!=NULL){
			if(p->element>v){
				p=p->left;
			}
			else if(p->element<v){
				p=p->right;
			}
			else if(p->element==v){
				break;
			}
		}
		p=p->right;

	}
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
