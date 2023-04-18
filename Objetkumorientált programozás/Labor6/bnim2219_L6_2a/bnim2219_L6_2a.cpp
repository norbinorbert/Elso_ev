//Boda Norbert, 511

#include <iostream>

using namespace std;

class Matr2 {
	double a11, a12, a21, a22;
public:
	Matr2();
	Matr2(double, double, double, double);
	Matr2 operator+(const Matr2&);
	Matr2 operator+=(const Matr2&);
	Matr2 operator*(const Matr2&);
	Matr2 operator*=(const Matr2&);
	double operator~();
	void kiir();
};

Matr2::Matr2() {
	a11 = 1;
	a12 = 0;
	a21 = 0;
	a22 = 1;
}

Matr2::Matr2(double a, double b, double c, double d) {
	a11 = a;
	a12 = b;
	a21 = c;
	a22 = d;
}

Matr2 Matr2::operator+(const Matr2& A) {
	Matr2 tmp;
	tmp.a11 = a11 + A.a11;
	tmp.a12 = a12 + A.a12;
	tmp.a21 = a21 + A.a21;
	tmp.a22 = a22 + A.a22;
	return tmp;
}

Matr2 Matr2::operator+=(const Matr2& A) {
	*this = *this + A;
	return *this;
}

Matr2 Matr2::operator*(const Matr2& A) {
	Matr2 tmp;
	tmp.a11 = a11 * A.a11 + a12 * A.a21;
	tmp.a12 = a11 * A.a12 + a12 * A.a22;
	tmp.a21 = a21 * A.a11 + a22 * A.a21;
	tmp.a22 = a21 * A.a12 + a22 * A.a22;
	return tmp;
}

Matr2 Matr2::operator*=(const Matr2& A) {
	*this = *this * A;
	return *this;
}

double Matr2::operator~() {
	return (a11 * a22) - (a12 * a21);
}

void Matr2::kiir() {
	cout << a11 << " " << a12 << endl << a21 << " " << a22 << endl;
}

int main() {
	Matr2 a(1, 1, 1, 1);
	Matr2 b;
	cout << "b deteminansa: " << ~b << endl;
	Matr2 c;
	c = a + b;
	cout << "c:" << endl;
	c.kiir();
	c += a;
	cout << "c:" << endl;
	c.kiir();
	Matr2 d;
	d = c * b;
	cout << "d: " << endl;
	d.kiir();
	d *= b;
	cout << "d:" << endl;
	d.kiir();

	return 0;
}