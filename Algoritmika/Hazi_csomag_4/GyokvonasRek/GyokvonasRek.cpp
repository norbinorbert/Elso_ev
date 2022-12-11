/*Boda Norbert
511-es csoport
Lab4/10
Írjunk rekurzív algoritmust, amely meghatározza egy adott 𝑎 szám négyzetgyökét, felhasználva a következő sorozatot, melyről tudjuk,
hogy √𝑎-hoz konvergál.*/

#include <iostream>
#include <iomanip>

using namespace std;

void beolvas(unsigned long long& szam) {
	cin >> szam;
}

double gyokvonas(unsigned long long szam, double elozo, int epszilon) {
	if (szam == 0) {
		return 0;
	}
	double mostani = (elozo + (szam / elozo)) / 2;
	if (elozo - mostani <= epszilon) {
		return mostani;
	}
	return gyokvonas(szam, mostani, epszilon);
}

void kiir(double& gyok) {
	cout << fixed << setprecision(6) << gyok;
}

int main() {
	unsigned long long szam;
	beolvas(szam);
	double f1 = 0, epszilon = 0.000001;
	if (szam % 2 == 0) {
		f1 = szam / 2 + 0.5;
	}
	else {
		f1 = szam / 2 + 1;
	}
	double gyok = gyokvonas(szam, f1, epszilon);

	kiir(gyok);
	return 0;
}