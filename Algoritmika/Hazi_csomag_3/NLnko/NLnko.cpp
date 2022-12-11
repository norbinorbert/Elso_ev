/*Boda Norbert
511-es csoport
Lab3/02
Írjuk ki 𝑛 darab természetes szám legnagyobb közös osztóját!
*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& szamok_szama, vector<unsigned long long>& szamok) {
	cin >> szamok_szama;
	for (int i = 0; i < szamok_szama; i++) {
		unsigned long long temp;
		cin >> temp;
		szamok.push_back(temp);
	}
	return;
}

unsigned long long lnko(unsigned long long szam1, unsigned long long szam2) {
	unsigned long long masolat1 = szam1, masolat2 = szam2;
	
	if (masolat1 == 0) {
		return masolat2;
	}
	if (masolat2 == 0) {
		return masolat1;
	}

	while (masolat1 != masolat2) {
		if (masolat1 > masolat2) {
			if (masolat1 % masolat2 != 0) {
				masolat1 = masolat1 % masolat2;
			}
			else {
				masolat1 = masolat2;
			}
		}

		if (masolat2 > masolat1) {
			if (masolat2 % masolat1 != 0) {
				masolat2 = masolat2 % masolat1;
			}
			else {
				masolat2 = masolat1;
			}
		}	
	}
	
	return masolat1;
}

void kiir(unsigned long long szam) {
	cout << szam;
	return;
}

int main() {
	int szamok_szama;
	vector<unsigned long long> szamok;
	beolvas(szamok_szama, szamok);

	for (int i = 1; i < szamok_szama; i++) {
		//kiszamitja ket egymast koveto szam lnko-jat es beteszi a nagyobb pozicioju helyere
		szamok[i] = lnko(szamok[i - 1], szamok[i]);
	}

	kiir(szamok[szamok_szama - 1]);

	return 0;
}