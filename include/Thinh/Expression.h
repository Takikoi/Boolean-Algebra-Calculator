#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

using namespace std;

class Expression {
private:
	//properties
	string expression;
	string input;
	TruthTableBool TB;
	bool* output; // bool string 
	string SOP;

	string processInp();
	bool process(const string& str);
	void processTruthTable();
	void processSOP();

public:
	Expression();
	Expression(const string& str);
	~Expression();

	string getExp() const;
	string getInp() const;
	TruthTableBool getTB() const;
	void printTB() const;
	string getSOP() const;
	void printSOP() const;
	void printOutput() const;
	bool* getOutput();

	Expression& operator=(const Expression& express);
};
#endif
