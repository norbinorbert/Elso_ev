//Boda Norbert, 511

#include <iostream>
#include <cmath>

using namespace std;

#define pi 3.14159265359

class Alakzat {
public:
	virtual double terulet() = 0;
	virtual double kerulet() = 0;
	virtual void nagyit(double s) = 0;
};

class Haromszog :public Alakzat {
	double old1, old2, old3;
public:
	Haromszog() {
		old1 = old2 = old3 = 1;
	}
	Haromszog(double a, double b, double c) {
		old1 = a;
		old2 = b;
		old3 = c;
	}
	double terulet() {
		double p = kerulet() / 2;
		return sqrt(p * (p - old1) * (p - old2) * (p - old3));
	}
	double kerulet() {
		return old1 + old2 + old3;
	}
	void nagyit(double s) {
		old1 *= s;
		old2 *= s;
		old3 *= s;
	}
};

class Kor :public Alakzat {
	double sugar;
public:
	Kor(double s) {
		sugar = s;
	}
	double terulet() {
		return pi * sugar * sugar;
	}
	double kerulet() {
		return 2 * pi * sugar;
	}
	void nagyit(double s) {
		sugar *= s;
	}
};

class DerekszoguHaromszog :public Haromszog {
	double be1, be2, at;
public:
	DerekszoguHaromszog(double old1, double old2, double old3):Haromszog(old1, old2, old3) {
		double t1 = old1 * old1;
		double t2 = old2 * old2;
		double t3 = old3 * old3;
		if (t3 >= t1 && t3 >= t2) {
			if (t3 != t1 + t2) {
				throw "Nem derekszogu a haromszog";
			}
			be1 = old1;
			be2 = old2;
			at = old3;
		}
		if (t2 >= t1 && t2 >= t3) {
			if (t2 != t1 + t3) {
				throw "Nem derekszogu a haromszog";
			}
			be1 = old1;
			be2 = old3;
			at = old2;
		}
		if (t1 >= t2 && t1 >= t3) {
			if (t1 != t2 + t3) {
				throw "Nem derekszogu a haromszog";
			}
			be1 = old2;
			be2 = old3;
			at = old1;
		}
	}
};

int main() {
	try {
		Alakzat* a[] = { new Kor(3), new Haromszog, new DerekszoguHaromszog(3,4,5) };

		cout << a[0]->kerulet() << ", " << a[0]->terulet() << endl;

		cout << a[1]->kerulet() << ", " << a[1]->terulet() << endl;

		cout << a[2]->kerulet() << ", " << a[2]->terulet() << endl;


		DerekszoguHaromszog asd(2, 3, 4);
	}
	catch (const char* s) {
		cout << s << endl;
	}
	return 0;
}