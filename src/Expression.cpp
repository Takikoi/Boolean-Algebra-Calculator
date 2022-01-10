#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <regex>
#include <math.h>
#include "TruthTableBool.h"
#include "Expression.h"

using namespace std;

Expression::Expression() : expression(""), input(""), TB(input.length()) {
	output = new bool[(int)pow(2, input.length())];
	processTruthTable();
}

Expression::Expression(const string& str) : expression(str), input(this->processInp()), TB(input.length()) {
	output = new bool [(int)pow(2, input.length())];
	processTruthTable();
	processSOP();
}

// Operators
Expression& Expression::operator=(const Expression& express) {
	this->~Expression();
	new(this) Expression(express.getExp());
	return *this;
}

//go through the expression, copy all uppercase letters, and sort alphabetically
string Expression::processInp() { // failed here
	string tempinput = ""; //tempinput = input;
	int count = 0;
	string temp = expression;
	for (int i = 0; i < temp.length(); ++i) {
		if ((int)temp[i] > 64 && (int)temp[i] < 91) {
			tempinput.push_back(temp[i]);
		}
	}
	sort(tempinput.begin(), tempinput.end());
	set<char> chars;

	tempinput.erase(
		remove_if(
			tempinput.begin(),
			tempinput.end(),
			[&chars](char i) {
				// If encountered character, remove this one.
				if (chars.count(i)) { return true; }

				// Otherwise, mark this character encountered and don't remove.
				chars.insert(i);
				return false;
			}
		),
		tempinput.end()
				);
	return tempinput;
}

Expression::~Expression() {
	// delete[] output;
	// output = NULL;
}

string Expression::getExp() const {
	return expression;
}

string Expression::getInp() const {
	return input;
}

//process from a string with all inputs substituted as 1s and 0s
//Example: (1*0')+0 will retrun 1
bool Expression::process(const string& str) {
	string c(str);
	bool par;

	//process () operator
	int numBrack = 1;
	while (numBrack != 0) {
		regex rgx("\\((\?:(\?!\\().)*\?\\)");
		smatch match;
		const string tempo = c;
		if (regex_search(tempo.begin(), tempo.end(), match, rgx)) {
			string m = match[0];
			m.erase(0, 1);
			m.pop_back();
			par = process(m);
			c.replace(c.find(match[0]), match[0].length(), par?"1":"0");
		}
		numBrack = 0;
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '(') {
				numBrack += 1;
			}
		}
	}

	//process ' operator
	int numInv(1);
	while (numInv != 0) {
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '\'') {
				if (c[i - 1] == '0') {
					c[i - 1] = '1';
				}
				else {
					c[i - 1] = '0';
				}
				c.erase(c.begin() + i);
			}
		}
		numInv = 0;
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '\'') {
				numInv += 1;
			}
		}
	}

	//process * operator
	int numStar = 1;
	while (numStar != 0) {
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '*') {
				c[i - 1] = ((bool)(c[i - 1] - '0') && (bool)(c[i + 1] - '0')) ? '1' : '0';
				c.erase(i, 2);
			}
		}
		numStar = 0;
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '*') {
				numStar += 1;
			}
		}
	}

	//process + operator
	int numPlus = 1;
	while (numPlus != 0) {
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '+') {
				c[i - 1] = ((bool)(c[i - 1] - '0') || (bool)(c[i + 1] - '0')) ? '1' : '0';
				c.erase(i, 2);
			}
		}
		numPlus = 0;
		for (int i = 0; i < c.length(); ++i) {
			if (c[i] == '+') {
				numPlus += 1;
			}
		}
	}

	//remove white spaces
	for (int i = 0; i < c.length(); ++i) {
		if (c[i] == ' ') {
			c.erase(i);
		}
	}

	//return the result. Example: (1*0')+0 will retrun 1
	return (c[0] == '1') ? true : false;
}

//A nested for loop with the number of loops dynamically created based on the number of inputs
//Will go through every input in a nested manner and set each one 0 or 1, put them in the truthtable accordingly, and substitute the
// ABCs with its value 0 or 1, then pass that string to process()
void Expression::processTruthTable() {
	string exp = expression;
	string inp = input;
	const int n = inp.length();
	int* i = new int[n + 1];
	for (int a = 0; a < n + 1; a++) {
		i[a] = 0;
	}
	int MAX = 2;

	int count = 0;
	int p = 0;
	while (i[n] == 0) {
		//do stuff here
		string temp(exp);
		for (int l = 0; l < temp.length(); ++l) {
			for (int j = 0; j < n; ++j) {
				if (temp[l] == inp[j]) {
					temp[l] = '0' + i[n - j - 1];
				}
			}
		}
		for (int j = n - 1; j >= 0; --j) {
			TB(count / ((int)input.length() + 1), count % ((int)input.length() + 1)) = i[j];
			count++;
		}
		TB(count / ((int)input.length() + 1), count % ((int)input.length() + 1)) = process(temp);
		output[count / ((int)input.length() + 1)] = TB(count / ((int)input.length() + 1), count % ((int)input.length() + 1));
		count++;

		//end do stuff
		i[0]++;
		while (i[p] == MAX) {
			i[p] = 0;
			i[++p]++;
			if (i[p] != MAX)
				p = 0;
		}
	}
	delete[] i;
	i = NULL;
}

TruthTableBool Expression::getTB() const {
	return TB;
}

void Expression::printTB() const {
	TB.print();
}

//go through the truthtable and get all the SOPs in human language, store in a string
void Expression::processSOP() {
	string exp = expression;
	string inp = input;
	const int n = inp.length();
	int* i = new int[n + 1];
	for (int a = 0; a < n + 1; a++) {
		i[a] = 0;
	}
	int MAX = 2;

	int count = 0;
	int p = 0;
	while (i[n] == 0) {
		//do stuff here
		if (output[count]) {
			for (int j = 0; j < n; ++j) {
				if (i[n-j-1] == 1) {
					SOP.push_back(input[j]);
				}
				else {
					SOP.push_back(input[j]);
					SOP.push_back('\'');
				}
			}
			if (count < (int)pow(2, input.length())-1) {
				SOP.push_back('+');
			}
		}
		count++;

		//end do stuff
		i[0]++;
		while (i[p] == MAX) {
			i[p] = 0;
			i[++p]++;
			if (i[p] != MAX)
				p = 0;
		}
	}
	delete[] i;
	i = NULL;
}

string Expression::getSOP() const {
	return SOP;
}
void Expression::printSOP() const {
	cout << SOP << endl;
}

void Expression::printOutput() const {
	for (int i = 0; i < (int)pow(2, input.length()); ++i) {
		cout << output[i];
	}
	cout << endl;
}

bool* Expression::getOutput() {
	return output;
}