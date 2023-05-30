#include <iostream>
#include "elem.h"
#include <string>

using namespace std;

Elem::Elem() {
	nev = "";
	atlag = 0;
	kovetkezo = NULL;
}

Elem::Elem(string n, double a) {
	nev = n;
	atlag = a;
	kovetkezo = NULL;
}

void Elem::kiir() {
	cout << "Adat: " << nev << "\tErtek: " << atlag << endl;
}