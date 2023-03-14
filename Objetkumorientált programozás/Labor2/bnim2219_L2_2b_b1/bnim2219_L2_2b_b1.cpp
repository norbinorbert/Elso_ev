//Boda Norbert, 511-es csoport
#include <iostream>

namespace interv {
	double* intervallum;
	void init(double, double);
	void felsz();
	void duplaz();
	void kiir();
}

void interv::init(double a, double b) {
	if (a > b) {
		std::swap(a, b);
	}
	intervallum = new double[2];
	intervallum[0] = a;
	intervallum[1] = b;
}

void interv::felsz() {
	delete[]intervallum;
}

void interv::duplaz() {
	double c = (intervallum[0] + intervallum[1]) / 2;
	intervallum[0] = intervallum[0] - (c - intervallum[0]);
	intervallum[1] = (intervallum[1] - c) + intervallum[1];
}

void interv::kiir() {
	std::cout << intervallum[0] << " " << intervallum[1] << std::endl;
}

int main() {
	using namespace interv;
	init(1, 3);
	kiir();
	duplaz();
	kiir();
	felsz();
	return 0;
}