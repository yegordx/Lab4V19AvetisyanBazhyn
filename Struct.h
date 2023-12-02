#include <iostream>
#include <mutex>

using namespace std;

class Calc {
private:
	int field1;
	int field2;
	mutable shared_mutex myMutex;
public:
	int GetField1();
	void SetField1(int value);

	int GetField2();
	void SetField2(int value);

	operator std::string() const;

	Calc();
};
