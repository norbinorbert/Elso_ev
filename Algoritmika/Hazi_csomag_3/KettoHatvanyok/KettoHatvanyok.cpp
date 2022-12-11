/*Boda Norbert
511-es csoport
Lab3/07
Bontsunk fel egy adott számot 2 hatványainak összegére!*/

#include <iostream>
#include <climits>

using namespace std;

void beolvas(unsigned long long& szam) {
	cin >> szam;
	return;
}

void kiir_hatvanyok_osszege(unsigned long long szam, unsigned long long ketto_hatvany, short hatvany) {
	//ha a szam kettes hatvany akkor kiirja a kettes hatvanyt
	if (szam == ketto_hatvany) {
		cout << 2 << "^" << hatvany;
		return;
	}

	//ha a szam nagyobb, mint a jelenlegi kettes hatvany akkor kiirja a kettes hatvanyt, kivonja a szambol azt, 
	//osztja a kettes hatvanyt 2-vel, illetve a hatvanyt csokkenti 1-el
	if (szam > ketto_hatvany) {
		cout << 2 << "^" << hatvany << "+";
		return kiir_hatvanyok_osszege(szam - ketto_hatvany, ketto_hatvany / 2, hatvany - 1);
	}

	//ha a szam kisebb, mint a jelenlegi kettes hatvany akkor
	//osztja a kettes hatvanyt 2-vel, illetve a hatvanyt csokkenti 1-el
	if (szam < ketto_hatvany) {
		return kiir_hatvanyok_osszege(szam, ketto_hatvany / 2, hatvany - 1);
	}
}

int main() {
	unsigned long long szam, ketto_hatvany = LLONG_MAX+1; //2^63
	short hatvany = 63;

	beolvas(szam);

	kiir_hatvanyok_osszege(szam, ketto_hatvany, hatvany);
	return 0;
}