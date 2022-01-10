#include "Util.h"

#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <algorithm>
#include <cmath>

string Util::intToBinString(int size, int val) {
	string bin;
	bin = bitset<100>(val).to_string();
	bin = bin.substr(100 - size);
	return bin;
}

int Util::get1s(string x) {
	// returns the number of 1s in a binary string
	int count = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (x[i] == '1')
			count++;
	}
	return count;
}

bool Util::compare(string a, string b) {
	// checks if two string differ at exactly one location or not
	int count = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i])
			count++;
	}

	if (count == 1)
		return true;

	return false;
}

string Util::getDiff(string a, string b) {
	// returs a string that replaces the differ location of two strings with '-'
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i])
			a[i] = '-';
	}

	return a;
}

bool Util::checkEmpty(vector< vector< string> > table) {
	for (int i = 0; i < table.size(); ++i) {
		if (table[i].size() != 0) {
			return false;
		}
	}
	return true;
}

string Util::binToString(string x, string inputName) {
	// Add a string constaining inputName instead of A to Z
	// converts binary string to alphabetic variables

	string out = "";
	// for (int i = 0; i < x.size(); ++i) {
	// 	if (x[i] == '1') {
	// 		char x = inputName[i];
	// 		out += x;
	// 	}
	// 	else if (x[i] == '0') {
	// 		char x = inputName[i];
	// 		out += x;
	// 		out += "'";
	// 	}
	// }

	for (int i = 0; i < x.size(); ++i) {
		if (x[i] == '1') {
			char x = 65 + i;
			out += x;
		}
		else if (x[i] == '0') {
			char x = 65 + i;
			out += x;
			out += "'";
		}
	}
	return out;
}

bool Util::primeIncludes(string imp, string minTerm) {
	// check is a prime implicant satisfies a min term or not
	for (int i = 0; i < imp.size(); ++i) {
		if (imp[i] != '-') {
			if (imp[i] != minTerm[i]) {
				return false;
			}
		}
	}
	return true;
}

int Util::getVar(set<int> comb, vector<string> primeImp) {
	// returns the number of variables in a petrick method combination
	int count = 0;
	set<int> ::iterator itr;
	for (itr = comb.begin(); itr != comb.end(); ++itr) {
		int imp = *itr;
		for (int i = 0; i < primeImp[imp].size(); ++i) {
			if (primeImp[imp][i] != '-')
				count++;
		}
	}
	return count;

}