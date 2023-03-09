#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_

#include <vector>
#include <iostream>
using namespace std;
class HashTableQuad
{
private:
	// must contain this private field
	vector<int> table;
	// define other private fields to store:
	// 1. the size of the table
	int size;
	// 2. the number of keys stored in the table
	int num_keys;
	// 3. the maximum load factor allowed
	double max_load;

public:
	// required constructor
	HashTableQuad(int maxNum, double load);
	//additional
	HashTableQuad(int tsize, double load, bool bysize);
	// required methods
	void insert(int n);
	int insertCount(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	//additional methods
	bool isPrime(int n);
	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */
