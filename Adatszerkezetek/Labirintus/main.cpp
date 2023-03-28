#include <iostream>
#include "Labirintus.h"

using namespace std;

int main() {
	Labirintus* A = LetrehozFilebol("labirintus.in");

	Pozicionalas(A, 5, 5);

	Kiir(A);

	while (true) {
		Lepes(A);
		system("CLS");
		Kiir(A);
	}

	return 0;
}