#include "Tabulation.h"

#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <algorithm>
#include <cmath>

void Tabulation::initialise(bool* input, int size, string inputName_) { //REWORK

	inputName = inputName_;
	//REWORK
	nMin = 0;
	int s = 1;
	while (pow(2, s) < size)
	{
		s++;
	}
	nBits = s;

	for (int i = 0; i < size; ++i)
	{
		if (input[i] == 1)
			++nMin;
	}

	for (int i = 0; i < size; ++i)
	{
		if (input[i] == 1)
		{
			int x = i;
			minInt.push_back(x);
			minBin.push_back(util.intToBinString(nBits, x));
		}

	}


	/*cout << "Enter min terms:" << endl;
	for (int i = 0; i < nMin; ++i) {
		int x;
		cin >> x;
		minInt.push_back(x);
		minBin.push_back(util.intToBinString(nBits, x));
	}*/

	/*cout << "\nBinary representation of provided min terms:" << endl;
	for (int i = 0; i < nMin; ++i) {
		cout << i << ") " << minBin[i] << endl;
	}*/

	table = vector< vector< string> >(nBits + 1);
}

void Tabulation::setPrimeImp() {
	set< string > primeImpTemp;
	createTable();
	/*cout << "\nGetting Prime Implicants.." << endl;*/

	// Combine consecutive terms in the table until its empty
	while (!util.checkEmpty(table)) {
		table = combinePairs(table, primeImpTemp);
	}

	set<string > ::iterator itr;  // convert set to vector
	for (itr = primeImpTemp.begin(); itr != primeImpTemp.end(); ++itr) {
		string x = *itr;
		primeImp.push_back(x);
	}

	/*cout << "\nThe Prime Implicants are:" << endl;
	for (int i = 0; i < primeImp.size(); ++i) {
		cout << i << ") " << util.binToString(primeImp[i]) << endl;
	}*/

}

void Tabulation::minimise() {
	// prepare primeImp chart
	bool primeImpChart[primeImp.size()][nMin] = { {false} };
	// vector< vector<bool> > primeImpChart(primeImp.size(), vector<bool>(nMin, false));

	for (int i = 0; i < primeImp.size(); ++i) {
		for (int j = 0; j < nMin; ++j) {
			primeImpChart[i][j] = util.primeIncludes(primeImp[i], minBin[j]);
		}
	}

	/*cout << "\nPrime implicants chart (rows: prime implicant no., col: minterm no.):" << endl;
	for (int i = 0; i < primeImp.size(); ++i) {
		for (int j = 0; j < nMin; ++j) {
			if (primeImpChart[i][j] == true) {
				cout << "1\t";
			}
			else {
				cout << "0\t";
			}
		}
		cout << endl;
	}*/

	// petric logic
	vector< set<int> > patLogic;
	for (int j = 0; j < nMin; ++j) { // column iteration
		set<int> x;
		for (int i = 0; i < primeImp.size(); ++i) { // row iteration
			if (primeImpChart[i][j] == true) {
				x.insert(i);
			}
		}
		patLogic.push_back(x);
	}
	//cout << "\nPetric logic is (row: minterms no., col: prime implicants no.): " << endl;
	//for (int i = 0; i < patLogic.size(); ++i) {
	//	set<int > ::iterator itr;  // convert set to vector
	//	for (itr = patLogic[i].begin(); itr != patLogic[i].end(); ++itr) {
	//		int x = *itr;
	//		cout << x << " ";
	//	}
	//	cout << endl;
	//}

	// get all possible combinations
	set< set<int> > posComb;
	set<int> prod;
	getPosComb(patLogic, 0, prod, posComb); // recursively multiply set elements
	int min = 9999;

	/*cout << "\nPossible combinations that satisfy all minterms:" << endl;*/
	set< set<int> > ::iterator itr1;
	for (itr1 = posComb.begin(); itr1 != posComb.end(); ++itr1) {
		set<int> comb = *itr1;
		if (comb.size() < min) {
			min = comb.size();
		}
		/*set<int > ::iterator itr;
		for (itr = comb.begin(); itr != comb.end(); ++itr) {
			int x = *itr;
			cout << x << " ";
		}
		cout << endl;*/
	}

	/*cout << "\nGetting the combinations with min terms and min variables ..." << endl;*/
	////Combinations with minimum terms
	vector< set<int> > minComb;
	set< set<int> > ::iterator itr;
	for (itr = posComb.begin(); itr != posComb.end(); ++itr) {
		set<int> comb = *itr;
		if (comb.size() == min) {
			minComb.push_back(comb);
		}
	}

	//Combinations with minimum variables
	min = 9999;
	for (int i = 0; i < minComb.size(); ++i) {
		if (util.getVar(minComb[i], primeImp) < min) {
			min = util.getVar(minComb[i], primeImp);
		}
	}

	for (int i = 0; i < minComb.size(); ++i) {
		if (util.getVar(minComb[i], primeImp) == min) {
			functions.push_back(minComb[i]);
		}
	}
}

string Tabulation::getFunctions() {
	// prints output
	string func = "";
	cout << "\n\nThe possible functions are-\n" << endl;
	for (int i = 0; i < functions.size(); ++i) {
		set<int> function = functions[i];
		set<int> ::iterator itr;
		cout << "Function " << i + 1 << ":" << endl;

		int temp(0);
		for (itr = function.begin(); itr != function.end(); ++itr) {
			int x = *itr;
			temp++;
			if (temp == (function.size()))
				func += (util.binToString(primeImp[x], inputName));
			else
				func += (util.binToString(primeImp[x], inputName) + " + ");
		}
	}
	return func;
}

void Tabulation::displayFunctions() {
	// prints output
	cout << "\n\nThe possible functions are-\n" << endl;
	for (int i = 0; i < functions.size(); ++i) {
		set<int> function = functions[i];
		set<int> ::iterator itr;
		cout << "Function " << i + 1 << ":" << endl;

		for (itr = function.begin(); itr != function.end(); ++itr) {
			int x = *itr;
			cout << util.binToString(primeImp[x], inputName) << " + "; 
		}
		cout << "\b\b  \n" << endl;

	}

}

void Tabulation::getPosComb(vector< set<int> >& patLogic, int level, set<int> prod, set< set<int> >& posComb) {
	// a recursive function to multiple elements of set patLogic and store it in set posComb
	if (level == patLogic.size()) {
		set<int> x = prod;
		posComb.insert(x);
		return;
	}
	else {
		set<int > ::iterator itr;
		for (itr = patLogic[level].begin(); itr != patLogic[level].end(); ++itr) {

			int x = *itr;
			bool inserted = prod.insert(x).second;
			getPosComb(patLogic, level + 1, prod, posComb);
			if (inserted) {
				prod.erase(x);
			}
		}
	}
}

vector< vector< string> > Tabulation::combinePairs(vector< vector< string> > table, set<string>& primeImpTemp) {
	bool checked[table.size()][nMin] = { false };
	// vector< vector<bool> > checked(table.size(), vector<bool>(nMin, false));
	vector< vector< string> > newTable(table.size() - 1);


	for (int i = 0; i < table.size() - 1; ++i) {
		for (int j = 0; j < table[i].size(); ++j) {
			for (int k = 0; k < table[i + 1].size(); k++) {
				if (util.compare(table[i][j], table[i + 1][k])) {
					newTable[i].push_back(util.getDiff(table[i][j], table[i + 1][k]));
					checked[i][j] = true;
					checked[i + 1][k] = true;
				}
			}
		}
	}

	for (int i = 0; i < table.size(); ++i) {
		for (int j = 0; j < table[i].size(); ++j) {
			if (!checked[i][j]) {
				primeImpTemp.insert(table[i][j]);
			}
		}
	}

	return newTable;
}

void Tabulation::createTable() {
	for (int i = 0; i < nMin; ++i) {
		int num1s = util.get1s(minBin[i]);
		table[num1s].push_back(minBin[i]);
	}

	/*cout << "\nTable:" << endl;
	for (int i = 0; i < nBits + 1; ++i) {
		cout << i << ")  ";
		for (int j = 0; j < table[i].size(); ++j) {
			cout << table[i][j] << ", ";
		}
		cout << endl;
	}*/
}