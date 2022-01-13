#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <algorithm>
#include <cmath>
#include "Util.h"

using namespace std;

class Tabulation {
private:
	Util util;
	vector< int > minInt; // min terms in decimal
	vector< string > minBin; // min terms in binary
	int nBits;
	int nMin;  // no of variables
	vector< vector< string> > table;
	vector< string > primeImp;
	vector< set<int> > functions;
	string inputName;

public:
	// void initialise(bool* input, int size);
	void initialise(bool* input, int size, string inputName_);
	void setPrimeImp();
	void minimise();
	void displayFunctions();
	string getFunctions();
	void getPosComb(vector< set<int> >& patLogic, int level, set<int> prod, set< set<int> >& posComb);
	vector< vector< string> > combinePairs(vector< vector< string> > table, set<string>& primeImpTemp);
	void createTable();
	
};