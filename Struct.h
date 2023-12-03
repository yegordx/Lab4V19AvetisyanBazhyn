#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string> 

using namespace std;

class Calc {
private:
	const int m=2;
	int fields[2];
	string field;
	mutable shared_mutex myMutex;
public:
	int GetField(int i) const;
	void SetField(int i, int value);
	operator string() const;

	Calc();
};
