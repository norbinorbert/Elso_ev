#ifndef ELEM_H
#define ELEM_H

#include <string>

using namespace std;

class Elem {
public:
	string nev;
	double atlag;
	Elem* kovetkezo;

	Elem();
	Elem(string, double);
	void kiir();
};

#endif // !ELEM_H
