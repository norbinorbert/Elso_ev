/*Boda Norbert
511-es csoport
Lab3/04
Írjunk algoritmust, amely egy adott 𝑥 páros számot felír két különböző
prímszám összegeként (Goldbach-sejtés).*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void beolvas(unsigned int& szam) {
	cin >> szam;
	return;
}

//megnezi ha egy szam prim
bool prim(unsigned int szam) {
	for (int i = 2; i <= sqrt(szam); i++) {
		if (szam % i == 0) {
			return false;
		}
	}
	return true;
}

//keresi a ket primszamot amelyek osszege egyenlo a szammal
void keres(unsigned int& szam, unsigned int& elso, unsigned int& masodik) {
	unsigned int i=3;
	while(i<szam) {
		if (prim(i)) {
			if (prim(szam - i)) {
				elso = i;
				masodik = szam - i;
				return;
			}
		}
		i = i + 2;
	}
	return;
}

void kiir(unsigned int& szam, unsigned int& elso, unsigned int& masodik) {
	cout << szam << " = " << elso << " + " << masodik;
	return;
}

int main() {
	unsigned int szam;
	beolvas(szam);

	unsigned int elso_prim = 0, masodik_prim = 0;
	keres(szam, elso_prim, masodik_prim);

	kiir(szam, elso_prim, masodik_prim);

	return 0;
}