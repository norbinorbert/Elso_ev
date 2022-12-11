#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void beolvas(int& szam) {
	cin >> szam;
}

bool prim(int szam) {
	if (szam == 1) {
		return false;
	}
	else if (szam % 2 == 0) {
		return (szam == 2);
	}
	else if (szam <= 5) {
		return true;
	}
	else {
		if ((szam - 1) % 6 != 0 && (szam + 1) % 6 != 0) {
			return false;
		}
		else {
			double gyok = sqrt(szam);
			for (int i = 3; i <= gyok; i+=2) {
				if (szam % i == 0) {
					return false;
				}
			}
		}
	}
	return true;
}

void torzstenyezore_bontas(int& szam, vector<int>& torzstenyezok) {
	int masolat = szam, oszto = 2;
	
	//a 2 es 3 nem (6k-1) vagy (6k+1) alakuak, ezert ezeket kulon vizsgalom
	if (masolat % oszto == 0) {
		torzstenyezok.push_back(oszto);
		if (prim(szam / oszto)) {
			torzstenyezok.push_back(szam / oszto);
		}
	}
	oszto = 3;
	if (masolat % oszto == 0) {
		torzstenyezok.push_back(oszto);
		if (prim(szam / oszto)) {
			torzstenyezok.push_back(szam / oszto);
		}
	}

	oszto = 5;
	double gyok = sqrt(szam);
	while (oszto <= gyok) {
		if (masolat % oszto == 0) {
			torzstenyezok.push_back(oszto);
			if (oszto != gyok && prim(szam / oszto)) {
				torzstenyezok.push_back(szam / oszto);
			}
		}
		//csak a prim alaku szamokat kell nezni, ha torzstenyezok vagy sem,
		//amelyek (6k-1) vagy (6k+1) alakuak
		if ((oszto + 1) % 6 == 0) {
			oszto += 2;
		}
		if ((oszto - 1) % 6 == 0) {
			oszto += 4;
		}
	}
}

double EulerPhi(int& szam) {
	if (prim(szam)) {
		return 1;
	}
	double temp_megoldas = szam;
	vector<int> torzstenyezok;
	torzstenyezore_bontas(szam, torzstenyezok);

	//𝜑(𝑛) fuggveny kiszamitasa
	for (int i = 0; i < torzstenyezok.size(); i++) {
		temp_megoldas = double(temp_megoldas * double(double(double(torzstenyezok[i] - 1) / torzstenyezok[i])));
	}
	return szam - temp_megoldas;
}

void kiir(double& megoldas) {
	cout << megoldas;
}

int main() {
	int szam;
	beolvas(szam);

	double megoldas = EulerPhi(szam);

	kiir(megoldas);
	return 0;
}