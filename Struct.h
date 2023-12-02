#include <iostream>

using namespace std;

class Calc {
private:
	int field1;
	int field2;
public:
	int GetField1();
	void SetField1(int value);

	int GetField2();
	void SetField2(int value);

	operator std::string() const;

	Calc();
};
