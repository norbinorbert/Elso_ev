/*Boda Norbert
511-es csoport
Lab6/10
Az állami kincstárba 𝑛 zsákban hozzák a pénzérméket. A raktár főnöke
ismeri minden zsák tartalmát (az érmék számát) és át szeretné rendezni minden
zsák tartalmát az érmék költöztetésével úgy, hogy végül minden zsákban azonos
számú érme legyen. Írjunk heurisztikus algoritmust, amely segít a főnöknek,
hogy, amennyiben ez lehetséges a legkevesebb költöztetéssel érje el a célját!*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(int& zsakok_szama, vector<int>& ermek) {
	cin >> zsakok_szama;
	ermek.resize(zsakok_szama);
	for (int i = 0; i < zsakok_szama; i++) {
		cin >> ermek[i];
	}
}

void egyenlo_hiany_tobblet(int& zsakok_szama, vector<int>& ermek, vector<int>& hianyos, vector<int>& tobblet, int& megoldas, int& atlag) {
	for (int i = 0; i < zsakok_szama; i++) {
		if (ermek[i] > atlag) {
			tobblet.push_back(ermek[i] - atlag);
		}
		if (ermek[i] < atlag) {
			hianyos.push_back(atlag - ermek[i]);
		}
	}
	for (int i = 0; i < tobblet.size(); i++) {
		for (int j = 0; j < hianyos.size(); j++) {
			if (tobblet[i] != 0 && tobblet[i] == hianyos[j]) {
				megoldas++;
				tobblet[i] = 0;
				hianyos[j] = 0;
				break;
			}
		}
	}
}

void elso_megoldas(int& zsakok_szama, vector<int>& ermek, vector<int>& hianyos, vector<int>& tobblet, int& szamlalo) {
	bool csere;
	do {
		csere = false;
		sort(tobblet.begin(), tobblet.end());
		sort(hianyos.begin(), hianyos.end());
		for (int i = 0; i < tobblet.size(); i++) {
			if (tobblet[i] != 0) {
				for (int j = 0; j < hianyos.size(); j++) {
					if (hianyos[j] != 0) {
						if (hianyos[j] > tobblet[i]) {
							hianyos[j] -= tobblet[i];
							tobblet[i] = 0;
							szamlalo++;
							csere = true;
							break;
						}
					}
				}
			}
		}
	} while (csere);

	for (int i = 0; i < tobblet.size(); i++) {
		if (tobblet[i] != 0) {
			for (int j = 0; j < hianyos.size(); j++) {
				if (hianyos[j] != 0) {
					tobblet[i] -= hianyos[j];
					hianyos[j] = 0;
					szamlalo++;
				}
			}
		}
	}
}

void masodik_megoldas(int& zsakok_szama, vector<int>& ermek, vector<int>& hianyos, vector<int>& tobblet, int& szamlalo) {
	bool csere;
	do {
		csere = false;
		sort(tobblet.begin(), tobblet.end());
		sort(hianyos.begin(), hianyos.end());
		for (int i = tobblet.size() - 1; i >= 0; i--) {
			if (tobblet[i] != 0) {
				for (int j = hianyos.size() - 1; j >= 0; j--) {
					if (hianyos[j] != 0) {
						if (hianyos[j] > tobblet[i]) {
							hianyos[j] -= tobblet[i];
							tobblet[i] = 0;
							szamlalo++;
							csere = true;
							break;
						}
					}
				}
			}
		}
	} while (csere);

	for (int i = tobblet.size() - 1; i >= 0; i--) {
		if (tobblet[i] != 0) {
			for (int j = hianyos.size() - 1; j >= 0; j--) {
				if (hianyos[j] != 0) {
					tobblet[i] -= hianyos[j];
					hianyos[j] = 0;
					szamlalo++;
				}
			}
		}
	}
}

int kincstar(int& zsakok_szama, vector<int>& ermek) {
	int osszeg = 0, megoldas = 0;
	for (int i = 0; i < zsakok_szama; i++) {
		osszeg += ermek[i];
	}
	if (osszeg % zsakok_szama != 0) {
		return -1;
	}
	int atlag = osszeg / zsakok_szama;
	vector<int> hianyos, tobblet;
	egyenlo_hiany_tobblet(zsakok_szama, ermek, hianyos, tobblet, megoldas, atlag);

	int szamlalo1 = megoldas, szamlalo2 = megoldas;
	vector<int> temp_hianyos = hianyos, temp_tobblet = tobblet;

	elso_megoldas(zsakok_szama, ermek, temp_hianyos, temp_tobblet, szamlalo1);
	
	masodik_megoldas(zsakok_szama, ermek, hianyos, tobblet, szamlalo2);

	return min(szamlalo1, szamlalo2);
}

void kiir(int& megoldas) {
	cout << megoldas;
}

int main() {
	int zsakok_szama;
	vector<int> ermek;
	beolvas(zsakok_szama, ermek);

	int megoldas = kincstar(zsakok_szama, ermek);

	kiir(megoldas);
	return 0;
}