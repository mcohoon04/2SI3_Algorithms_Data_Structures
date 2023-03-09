#include "HashTableQuad.h"
using namespace std;
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

HashTableQuad::HashTableQuad(int maxNum, double load)
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
HashTableQuad::HashTableQuad(int tsize, double load, bool bysize)
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
bool HashTableQuad::isPrime(int x){
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
void HashTableQuad::insert(int n)
{
	if(isIn(n)==false){
		int index = n%size;
		int i=1;
		int count = 0;
		while(table[index]!=0){
			index=(n+(i*i))%size;
			count++;
			i++;
			if(i>size)
			{
				return;
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
int HashTableQuad::insertCount(int n)
{
	int count=0;
	if(isIn(n)==false){
		int index = n%size;
		int i=1;
		int count = 1;
		while(table[index]!=0){
			index=(n+(i*i))%size;
			count++;
			i++;
			if(i>size)
			{
				return 0;
			}
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

void HashTableQuad::rehash()
{
	int tsize = 2*size;
	while(!isPrime(tsize)){
		tsize++;
	}

	HashTableQuad* temp = new HashTableQuad(tsize,max_load,true);

	for(int i: table){
		if(i!=0){
			temp->insert(i);
		}
	}

	table = temp->table;
	size = temp->size;
}

bool HashTableQuad::isIn(int n)
{
	int index = n%size;
	int i = 1;
    int count = 0;
	while(table[index]!=n){
	    index=(n+(i*i))%size;
	    count++;
	    i++;
    	if(count==size-1){
    		return false;
	    }
	}
	    return true;
}

void HashTableQuad::printKeys()
{
	for(int i=0;i<size;i++){
		if(table[i]!=0){
	   		cout<<table[i]<<" ";
    	}
	}
}

void HashTableQuad::printKeysAndIndexes()
{
	for(int i=0;i<size;i++){
		if(table[i]!=0){
			cout<<"I:"<<i<<" ";
			cout<<"K:"<<table[i]<<" ";
		}
	}
}

int HashTableQuad::getNumKeys() {
	// TODO, change following code after completing this function
    return num_keys;
}

int HashTableQuad::getTableSize() {
	// TODO, change following code after completing this function
    return size;
}

double HashTableQuad::getMaxLoadFactor() {
	// TODO, change following code after completing this function
    return max_load;
}

std::vector<double> HashTableQuad::simProbeSuccess()
{
	vector<double> result(9);
	    double load = 0.1;
	    //run sim for each load value
	    for(int k=0;k<4;k++){
	    	double average=0;
	    	//run sim 100 times
	    	for(int j=0;j<100;j++){
	    		HashTableQuad* temp = new HashTableQuad(1000,load);
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
