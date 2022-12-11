/*Boda Norbert
511-es csoport
Lab3/08
Bontsunk törzstényezőkre egy adott természetes számot!*/

#include <iostream>
#include <cmath>

using namespace std;

void beolvas(unsigned int& szam) {
	cin >> szam;
	return;
}

void kiir_torzstenyezore_bontas(unsigned int& szam) {
	//a 0-as es 1-es szam eseten nem letezik prim oszto amit ki lehetne iratni
	if (szam == 0 || szam == 1) {
		return;
	}

	unsigned int masolat = szam, oszto = 2;
	bool kiir = false, legkisebb_oszto = true;
	double limit = szam / 2;

	//primszamok eseten csak a szam gyokeig fog elmenni az oszto, mert azon tul biztos nem letezik oszto
	if ((masolat - 1) % 6 == 0 || (masolat + 1) % 6 == 0) {
		limit = sqrt(szam);
		legkisebb_oszto = false;
	}

	while (masolat > 1 && oszto<=limit) {
		if (masolat % oszto == 0) {

			//ha a szam nem prim, vagyis letezik egy osztoja ami kisebb a gyokenel, akkor a legnagyobb osztoig fog elmenni a ciklus
			if (!legkisebb_oszto) {
				legkisebb_oszto = true;
				limit = masolat / oszto + 2;
			}

			short szamlalo = 0;
			while (masolat % oszto == 0) {
				masolat /= oszto;
				szamlalo++;
			}
			if (szamlalo > 1 && masolat != 1) {
				kiir = true;
				cout << oszto << "^" << szamlalo << "*";
			}
			if (szamlalo == 1 && masolat != 1) {
				kiir = true;
				cout << oszto << "*";
			}
			if (szamlalo > 1 && masolat == 1) {
				kiir = true;
				cout << oszto << "^" << szamlalo;
			}
			if (szamlalo == 1 && masolat == 1) {
				kiir = true;
				cout << oszto;
			}
		}

		//2-es utan nincs miert nezni a paros szamokat
		if (oszto == 2) {
			oszto++;
		}
		else {
			oszto += 2;
		}
	}

	//primszam kiirasa
	if (!kiir) {
		cout << szam;
	}
	return;
}

int main() {
	unsigned int szam;
	beolvas(szam);

	kiir_torzstenyezore_bontas(szam);
	return 0;
}