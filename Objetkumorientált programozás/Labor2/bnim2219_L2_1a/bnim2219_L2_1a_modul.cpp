//Boda Norbert, 511-es csoport

#include <iostream>

static double* intervallum;

void init(double a, double b){
	if (a > b) {
		std::swap(a, b);
	}
	intervallum = new double[2];
	intervallum[0] = a;
	intervallum[1] = b;
}

void felsz() {
	delete[]intervallum;
}

void duplaz() {
	double c = (intervallum[0] + intervallum[1]) / 2;
	intervallum[0] = intervallum[0] - (c - intervallum[0]);
	intervallum[1] = (intervallum[1] - c) + intervallum[1];
}

void kiir() {
	std::cout << intervallum[0] << " " << intervallum[1] << std::endl;
}