/*Boda Norbert
511-es csoport
Lab7/04
Adott egy 𝑛 elemű tömb, mely 32 bites előjeles egész számokat tartalmaz
és egy 𝑥 32 bites előjeles egész szám. Határozzuk meg, hogy létezik-e két olyan
eleme a tömbnek, melyek összege pontosan 𝑥. Alkalmazzunk bináris keresést!*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void beolvas(int& elemek_szama, int& osszeg, vector<int>& szamok) {
	cin >> elemek_szama >> osszeg;
	szamok.resize(elemek_szama);
	for (int i = 0; i < elemek_szama; i++) {
		cin >> szamok[i];
	}
}

bool letezik(vector<int>& szamok, long long keresendo_szam, int jobb, int bal) {
	if (jobb < bal) {
		int kozep = (bal + jobb) / 2;
		if (szamok[kozep] == keresendo_szam) {
			return true;
		}
		else {
			if (szamok[kozep] < keresendo_szam) {
				return letezik(szamok, keresendo_szam, kozep + 1, bal);
			}
			else {
				return letezik(szamok, keresendo_szam, jobb, kozep);
			}
		}
	}
	else if ((jobb == bal) && (szamok[bal] == keresendo_szam)) {
		return true;
	}
	return false;
}

vector<pair<int, int>> SUM(int& osszeg, vector<int>& szamok) {
	vector<int> rendezett = szamok;
	vector<pair<int, int>> megoldas;
	//n*log(n)-es rendezes, az algoritmus legrosszabb esetben n^2-es bonyolultsagu, ugyhogy ez nem ront rajta
	sort(rendezett.begin(), rendezett.end());
	for (int i = 0; i < szamok.size(); i++) {
		long long temp_osszeg = osszeg;
		long long temp_szam = szamok[i];
		long long keresendo_szam = temp_osszeg - temp_szam;
		if (keresendo_szam >= INT_MIN && keresendo_szam <= INT_MAX) {
			if (letezik(rendezett, keresendo_szam, 0, rendezett.size() - 1)) {
				if (szamok[i] == keresendo_szam) {
					for (int j = i + 1; j < szamok.size(); j++) {
						if (szamok[j] == szamok[i]) {
							megoldas.push_back({ i + 1, j + 1 });
							return megoldas;
						}
					}
				}
				else {
					for (int j = i + 1; j < szamok.size(); j++) {
						if (szamok[j] == keresendo_szam) {
							megoldas.push_back({ i + 1, j + 1 });
							return megoldas;
						}
					}
				}
			}
		}
	}
	
	return megoldas;
}

void kiir(vector<pair<int, int>>& megoldas) {
	if (megoldas.size() == 0) {
		cout << 0;
	}
	else {
		cout << 1 << endl;
		cout << megoldas[0].first << " " << megoldas[0].second;
	}
}

int main() {
	int elemek_szama, osszeg;
	vector<int> szamok;
	beolvas(elemek_szama, osszeg, szamok);

	vector<pair<int, int>> megoldas = SUM(osszeg, szamok);

	kiir(megoldas);

	return 0;
}