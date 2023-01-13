/*Boda Norbert
511-es csoport
Lab8/05
Adott egy 𝑛 soros és 𝑚 oszlopos bitmátrix. Határozzuk meg a legnagyobb
olyan négyzet oldalhosszát, amely a mátrixban található és csak 1-eseket tartalmaz!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& sor, short& oszlop, vector<vector<short>>& bitmatrix) {
	cin >> sor >> oszlop;
	bitmatrix.resize(sor);
	for (short i = 0; i < sor; i++) {
		bitmatrix[i].resize(oszlop);
		for (short j = 0; j < oszlop; j++) {
			cin >> bitmatrix[i][j];
		}
	}
}

//visszateriti 3 szam minimumat
short minimum(short a, short b, short c) {
	if (a < b) {
		return (a < c) ? a : c;
	}
	else {
		return (b < c) ? b : c;
	}
}

void felepit(short& sor, short& oszlop, vector<vector<short>>& bitmatrix, vector<vector<short>>& megoldas) {
	//utolso sor felepitese
	for (short i = 0; i < sor; i++) {
		if (bitmatrix[i][oszlop - 1] == 1) {
			megoldas[i][oszlop - 1] = 1;
		}
	}
	//utolso oszlop felepitese
	for (short i = 0; i < oszlop; i++) {
		if (bitmatrix[sor - 1][i] == 1) {
			megoldas[sor - 1][i] = 1;
		}
	}
	//matrix tobbi reszenek felepitese
	for (short i = sor - 2; i >= 0; i--) {
		for (short j = oszlop - 2; j >= 0; j--) {
			if (bitmatrix[i][j] == 1) {
				megoldas[i][j] = minimum(megoldas[i + 1][j], megoldas[i][j + 1], megoldas[i + 1][j + 1]) + 1;
			}
		}
	}
}

//megkeresi egy matrixban a legnagyobb elemet
short keres_max(vector<vector<short>>& megoldas) {
	short maximum = megoldas[0][0];
	for (short i = 0; i < megoldas.size(); i++) {
		for (short j = 0; j < megoldas[i].size(); j++) {
			if (megoldas[i][j] > maximum) {
				maximum = megoldas[i][j];
			}
		}
	}
	return maximum;
}

void kiir(vector<vector<short>>& megoldas) {
	short maximum = keres_max(megoldas);
	cout << maximum << endl;
}

int main() {
	short sor, oszlop;
	vector<vector<short>> bitmatrix;
	beolvas(sor, oszlop, bitmatrix);

	vector<vector<short>> megoldas(sor, vector<short>(oszlop, 0));
	felepit(sor, oszlop, bitmatrix, megoldas);

	kiir(megoldas);
	return 0;
}