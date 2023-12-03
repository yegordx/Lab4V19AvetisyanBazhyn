#include <iostream>
#include <mutex>

using namespace std;

class Calc {
private:
	int field1;
	int field2;
	mutable shared_mutex myMutex;
public:
	int GetField1() const;
	void SetField1(const int& value);

	int GetField2() const;
	void SetField2(const int& value);

	operator std::string() const;

	Calc();
};
