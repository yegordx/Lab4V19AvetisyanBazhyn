#include "Struct.h"
#include <mutex>
#include <iostream>

int Calc :: GetField1() {
	return field1;
}

void Calc :: SetField1(int value) {
	field1 = value;
}
int Calc :: GetField2() {
	return field2;
}
void Calc :: SetField2(int value) {
	field2 = value;
}
Calc::Calc() {
	field1 = 0;
	field2 = 0;
}