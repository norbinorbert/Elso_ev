/*Boda Norbert
511-es csoport
Lab5/05
Bontsunk fel egy szót minden lehetséges módon palindromszavakra!*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(string& szo) {
	cin >> szo;
}

bool palindrom_e(string& szo) {
	int i = 0;
	while (i < szo.size() / 2) {
		if (szo[i] != szo[szo.size() - i - 1]) {
			return false;
		}
		i++;
	}
	return true;
}

void general_palindrom(string& szo, vector<string>& temp_megoldas, vector<vector<string>>& megoldasok, int jelenlegi_hossz, int index) {
	if (jelenlegi_hossz == szo.size()) {
		bool helyes = true;
		//vizsgalja ha a jelenlegi megoldasban az osszes szo pallindrom-e
		for (int i = 0; i < temp_megoldas.size(); i++) {
			if (!palindrom_e(temp_megoldas[i])) {
				helyes = false;
			}
		}
		if (helyes) {
			megoldasok.push_back(temp_megoldas);
		}
		return;
	}
	//az i jelkepezi, hogy milyen hosszusagu particiot akarunk a megmaradt betukbol
	for (int i = 1; i <= szo.size() - jelenlegi_hossz; i++) {
		string temp_szo = "";
		//a j-t tartalmazo ciklus legeneralja az i hosszusagu particiot a megfelelo betutol kezdve, illetve hozzaadja a jelenlegi megoldashoz
		for (int j = jelenlegi_hossz; j < jelenlegi_hossz + i; j++) {
			temp_szo += szo[j];
			temp_megoldas[index] = temp_szo;
		}
		if (jelenlegi_hossz < szo.size()) {
			general_palindrom(szo, temp_megoldas, megoldasok, jelenlegi_hossz + i, index + 1);
		}
		temp_megoldas[index] = "";
	}
}

vector<vector<string>> palindromok(string& szo) {
	vector<vector<string>> megoldasok;
	vector<string> temp_megoldas(szo.size(), "");
	general_palindrom(szo, temp_megoldas, megoldasok, 0, 0);
	return megoldasok;
}

void kiir(vector<vector<string>>& megoldasok) {
	for (int i = 0; i < megoldasok.size(); i++) {
		for (int j = 0; j < megoldasok[i].size(); j++) {
			cout << megoldasok[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	string szo;
	beolvas(szo);

	vector<vector<string>> megoldasok = palindromok(szo);

	kiir(megoldasok);
}