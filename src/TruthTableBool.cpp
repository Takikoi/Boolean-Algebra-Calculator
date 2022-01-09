#include <iostream>
#include <cassert>
#include <cstdlib>
#include <math.h>
#include "TruthTableBool.h"

using namespace std;

//this is a boolean matrix, with the size (2^n) rows by (n+1) collums with n is the number of inputs

void TruthTableBool::allocate() {
	entry = new bool* [(int)pow(2,size)];
	for (int i = 0; i < (int)pow(2,size); ++i) {
		entry[i] = new bool[size+1];
	}
}

void TruthTableBool::deallocate() {
	for (int i = 0; i < (int)pow(2, size); ++i) {
		delete[] entry[i];
		entry[i] = NULL;
	}
	delete[] entry;
	entry = NULL;
}

TruthTableBool::TruthTableBool() : size(0) {
	allocate();
	zeros();
}

TruthTableBool::TruthTableBool(const int& _size) : size(_size) {
	allocate();
	zeros();
}

TruthTableBool::~TruthTableBool() {
	// deallocate();
}

void TruthTableBool::zeros() const {
	for (int i = 0; i < (int)pow(2, size); ++i) {
		for (int j = 0; j < size + 1; ++j) {
			entry[i][j] = false;
		}
	}
}

void TruthTableBool::print() const {
	for (int i = 0; i < (int)pow(2, size); ++i) {
		for (int j = 0; j < size + 1; ++j) {
			cout << entry[i][j] << "      ";
		}
		cout << endl;
	}
}

bool TruthTableBool::operator() (const int& i, const int& j) const {
	assert(i > -1 && i < (int)pow(2,size));
	assert(j > -1 && j < size+1);
	return entry[i][j];
}

bool& TruthTableBool::operator() (const int& i, const int& j) {
	assert(i > -1 && i < (int)pow(2, size));
	assert(j > -1 && j < size + 1);
	return entry[i][j];
}

bool** TruthTableBool::getBool() const{
	return entry;
}