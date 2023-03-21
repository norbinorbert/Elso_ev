//Boda Norbert, 511

#include <iostream>
#include <ctime>
#include <cmath>

#define pi 3.14159265359

using namespace std;

class pont {
	double x, y;
public:
	pont();
	pont(double, double);
	pont(const pont&);
	void kiir()const;
	double GetX()const;
	double GetY()const;
};

pont::pont() {
	x = 0;
	y = 0;
}

pont::pont(double x, double y) {
	this->x = x;
	this->y = y;
}

pont::pont(const pont& P) {
	x = P.x;
	y = P.y;
}

void pont::kiir() const{
	cout << x << " " << y << endl;
}

double pont::GetX()const {
	return x;
}

double pont::GetY()const {
	return y;
}

class Kor {
	pont kp;
	double sugar;
public:
	Kor();
	Kor(double, double, double);
	Kor(const pont&, double);
	void kiir() const;
	double kerulet() const;
	double terulet() const;
	pont random_pont() const;
};

Kor::Kor():kp() {
	sugar = 1;
}

Kor::Kor(double x, double y, double s):kp(x, y) {
	sugar = s;
}

Kor::Kor(const pont& p, double s):kp(p) {
	sugar = s;
}

void Kor::kiir() const{
	cout << kp.GetX() << " " << kp.GetY() << " " << sugar << endl;
}

double Kor::kerulet() const{
	return 2 * pi * sugar;
}

double Kor::terulet() const{
	return pi * sugar * sugar;
}

pont Kor::random_pont() const{
	double phi = ((double)rand() / (double)RAND_MAX) * 2 * pi;
	double x = cos(phi) * sugar + kp.GetX();
	double y = sin(phi) * sugar + kp.GetY();
	return pont(x, y);
}

int main() {
	srand(time(NULL));
	Kor A;
	pont P;
	cout << A.kerulet() << " " << A.terulet() << endl;
	P = A.random_pont();
	P.kiir();

	P = A.random_pont();
	P.kiir();

	P = A.random_pont();
	P.kiir();

	P = A.random_pont();
	P.kiir();

	return 0;
}