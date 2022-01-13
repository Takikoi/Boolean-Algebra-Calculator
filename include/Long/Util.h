#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <algorithm>
#include <cmath>

using namespace std;

class Util
{
public:
	string intToBinString(int size, int val);
	int get1s(string x);
	bool compare(string a, string b);
	string getDiff(string a, string b);
	bool checkEmpty(vector< vector< string> > table);

	string binToString(string x, string inputName);
	
	bool primeIncludes(string imp, string minTerm);
	int getVar(set<int> comb, vector<string> primeImp);
};