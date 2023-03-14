//Boda Norbert, 511-es csoport
#include <iostream>

class interv {
	double* intervallum;
public:
	interv(double, double);
	~interv() { delete[]intervallum; }
	void duplaz();
	void kiir();
};

interv::interv(double a, double b) {
	if (a > b) {
		std::swap(a, b);
	}
	intervallum = new double[2];
	intervallum[0] = a;
	intervallum[1] = b;
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
	interv i(1, 3);
	i.kiir();
	i.duplaz();
	i.kiir();
	return 0;
}