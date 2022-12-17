/*Boda Norbert
511-es csoport
Lab5/08
Adott egy 𝑛 szót tartalmazó lista. Legkevesebb hány szóval tudjuk lefedni
az angol ábécé összes kisbetűjét, úgy, hogy a kiválasztott szavak között minden
betű pontosan egyszer szerepeljen?*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(short& szavak_szama, vector<string>& szavak) {
	cin >> szavak_szama;
	szavak.resize(szavak_szama);
	for (short i = 0; i < szavak_szama; i++) {
		cin >> szavak[i];
	}
}

void rendez(vector<string>& szavak) {
	vector<short> hosszak;
	for (short i = 0; i < szavak.size(); i++) {
		hosszak.push_back(szavak[i].size());
	}

	vector<int> darab(31);
	for (int i = 0; i < hosszak.size(); i++) {
		darab[hosszak[i]]++;
	}
	for (int i = 1; i < darab.size(); i++) {
		darab[i] += darab[i - 1];
	}

	vector<string> temp(hosszak.size());
	for (int i = hosszak.size() - 1; i >= 0; i--) {
		temp[temp.size()-darab[hosszak[i]]] = szavak[i];
		darab[hosszak[i]]--;
	}
	szavak = temp;
}

void felepit_megoldas(vector<string>& rendezett_megoldas, string& jelenlegi_megoldas, string& jelenlegi_megoldas_spacek_nelkul) {
	sort(rendezett_megoldas.begin(), rendezett_megoldas.end());
	for (short i = 0; i < rendezett_megoldas.size(); i++) {
		jelenlegi_megoldas += rendezett_megoldas[i] + " ";
		jelenlegi_megoldas_spacek_nelkul += rendezett_megoldas[i];
	}
}

bool ervenyes(string& szo, vector<bool>& elofordult) {
	for (short i = 0; i < szo.size(); i++) {
		short index = szo[i] - 97;
		if (elofordult[index]) {
			return false;
		}
	}
	return true;
}

void general_ABClefedes(short& max_hossz, vector<string>& szavak, vector<string>& temp_megoldas, vector<string>& megoldas, vector<bool>& mask, vector<bool>& elofordult, 
	string& jelenlegi_megoldas, string& jelenlegi_megoldas_spacek_nelkul) {
	if (temp_megoldas.size() > max_hossz) {
		return;
	}
	if (elofordult == mask && temp_megoldas.size() <= max_hossz) {
		if (jelenlegi_megoldas == "") {
			vector<string> rendezett_megoldas = temp_megoldas;
			felepit_megoldas(rendezett_megoldas, jelenlegi_megoldas, jelenlegi_megoldas_spacek_nelkul);
			max_hossz = temp_megoldas.size();
			megoldas = rendezett_megoldas;
		}
		else {
			string uj_megoldas = "", uj_megoldas_spacek_nelkul = "";
			vector<string> rendezett_megoldas = temp_megoldas;
			felepit_megoldas(rendezett_megoldas, uj_megoldas, uj_megoldas_spacek_nelkul);
			if (uj_megoldas_spacek_nelkul < jelenlegi_megoldas_spacek_nelkul) {
				jelenlegi_megoldas = uj_megoldas;
				jelenlegi_megoldas_spacek_nelkul = uj_megoldas_spacek_nelkul;
				max_hossz = temp_megoldas.size();
				megoldas = rendezett_megoldas;
			}
			else if (uj_megoldas_spacek_nelkul == jelenlegi_megoldas_spacek_nelkul) {
				if (uj_megoldas < jelenlegi_megoldas) {
					jelenlegi_megoldas = uj_megoldas;
					jelenlegi_megoldas_spacek_nelkul = uj_megoldas_spacek_nelkul;
					max_hossz = temp_megoldas.size();
					megoldas = rendezett_megoldas;
				}
			}
		}
		return;
	}
	for (short i = 0; i < szavak.size(); i++) {
		if (ervenyes(szavak[i], elofordult)) {
			for (short j = 0; j < szavak[i].size(); j++) {
				short index = szavak[i][j] - 97;
				elofordult[index] = true;
			}
			temp_megoldas.push_back(szavak[i]);
			general_ABClefedes(max_hossz, szavak, temp_megoldas, megoldas, mask, elofordult, jelenlegi_megoldas, jelenlegi_megoldas_spacek_nelkul);
			temp_megoldas.pop_back();
			for (short j = 0; j < szavak[i].size(); j++) {
				short index = szavak[i][j] - 97;
				elofordult[index] = false;
			}
		}
	}
}

vector<string> ABClefedes(short& szavak_szama, vector<string>& szavak){
	vector<string> megoldas, temp_megoldas;
	short max_hossz = szavak_szama;
	vector<bool> mask(26, true), elofordult(26, false); //26 betu van az angol ABC-ben, ezert 26 hosszusaguak a vektorok
	string jelenlegi_megoldas = "", jelenlegi_megoldas_spacek_nelkul = "";
	general_ABClefedes(max_hossz, szavak, temp_megoldas, megoldas, mask, elofordult, jelenlegi_megoldas, jelenlegi_megoldas_spacek_nelkul);
	return megoldas;
}

void kiir(vector<string>& megoldas) {
	if (megoldas.size() == 0) {
		cout << -1;
	}
	else {
		cout << megoldas.size() << endl;
		for (short i = 0; i < megoldas.size(); i++) {
			cout << megoldas[i] << endl;
		}
	}
}

int main() {
	short szavak_szama;
	vector<string> szavak;
	beolvas(szavak_szama, szavak);
	
	rendez(szavak);

 	vector<string> megoldas = ABClefedes(szavak_szama, szavak);

	kiir(megoldas);
	return 0;
}