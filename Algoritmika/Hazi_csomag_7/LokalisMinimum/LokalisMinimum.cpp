/*Boda Norbert
511-es csoport
Lab7/05
Adott 𝑛 elemű 𝑎 sorozat, melyre igaz, hogy 𝑎1 > 𝑎2 és 𝑎𝑛−1 < 𝑎𝑛. Lokális
minimumnak nevezünk minden olyan 𝑎𝑖 elemet, amelyre 𝑎𝑖−1 > 𝑎𝑖 < 𝑎𝑖+1 és
𝑖 = 2, 𝑛 − 1. Határozzunk meg egy tetszőleges lokális minimumot egy tömbben,
melynek kezdetben ismeretlenek az elemei!*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void beolvas(short& sorozat_hossza) {
	cin >> sorozat_hossza;
}

void lekerdez(short index, vector<int>& sorozat) {
	cout << 0 << " " << index << endl;
	cin >> sorozat[index];
}

void kiir_megoldas(short index) {
	cout << 1 << " " << index << endl;
}

void LokalisMinimum(short bal, short kozep, short jobb, vector<int>& sorozat) {
	if (jobb - bal < 3) {
		if (sorozat[bal] == 0) {
			lekerdez(bal, sorozat);
		}
		if (sorozat[kozep] == 0) {
			lekerdez(kozep, sorozat);
		}
		if (sorozat[jobb] == 0) {
			lekerdez(jobb, sorozat);
		}
		if ((sorozat[kozep] < sorozat[bal]) && (sorozat[kozep] < sorozat[jobb])) {
			kiir_megoldas(kozep);
			return;
		}
		if (sorozat[bal] < sorozat[kozep]) {
			kiir_megoldas(bal);
			return;
		}
		if (sorozat[jobb] < sorozat[kozep]) {
			kiir_megoldas(jobb);
			return;
		}
	}
	short bal_kozep = (bal + kozep) / 2;
	short jobb_kozep = (kozep + jobb) / 2;
	if (bal_kozep == kozep) {
		bal_kozep--;
	}
	if (jobb_kozep == kozep) {
		jobb_kozep++;
	}
	if (sorozat[bal_kozep] == 0) {
		lekerdez(bal_kozep, sorozat);
	}
	if (sorozat[bal_kozep] <= sorozat[kozep]) {
		LokalisMinimum(bal, bal_kozep, kozep, sorozat);
		return;
	}
	if (sorozat[jobb_kozep] == 0) {
		lekerdez(jobb_kozep, sorozat);
	}
	if (sorozat[jobb_kozep] <= sorozat[kozep]) {
		LokalisMinimum(kozep, jobb_kozep, jobb, sorozat);
		return;
	}
	if (sorozat[jobb_kozep] > sorozat[kozep] && sorozat[bal_kozep] > sorozat[kozep]) {
		LokalisMinimum(bal_kozep, kozep, jobb_kozep, sorozat);
		return;
	}
}

int main() {
	short sorozat_hossza;
	beolvas(sorozat_hossza);
	vector<int> sorozat(sorozat_hossza + 1, 0);
	sorozat[1] = INT_MAX; //𝑎1 > 𝑎2 biztositasa
	sorozat[sorozat_hossza] = INT_MAX; //𝑎𝑛−1 < 𝑎𝑛 biztositasa

	short kozep = (1 + sorozat_hossza) / 2;
	lekerdez(kozep, sorozat);

	LokalisMinimum(1, kozep, sorozat_hossza, sorozat);
	return 0;
}