#include <iostream>
#include "lista.h"

using namespace std;

int main() {
	Lista a(1);
	a.beszuras_elejere("Janos", 1.12);
	a.beszuras_vegere("Marton", 5);
	a.beszuras_elejere("David", 6.69);
	a.beszuras_vegere("Kriszti", 9);
	a.beszuras_rendezett("Dddd", 10);
	
	Elem* tmp = new Elem("Daniel", 8);
	a.beszuras_vegere(tmp);

	a.kiir();
	cout << endl;
	a.rendezes(2);
	a.kiir();
	cout << endl;
	a.rendezes(1);
	a.kiir();
	return 0;
}