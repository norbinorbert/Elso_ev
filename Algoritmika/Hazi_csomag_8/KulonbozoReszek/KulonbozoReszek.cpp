/*Boda Norbert
511-es csoport
Lab8/07
Adott egy 𝑛 karakterből álló karakterlánc, mely kizárólag az angol ábécé
kis- és nagybetűit tartalmazhatja. Határozzuk meg, hogy hány különböző
részsorozata van a megadott string-nek. Azokat a részsorozatokat, melyeknek
ugyanaz a rész-string felel meg, csak egyszer számoljuk.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MOD 1000000007

void beolvas(string& karakterlanc) {
	cin >> karakterlanc;
}

long long KulonbozoReszek(string& karakterlanc) {
	vector<long long> reszsorozatok_szama(karakterlanc.size() + 1, 0);
	string karakterlanc_masolat = " " + karakterlanc; //a karakterlanc elejere betesz egy spacet, hogy egyszerubb legyen az indexeles
	reszsorozatok_szama[0] = 1; //ures halmaz
	for (int i = 1; i < reszsorozatok_szama.size(); i++) {
		reszsorozatok_szama[i] = 2 * reszsorozatok_szama[i - 1];
		int j = i - 1;
		while (j >= 1 && karakterlanc_masolat[j] != karakterlanc_masolat[i]) {
			j--; //megkeresi ha ismetlodott mar a jelenlegi karakter
		}
		if (j != 0) {
			reszsorozatok_szama[i] = reszsorozatok_szama[i] - reszsorozatok_szama[j-1];
			if (reszsorozatok_szama[i] < 0) {
				reszsorozatok_szama[i] += MOD;
			}
		}
		reszsorozatok_szama[i] = reszsorozatok_szama[i] % MOD;
	}
	return reszsorozatok_szama[reszsorozatok_szama.size() - 1];
}

void kiir(long long& megoldas) {
	cout << megoldas;
}

int main() {
	string karakterlanc;
	beolvas(karakterlanc);

	long long megoldas = KulonbozoReszek(karakterlanc);

	kiir(megoldas);
	return 0;
}