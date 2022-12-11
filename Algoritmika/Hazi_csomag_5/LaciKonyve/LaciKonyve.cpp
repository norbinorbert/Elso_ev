/*Boda Norbert
511-es csoport
Lab5/07
Adva van egy 𝑛 személyből álló csoport. Minden személynek van legalább 𝑛/2
barátja a csoporton belül. Lacinak van egy könyve, amelyet a csoport minden
tagja el szeretne olvasni. Írjátok ki, hogyan vándorol a könyv egyik személytől
a másikig úgy, hogy mindenkihez csak egyszer kerül, és egy személy csak egy
barátjának kölcsönzi a könyvet, amíg az visszatér Lacihoz. Az összes lehetséges
megoldást keressük, a megoldásokat tetszőleges sorrendben ki lehet íratni.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//megnezi ha a nev letezik-e a vektorban
bool uj_nev(vector<string>& nevek, string& nev) {
	short i = 0;
	while (i < nevek.size()) {
		if (nevek[i] == nev) {
			return false;
		}
		i++;
	}
	return true;
}

//megnezi a nev hanyadik indexen szerepel
short nev_index(vector<string>& nevek, string& nev) {
	short i = 0;
	while (i < nevek.size()) {
		if (nevek[i] == nev) {
			return i;
		}
		i++;
	}
}

//megnezi, hogy Laci melyik indexen szerepel
short keres_Laci(vector<string>& temp_megoldas) {
	short i = temp_megoldas.size() - 1;
	while (i > 0) {
		if (temp_megoldas[i] == "Laci") {
			return i;
		}
		i--;
	}
	return 0;
}

void beolvas(short& emberek_szama, short& barat_parosok_szama, vector<pair<string, string>>& parok, vector<string>& nevek) {
	cin >> emberek_szama >> barat_parosok_szama;
	string nev1, nev2;
	cin >> nev1 >> nev2;
	//eltarolja a beolvasott neveket, illetve a parokat
	nevek.push_back(nev1);
	nevek.push_back(nev2);
	parok.push_back(make_pair(nev1, nev2));
	for (short i = 1; i < barat_parosok_szama; i++) {
		cin >> nev1;
		//ha meg nem olvasott be ilyen nevet akkor azt eltarolja a nevek vectorban
		if (uj_nev(nevek, nev1)) {
			nevek.push_back(nev1);
		}
		cin >> nev2;
		if (uj_nev(nevek, nev2)) {
			nevek.push_back(nev2);
		}
		parok.push_back(make_pair(nev1, nev2));
	}
}

void general_LaciKonyve(short szint, short& emberek_szama, vector<vector<string>>& megoldas, vector<string>& temp_megoldas, vector<pair<string, string>>& parok, vector<bool>& hasznalt_parok,
	string mostani_szemely, vector<string>& nevek, vector<bool>& hasznalt_nevek) {
	if (szint == emberek_szama + 1) {
		//ha a megoldas megfelelo hosszusagu es az utolso szemely Laci akkor elmenti a megoldast
		if (mostani_szemely == "Laci") {
			megoldas.push_back(temp_megoldas);
		}
		return;
	}
	for (short i = 0; i < parok.size(); i++) {
		if ((parok[i].first == mostani_szemely || parok[i].second == mostani_szemely)) {
			if (szint == emberek_szama && ((parok[i].first == "Laci" || parok[i].second == "Laci"))) {
				//ha mar az utolso nev hianyzik (ami mindig Laci lesz), akkor megnezi, hogy ez ne ismetlodjon
				short Laci_index = keres_Laci(temp_megoldas);
				if (Laci_index == 0) {
					temp_megoldas[szint] = "Laci";
					general_LaciKonyve(szint + 1, emberek_szama, megoldas, temp_megoldas, parok, hasznalt_parok, "Laci", nevek, hasznalt_nevek);
					temp_megoldas[szint] = "";
				}
			}
			//megnezi ha a jelenlegi part mar vizsgaltuk-e
			else if (hasznalt_parok[i] == false) {
				if (parok[i].first == mostani_szemely) {
					short index = nev_index(nevek, parok[i].second);
					//megnezi ha a nev szerepel mar-e a megoldasban
					if (hasznalt_nevek[index] == false) {
						temp_megoldas[szint] = parok[i].second;
						hasznalt_parok[i] = true;
						hasznalt_nevek[index] = true;
						general_LaciKonyve(szint + 1, emberek_szama, megoldas, temp_megoldas, parok, hasznalt_parok, parok[i].second, nevek, hasznalt_nevek);
						hasznalt_nevek[index] = false;
						hasznalt_parok[i] = false;
						temp_megoldas[szint] = "";
					}
				}
				else {
					short index = nev_index(nevek, parok[i].first);
					//megnezi ha a nev szerepel mar-e a megoldasban
					if (hasznalt_nevek[index] == false) {
						temp_megoldas[szint] = parok[i].first;
						hasznalt_parok[i] = true;
						hasznalt_nevek[index] = true;
						general_LaciKonyve(szint + 1, emberek_szama, megoldas, temp_megoldas, parok, hasznalt_parok, parok[i].first, nevek, hasznalt_nevek);
						hasznalt_nevek[index] = false;
						hasznalt_parok[i] = false;
						temp_megoldas[szint] = "";
					}
				}
			}
			
		}
	}

}

vector<vector<string>> LaciKonyve(short& emberek_szama, short& barat_parosok_szama, vector<pair<string, string>>& parok, vector<string>& nevek) {
	vector<vector<string>> megoldas;
	vector<string> temp_megoldas(emberek_szama + 1);
	vector<bool> hasznalt_parok(barat_parosok_szama, false), hasznalt_nevek(emberek_szama, false);
	temp_megoldas[0] = "Laci"; //mindig Lacitol indul el a konyv
	general_LaciKonyve(1, emberek_szama, megoldas, temp_megoldas, parok, hasznalt_parok, "Laci", nevek, hasznalt_nevek);
	return megoldas;
}

void kiir(vector<vector<string>>& megoldas) {
	for (short i = 0; i < megoldas.size(); i++) {
		for (short j = 0; j < megoldas[i].size(); j++) {
			cout << megoldas[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	short emberek_szama, barat_parosok_szama;
	vector<pair<string, string>> parok;
	vector<string> nevek;
	beolvas(emberek_szama, barat_parosok_szama, parok, nevek);

	vector<vector<string>> megoldas = LaciKonyve(emberek_szama, barat_parosok_szama, parok, nevek);

	kiir(megoldas);
	return 0;
}