#include "Poly.h"
#include <iostream>
#include <math.h>
using namespace std;

Poly::Poly()
{
    // create the zero polynomial
    head = new PolyNode(-1, 0, NULL);
    degree = -1;
    term_num = 0;
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
    //construct the polynomial
    // create the zero polynomial(i.e. dummy node)
    head = new PolyNode(-1, 0, NULL);

    //set the degree of poly and number of terms
    degree = -1;
    term_num = 0;

    //begin creating nodes
    for(int i=deg.size()-1;i>=0;i--){
    	if(coeff[i]!=0){
    		if(deg[i]>degree){
    			degree = deg[i];
    		}
    		 PolyNode* p = new PolyNode(deg[i], coeff[i], head->next);
    		 head->next = p;
    		 term_num++;
    	}
    }
}

Poly::~Poly()
{
    PolyNode* p = head->next;
    PolyNode* next;
    //free all memory used
    while(p != NULL){
        next = p->next;
        delete p;
        p = next;
        //term_num--;
    }
}

void Poly::addMono(int i, double c)
{
	//Run time: O(n)
	//Space Complexity: O(1)
if( c != 0 ){
    if( i > degree ){
        PolyNode* node = new PolyNode(i, c, head->next);
        head->next = node;
        degree = i;
        term_num++;
    }

    else{
        PolyNode* node = head->next;
        PolyNode* current = head;
        while(node != NULL){
            if(node->deg > i && node->next == NULL){
                node->next = new PolyNode(i, c, NULL);
                //current->next = add;
                term_num++;
                break;
            }
            else if(node->deg > i){
                node = node->next;
                current = current->next;
            }
            else if(node->deg < i){
                PolyNode* add = new PolyNode(i, c, current->next);
                current->next = add;
                term_num++;
                break;
            }
            else{ //node->deg == i
                node->coeff += c;
                if( node->coeff == 0){
                    term_num--;
                    node->deg = -1;
                    current->next = node->next; //current is previous
                    delete node;
                    if(term_num == 0)
                        degree = -1;



                    else if(head->next->deg != degree)
                        degree = head->next->deg;
                    }
                break;
                }
            }
        }
    }
}

void Poly::addPoly(const Poly& p)
{
	//Run time: O(n^2)
	//Space Complexity: O(n)

	//adds polynomial p to this polynomial.
	//The method modifies this polynomial, but it does not modify polynomial p.

	//node to be added
	PolyNode* add = p.head->next;

	while(add!=NULL){
		//use addMono to add, 'add', to this poly
		this->addMono(add->deg,add->coeff);
		//increment add to go to next node in p
		add = add->next;
	}

}

void Poly::multiplyMono(int i, double c)
{
		//Run time: O(n)
		//Space Complexity: O(0)
		PolyNode* current = head->next;
		PolyNode* p = head;
		if(c==0){
			// create the zero polynomial
			head = new PolyNode(-1, 0, NULL);
		    degree = -1;
		    term_num = 0;
		}
		else{
			while(current!=NULL){
				current->deg = current->deg+i;
				current->coeff = (current->coeff)*c;
				if (current->coeff == 0){
					p->next = current->next;
					delete current;
					current = p;
					term_num--;
				}
				if(current->deg>degree){
					degree = current->deg;
				}
				p = p->next;
				current = current->next;
				}
		}
}

void Poly::multiplyPoly(const Poly& p)
{
		//Run time: O(n^3)
		//Space Complexity: O(n*m)
		//create empty polynomial for output
		Poly empty = Poly();
		//create
		PolyNode* current = p.head->next;
		while (current!=NULL){
			Poly temp = Poly();
			duplicate(temp);
			temp.multiplyMono(current->deg, current->coeff);
			empty.addPoly(temp);
			current = current->next;
		}

		empty.duplicate(*this);
}

void Poly::duplicate(Poly& outputPoly){
	//Run time: O(n)
	//Space Complexity: O(n)
	if(this->degree==-1){
		// create the zero polynomial
		outputPoly.head = new PolyNode(-1, 0, NULL);
		outputPoly.degree = -1;
		outputPoly.term_num = 0;
	}
	else{
			PolyNode* node = outputPoly.head;
		    PolyNode* current = head->next;
		    outputPoly.degree = current->deg;
		    outputPoly.term_num = 0;
		    while(current!=NULL){
		        node->next = new PolyNode(current->deg,current->coeff,NULL);
		        node=node->next;
		        current=current->next;
		        outputPoly.term_num++;
		    }
	}

}

int Poly::getDegree()
{
	//Run time: theta(1)
	//Space Complexity: theta(1)
    //return the known degree of this polynomial
    return degree;
}

int Poly::getTermsNo()
{
	//Run time: theta(1)
	//Space Complexity: theta(1)
    //return the known number of terms in this polynomial
    return term_num;
}

double Poly::evaluate(double x)
{
	//Run time: theta(n)
	//Space Complexity: theta(1)
	//create variable to hold product
	double prod = 0.0;
	//create node p to iterate through linked List
	PolyNode* p = head->next;
	//iterate through linked list
	while(p!=NULL){
		prod+=(p->coeff)*pow(x,p->deg);
		p=p->next;
	}
    return prod;
}

std::string Poly::toString()
{
    //return a string in form "degree=3; a(3)=4.0; a(1)=5.0; a(0)=2.0” representing poly
    std::string output = "degree="+std::to_string(degree)+";";
    //output.append(std::to_string(degree)+"; ");
    PolyNode* p;
    for(p=head;p!=NULL;p=p->next){
        output.append(" a("+std::to_string(p->deg)+")="+std::to_string(p->coeff)+";");
    }

    return output;//change this after completing this function
}
