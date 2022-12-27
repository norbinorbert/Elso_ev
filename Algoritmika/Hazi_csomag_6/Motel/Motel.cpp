/*Boda Norbert
511-es csoport
Lab6/08
Az Encián motelben évekkel előre is fogadnak foglalásokat az odaérkező
𝑛 turistacsoport számára. Ismervén a napot, amellyel kezdve foglalni lehet
és amelyet 1-el számozunk, a csoportok megjelölik az első és az utolsó napot,
amelyet a motelben szeretnének tölteni. Az Encián tulajdonosa mindegyik
csoport számára szeretne egy tradicionális előadást szervezni, amire csak a motel
dísztermében kerülhet sor, ahova egyszerre csak egy turistacsoport fér be. Ezeken
az előadásokon fel fog lépni egy előadó, aki megszabja azt az 𝑛 napot, amikor
el tud jönni az előadásokra. Segítsetek a tulajdonosnak eldönteni, hogy melyik
turistacsoportnak melyik napra szervezze meg az előadást.*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(short& napok_szama, vector<pair<short, short>>& intervallumok, vector<short>& napok) {
	cin >> napok_szama;
	intervallumok.resize(napok_szama);
	napok.resize(napok_szama);
	for (short i = 0; i < napok_szama; i++) {
		cin >> intervallumok[i].first >> intervallumok[i].second;
	}
	for (short i = 0; i < napok_szama; i++) {
		cin >> napok[i];
	}
}

short keres_max(vector<pair<short, short>>& intervallumok) {
	short maximum = intervallumok[0].second;
	for (short i = 1; i < intervallumok.size(); i++) {
		if (maximum < intervallumok[i].second) {
			maximum = intervallumok[i].second;
		}
	}
	return maximum;
}

void felepit(vector<short>& darab, vector<pair<short, short>>& intervallumok) {
	short maximum_nap = keres_max(intervallumok);
	darab.resize(maximum_nap + 1, 0);
	for (short i = 0; i < intervallumok.size(); i++) {
		for (short j = intervallumok[i].first; j <= intervallumok[i].second; j++) {
			darab[j]++;
		}
	}
}

bool vegso_nap_szerint_novekvo(pair<short, short>& a, pair<short, short>& b) {
	if (a.second != b.second) {
		return (a.second < b.second);
	}
	else {
		return (a.first < b.first);
	}
}

vector<pair<short, short>> Motel(short& napok_szama, vector<pair<short, short>>& intervallumok, vector<short>& napok) {
	vector<short> darab, temp_napok = napok;
	vector<pair<short, short>> megoldas, temp_intervallumok = intervallumok;
	vector<bool> volt(napok_szama, false), temp_volt(napok_szama, false);
	felepit(darab, intervallumok);
	sort(temp_napok.begin(), temp_napok.end());
	sort(temp_intervallumok.begin(), temp_intervallumok.end(), vegso_nap_szerint_novekvo);

	for (short i = 0; i < temp_napok.size(); i++) {
		if (darab[temp_napok[i]] == 0) {
			vector<pair<short, short>> ures;
			return ures;
		}
		else {
			short j = 0;
			while (temp_intervallumok[j].first > temp_napok[i] || temp_intervallumok[j].second < temp_napok[i] || volt[j]) {
				j++;
			}
			volt[j] = true;
			short i_index = 0, j_index = 0;
			while (napok[i_index] != temp_napok[i]) {
				i_index++;
			}
			while (intervallumok[j_index] != temp_intervallumok[j]) {
				j_index++;
			}
			megoldas.push_back({ j_index + 1, i_index + 1 });
			for (short k = temp_intervallumok[j].first; k <= temp_intervallumok[j].second; k++) {
				darab[k]--;
			}
		}
	}
	return megoldas;
}

void kiir(vector<pair<short, short>>& megoldas) {
	if (megoldas.size() == 0) {
		cout << 0 << " " << 0;
	}
	for (short i = 0; i < megoldas.size(); i++) {
		cout << megoldas[i].first << " " << megoldas[i].second << endl;
	}
}

int main() {
	short napok_szama;
	vector<pair<short, short>> intervallumok;
	vector<short> napok;
	beolvas(napok_szama, intervallumok, napok);

	vector<pair<short, short>> megoldas = Motel(napok_szama, intervallumok, napok);

	kiir(megoldas);
	return 0;
}