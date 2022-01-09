#ifndef TRUTH_TABLE_BOOL
#define TRUTH_TABLE_BOOl

class TruthTableBool {
private:
	int size;
	bool** entry;
	//kich thuoc 2^n x (n+1)

	void allocate();
	void deallocate();
public:
	TruthTableBool();
	TruthTableBool(const int& _size);
	~TruthTableBool();

	void zeros() const;
	void print() const;
	bool** getBool() const;

	//operator
	bool operator() (const int& i, const int& j) const;
	bool& operator() (const int& i, const int& j);
};

#endif