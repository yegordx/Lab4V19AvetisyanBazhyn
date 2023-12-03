#include "Struct.h"

int Calc :: GetField1() const {
	return field1;
}

void Calc :: SetField1(const int& value) {
	field1 = value;
}
int Calc :: GetField2() const {
	return field2;
}
void Calc :: SetField2(const int& value) {
	field2 = value;
}
Calc::Calc() {
	field1 = 0;
	field2 = 0;
}