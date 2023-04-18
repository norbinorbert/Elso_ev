//Boda Norbert, 511

#include <iostream>

using namespace std;

class Intervallum {
	int kezdopont, vegpont;
public:
	Intervallum(int, int);
	void kiir();
	Intervallum& operator--();	//prefix
	Intervallum operator--(int);	//postfix
};


Intervallum::Intervallum(int a, int b) {
	if (a > b) {
		throw "Hiba";
	}
	else {
		kezdopont = a;
		vegpont = b;
	}
}
void Intervallum::kiir() {
	cout << "[" << kezdopont << "," << vegpont << "]" << endl;
}

Intervallum& Intervallum::operator--() {
	kezdopont++;
	vegpont--;
	return *this;
}

Intervallum Intervallum::operator--(int) {
	Intervallum tmp(kezdopont, vegpont);
	kezdopont++;
	vegpont--;
	return tmp;
}

int main() {
	try {
		Intervallum a(3, 2);
		cout << "a: " << endl;
		a.kiir();
	}
	catch (const char* s) {
		cout << s << endl;
	}
	Intervallum b(1, 8);
	cout << "b--:" << endl;
	(b--).kiir();
	cout << "b:" << endl;
	b.kiir();
	cout << "--b:" << endl;
	(--b).kiir();
	return 0;
}