/*Boda Norbert
511-es csoport
Lab7/01
Legyen a következő játék: az egyik játékos (Játékos1) gondol egy 1 és 1000
közötti természetes számra. A másik játékosnak (Játékos2) ki kell találnia ezt
a számot minél kevesebb próbálgatással. A titkos szám „birtokosa” (Játékos1)
egy-egy találgatásra csak annyit válaszol, hogy a titkos szám kisebb vagy nagyobb
mint a másik játékos (Játékos2) által feltételezett szám.
Írjunk programot amely a fenti játékot szimulálja, úgy, hogy a programunk a
Játékos2, azaz ő találja ki a felhasználó titkos számát.*/

#include <iostream>

using namespace std;

void szamkitalalos(short also_korlat, short felso_korlat) {
	short tipp = (also_korlat + felso_korlat) / 2;
	cout << tipp << endl;
	short valasz;
	cin >> valasz;
	if (valasz == 0) {
		return;
	}
	else {
		if (valasz == 1) {
			also_korlat = tipp + 1;
		}
		else {
			felso_korlat = tipp;
		}
		return szamkitalalos(also_korlat, felso_korlat);
	}
}

int main() {
	short also_korlat = 0, felso_korlat = 1000;
	szamkitalalos(also_korlat, felso_korlat);
	return 0;
}