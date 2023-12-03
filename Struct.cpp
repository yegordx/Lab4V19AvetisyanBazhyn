#include "Struct.h"

int Calc :: GetField(int i) const{
	if (i >= m||i<0) {
		return-1;
	}
	shared_lock<shared_mutex> lk(myMutex);
	return fields[i];
}

void Calc :: SetField(int i, int value) {
	lock_guard<shared_mutex> lk(myMutex);
	fields[i] = value;
}

Calc::Calc() {
	for (int i = 0; i < m; i++) {
		fields[i] = 0;
	}
}

Calc:: operator string() const {
	shared_lock<shared_mutex> lk(myMutex);
	string result = "field1: " + to_string(fields[0]) + "\t field2: " + to_string(fields[1]) + "\n";
	return result;
}