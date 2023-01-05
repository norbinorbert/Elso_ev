/*Boda Norbert
511-es csoport
Lab7/07
Adott egy 𝑛 elemű egész számokat tartalmazó 𝑎 sorozat. Állapítsuk meg
a sorozatban található inverziók számát! Inverziónak nevezünk minden olyan
𝑖 < 𝑗 indexpárt, amelyre 𝑎𝑖 > 𝑎𝑗 .*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& elemek_szama, vector<int>& szamok) {
	cin >> elemek_szama;
	szamok.resize(elemek_szama);
	for (int i = 0; i < elemek_szama; i++) {
		cin >> szamok[i];
	}
}

void osszefesul(vector<int>& szamok, int bal, int kozep, int jobb, long long& szamlalo) {
	int i = bal, j = kozep + 1;
	long long temp_szamlalo = 0;
	vector<int> seged;
	while (i <= kozep && j <= jobb) {
		if (szamok[i] <= szamok[j]) {
			szamlalo += temp_szamlalo;
			seged.push_back(szamok[i]);
			i++;
		}
		else {
			temp_szamlalo++;
			seged.push_back(szamok[j]);
			j++;
		}
	}
	while (i <= kozep) {
		szamlalo += temp_szamlalo;
		seged.push_back(szamok[i]);
		i++;
	}
	while (j <= jobb) {
		seged.push_back(szamok[j]);
		j++;
	}
	for (int i = 0; i < seged.size(); i++) {
		szamok[bal + i] = seged[i];
	}
}

void merge_sort(vector<int>& szamok, int bal, int jobb, long long& szamlalo) {
	if (bal < jobb) {
		int kozep = (bal + jobb) / 2;
		merge_sort(szamok, bal, kozep, szamlalo);
		merge_sort(szamok, kozep + 1, jobb, szamlalo);
		osszefesul(szamok, bal, kozep, jobb, szamlalo);
	}
}

long long inverziok(int& elemek_szama, vector<int>& szamok) {
	long long szamlalo = 0;
	merge_sort(szamok, 0, szamok.size() - 1, szamlalo);
	return szamlalo;
}

void kiir(long long& inverziok_szama) {
	cout << inverziok_szama;
}

int main() {
	int elemek_szama;
	vector<int> szamok;
	beolvas(elemek_szama, szamok);

	long long inverziok_szama = inverziok(elemek_szama, szamok);

	kiir(inverziok_szama);

	return 0;
}