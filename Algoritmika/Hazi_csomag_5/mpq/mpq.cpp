/*Boda Norbert
511-es csoport
Lab5/01
Generáljunk minden lehetséges sorozatot, amelynek elemei a 0, 1, 2 halmazból
vannak, és a 0 𝑚-szer, az 1 𝑝-szer és a 2 𝑞-szor fordul elő*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(vector<short>& mpq) {
	for (int i = 0; i < mpq.size(); i++) {
		cin >> mpq[i];
	}
}

void general_mpq(vector<short>& mpq, vector<short>& temp_megoldas, short szamlalo, short& hossz, vector<vector<short>>& megoldas) {
	if (szamlalo == hossz) {
		megoldas.push_back(temp_megoldas);
		return;
	}
	for (int i = 0; i < mpq.size(); i++) {
		if (mpq[i] > 0) {
			temp_megoldas[szamlalo] = i;
			mpq[i]--;
			general_mpq(mpq, temp_megoldas, szamlalo + 1, hossz, megoldas);
			mpq[i]++;
		}
	}
}

vector<vector<short>> meghiv_mpq(vector<short>& mpq) {
	short hossz = mpq[0] + mpq[1] + mpq[2];
	vector<short> temp_megoldas(hossz);
	vector<vector<short>> megoldas;
	general_mpq(mpq, temp_megoldas, 0, hossz, megoldas);
	return megoldas;
}

void kiir(vector<vector<short>>& megoldas) {
	for (int i = 0; i < megoldas.size(); i++) {
		for (int j = 0; j < megoldas[i].size(); j++) {
			cout << megoldas[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<short> mpq(3); //3 hosszusagu, mert 3 szamot olvas be
	beolvas(mpq);

	vector<vector<short>> megoldas = meghiv_mpq(mpq);

	kiir(megoldas);
	return 0;
}