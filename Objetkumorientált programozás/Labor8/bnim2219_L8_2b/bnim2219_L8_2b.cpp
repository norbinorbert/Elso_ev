//Boda Norbert, 511

#include <iostream>

using namespace std;

class komp {
protected:
	int re, im;
public:
	komp(int, int);
	virtual komp operator *(const komp&);
	komp operator *=(const komp&);
	void kiir() const;
	int get_real() const;
	int get_im() const;
};

komp::komp(int re = 1, int im = 0) {
	this->re = re;
	this->im = im;
}

komp komp::operator*(const komp& a) {
	return komp(re * a.re - im * a.im, re * a.im + im * a.re);
}

komp komp::operator*=(const komp& a) {
	*this = *this * a;
	return *this;
}

void komp::kiir() const{
	cout << re << "+" << im << "i" << endl;
}

int komp::get_real() const {
	return re;
}

int komp::get_im() const {
	return im;
}

class kompkiir : public komp {
public:
	kompkiir(int, int);
	komp operator*(const komp&);
};

kompkiir::kompkiir(int re, int im) :komp(re, im) {};

komp kompkiir::operator*(const komp& a) {
	cout << "(" << re << "+" << im << "i)";
	cout << " * ";
	cout << "(" << a.get_real() << "+" << a.get_im() << "i) = ";

	komp b(re * a.get_real() - im * a.get_im(), re * a.get_im() + im * a.get_real());
	b.kiir();
	return b;
}

void main() {

	komp p(1, 2), q(3, 3), r;

	r = p *= q;

	p.kiir();

	r.kiir();

	kompkiir p1(1, 2), q1(3, 3);

	komp r1, r2;

	r1 = p1 * q1;

	r2 = p1 *= q1;

	p1.kiir();

	r1.kiir();

	r2.kiir();

}