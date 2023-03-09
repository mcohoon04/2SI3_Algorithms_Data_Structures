#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class HugeInteger
{
private:


public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
	vector<int> HI;
	bool isNeg;
};

#endif /* HUGEINTEGER_H_ */
