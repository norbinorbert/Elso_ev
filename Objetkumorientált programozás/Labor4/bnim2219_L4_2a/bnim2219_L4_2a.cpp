//Boda Norbert, 511

#include <iostream>

using namespace std;

class Vektor {
	double* elemek;
	int dim;
public:
	Vektor(int, double*);
	~Vektor() { delete[]elemek; }
	Vektor osszead(const Vektor&);
	Vektor kivon(const Vektor&);
	double skalarSzorzat(const Vektor&);
	double lekerdez(int);
	void beallit(int, double);
	class Kulonbozo {};
	class HibasIndex {};
};

Vektor::Vektor(int meret, double* elemek) {
	this->elemek = new double[meret];
	for (int i = 0; i < meret; i++) {
		this->elemek[i] = elemek[i];
	}
	dim = meret;
}

Vektor Vektor::osszead(const Vektor& A) {
	if (dim != A.dim) {
		throw Kulonbozo{};
	}
	double* x = new double[dim];
	for (int i = 0; i < dim; i++) {
		x[i] = elemek[i] + A.elemek[i];
	}
	Vektor B(dim, x);
	delete[]x;
	return B;
}

Vektor Vektor::kivon(const Vektor& A) {
	if (dim != A.dim) {
		throw Kulonbozo{};
	}
	double* x = new double[dim];
	for (int i = 0; i < dim; i++) {
		x[i] = elemek[i] - A.elemek[i];
	}
	Vektor B(dim, x);
	delete[]x;
	return B;
}

double Vektor::skalarSzorzat(const Vektor& A) {
	if (dim != A.dim) {
		throw Kulonbozo{};
	}
	double x = 0;
	for (int i = 0; i < dim; i++) {
		x += elemek[i] * A.elemek[i];
	}
	return x;
}

double Vektor::lekerdez(int index) {
	if (index < 0 || index >= dim) {
		throw HibasIndex{};
	}
	return elemek[index];
}

void Vektor::beallit(int index, double ertek) {
	if (index < 0 || index >= dim) {
		throw HibasIndex{};
	}
	elemek[index] = ertek;
}

int main() {
	double x[] = {3, 2, 5};
	double y[] = {4, 1, 4};
	double z[] = { 1 , 3 };
	Vektor A(3, x);
	Vektor B(3, y);
	Vektor Z(2, z);

	try {
		cout << "A + B\n";
		Vektor C = A.osszead(B);
		cout << "A - Z\n";
		Vektor D = A.kivon(Z);
		cout << "A * B\n";
		double E = A.skalarSzorzat(B);
	}
	catch (Vektor::Kulonbozo) {
		cerr << "Kulonbozo meret" << endl;
	}
	try {
		cout << A.lekerdez(2) << endl;
		cout << Z.lekerdez(-1) << endl;
	}
	catch (Vektor::HibasIndex) {
		cerr << "Hibas index" << endl;
	}

	return 0;
}