#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <algorithm>
#include <cmath>

#include "Tabulation.h"
#include "Util.h"

using namespace std;


int main() {

	//test
	int size=10;
	bool* input = new bool(size);
	cout << "size " << endl;
	for (int i = 0; i < size; ++i)
	{
		cin >> input[i];
	}
	//

	Tabulation tab;
	tab.initialise(input,size);
	tab.setPrimeImp();
	tab.minimise();
	tab.displayFunctions();
	return 0;
}