/*Boda Norbert
511-es csoport
Lab2/08
Vizsgáljuk meg, hogy egy adott, nxn méretű négyzetes tömb bűvös négyzet-e
vagy sem. Egy természetes számokkal feltöltött négyzetes tömböt akkor nevezünk
bűvös négyzetnek, ha páronként különböző számokat tartalmaz, a számok összege
soronként és oszloponként, valamint a két átló mentén azonos. Alkalmazzuk a
Halmaz-e programozási tételt!
*/
#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& n, vector<vector<unsigned long long>>& negyzet) {
	cin >> n;
	negyzet.resize(n);
	unsigned long long temp_szam;
	for (short i = 0; i < n; i++) {
		for (short j = 0; j < n; j++) {
			cin >> temp_szam;
			negyzet[i].push_back(temp_szam);
		}
	}
	return;
}

void tomb_alakitas(vector<vector<unsigned long long>>& negyzet, vector<unsigned long long>& tomb) {
	for (short i = 0; i < negyzet.size(); i++) {
		for (short j = 0; j < negyzet.size(); j++) {
			tomb.push_back(negyzet[i][j]);
		}
	}
	return;
}

//halmaz-e programozasi tetel
bool halmaz_e(vector<unsigned long long> tomb) {
	short i = 0;
	bool ok = true;
	while (ok && i < tomb.size()-1) {
		short j = i + 1;
		while (j <= tomb.size() - 1 && tomb[i] != tomb[j]) {
			j++;
		}
		ok = (j > tomb.size()-1);
		i++;
	}
	return ok;
}

bool buvos_negyzet(vector<vector<unsigned long long>>& negyzet) {
	unsigned long long osszeg = 0, prev_osszeg = 0, foatlo_osszeg = 0, mellekatlo_osszeg = 0;
	
	//soronkenti osszegek vizsgalasa
	for (short i = 0; i < negyzet.size(); i++) {
		for (short j = 0; j < negyzet.size(); j++) {
			osszeg += negyzet[i][j];

			//foatlo elemeinek osszege
			if (i == j) {
				foatlo_osszeg += negyzet[i][j];
			}

			//mellekatlo elemeinek osszege
			if (i + j == negyzet.size() - 1) {
				mellekatlo_osszeg += negyzet[i][j];
			}
		}
		if (prev_osszeg != osszeg && prev_osszeg != 0) {
			return false;
		}
		prev_osszeg = osszeg;
		osszeg = 0;
	}

	//oszloponkenti osszegek vizsgalata
	for (short i = 0; i < negyzet.size(); i++) {
		for (short j = 0; j < negyzet.size(); j++) {
			osszeg += negyzet[j][i];
		}
		if (prev_osszeg != osszeg && prev_osszeg != 0) {
			return false;
		}
		prev_osszeg = osszeg;
		osszeg = 0;
	}

	if (foatlo_osszeg != mellekatlo_osszeg || foatlo_osszeg != prev_osszeg) {
		return false;
	}

	return true;
}

int main() {
	short n;
	vector<vector<unsigned long long>> negyzet;
	beolvas(n, negyzet);

	vector<unsigned long long> tomb;
	tomb_alakitas(negyzet, tomb);

	if (halmaz_e(tomb)) {
		if (buvos_negyzet(negyzet)) {
			cout << "igen";
		}
		else {
			cout << "nem";
		}
	}
	else {
		cout << "nem";
	}

	return 0;
}