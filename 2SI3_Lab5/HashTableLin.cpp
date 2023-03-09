#include "HashTableLin.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

HashTableLin::HashTableLin(int maxNum, double load)
{
    num_keys = 0;
    max_load = load;
    int x = (int)ceil(maxNum/load);
	while(!isPrime(x)){
		x++;
	}
	size = x;
	table = vector<int>(size);
}

HashTableLin::HashTableLin(int tsize, double load, bool bysize)
{
    num_keys = 0;
    max_load = load;
    int x = tsize;
	while(!isPrime(x)){
		x++;
	}
	size = x;
	table = vector<int>(size);
}

bool HashTableLin::isPrime(int x){
	//1 is not prime
	if(x==1){
		return false;
	}
	//initialize divisor
	int k=2;
	//check all divisors <=sqrt(x)
	while(k*k<=x){
		//check if divisible
		if(x%k==0){
			return false;
		}
		k++;
	}
	return true;
}

void HashTableLin::insert(int n)
{
	//time complex: worst case - theta(n) best case - theta(1)
	if(isIn(n)==false){
		int index = n%size;
		while(table[index]!=0){
			if(index==size-1){
				index=0;
			}
			else{
				index++;
			}
		}
		table[index]=n;
		num_keys++;
		double load = num_keys/(double)size;
		if(load>max_load){
			this->rehash();
		}
	}
}

int HashTableLin::insertCount(int n)
{
	int count=0;
	//time complex: worst case - theta(n) best case - theta(1)
	if(isIn(n)==false){
		count=1;
		int index = n%size;
		while(table[index]!=0){
			if(index==size-1){
				index=0;
			}
			else{
				index++;
			}
			count++;
		}
		table[index]=n;
		num_keys++;
		double load = num_keys/(double)size;
		if(load>max_load){
			this->rehash();
		}
	}
	return count;
}

void HashTableLin::rehash()
{
	//time complex: theta(numKeys)
	//space complexity:
	int tsize = 2*size;
	while(!isPrime(tsize)){
		tsize++;
	}

	HashTableLin* temp = new HashTableLin(tsize,max_load,true);

	for(int i: table){
		if(i!=0){
			temp->insert(i);
		}
	}

	table = temp->table;
	size = temp->size;
}

bool HashTableLin::isIn(int n)
{
	//time complex: worst case - theta(n) best - theta(1)
    int index = n%size;
    int count = 0;
    while(table[index]!=n){
    	index++;
    	if(index==size){
    		index=0;
    	}
    	count++;
    	if(count==size-1){
    		return false;
    	}
    }
    return true;
}

void HashTableLin::printKeys()
{
    for(int i=0;i<size;i++){
    	if(table[i]!=0){
    		cout<<table[i]<<" ";
    	}
    }
}

void HashTableLin::printKeysAndIndexes()
{
	for(int i=0;i<size;i++){
		if(table[i]!=0){
			cout<<"I:"<<i<<" ";
			cout<<"K:"<<table[i]<<" ";
		}
	}
}

int HashTableLin::getNumKeys() {
	//return the number of keys
    return num_keys;
}

int HashTableLin::getTableSize() {
	//return the size of table
    return size;
}

double HashTableLin::getMaxLoadFactor() {
	//return max load
    return max_load;
}

std::vector<double> HashTableLin::simProbeSuccess()
{
    vector<double> result(9);
    double load = 0.1;
    //run sim for each load value
    for(int k=0;k<9;k++){
    	double average=0;
    	//run sim 100 times
    	for(int j=0;j<100;j++){
    		HashTableLin* temp = new HashTableLin(1000,load);
    		double probes = 0;
    		double keys = 0;
			srand(time(NULL));
			//insert 100000 random numbers
			for(int i=0;i<1000;i++){
				int n = rand();
				int c = temp->insertCount(n);
				if(c!=0){
					keys++;
				}
				probes+=c;
			}
			average+=(probes/keys);
    	}
    	average=average/100.0;
    	result[k]=average;
    	load+=0.1;
    }
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
