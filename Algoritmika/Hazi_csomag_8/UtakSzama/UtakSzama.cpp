/*Boda Norbert
511-es csoport
UtakSzama
Adott egy 𝑛 soros és 𝑚 oszlopos bitmátrix. Határozzuk meg az olyan utak
számát, amelyek a mátrix bal felső sarkából indulnak és a jobb alsó sarkába
érkeznek, minden lépésben vagy lefelé vagy jobbra haladnak és csak azokra a
mezőkre léphetnek, melyek értéke 1. Garantált, hogy a bal felső és jobb alsó
sarokban 1-es érték található.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& sor, short& oszlop, vector<vector<short>>& bitmatrix) {
	cin >> sor >> oszlop;
	bitmatrix.resize(sor, vector<short>(oszlop));
	for (short i = 0; i < sor; i++) {
		for (short j = 0; j < oszlop; j++) {
			cin >> bitmatrix[i][j];
		}
	}
}

vector<vector<long long>> UtakSzama(short& sor, short& oszlop, vector<vector<short>>& bitmatrix) {
	vector<vector<long long>> megoldas(sor, vector<long long>(oszlop, 0));
	megoldas[0][0] = 1;
	for (short i = 1; i < sor; i++) {
		if (bitmatrix[i][0] == 1 && megoldas[i - 1][0] != 0) {
			megoldas[i][0] = 1;
		}
	}
	for (short i = 1; i < oszlop; i++) {
		if (bitmatrix[0][i] == 1 && megoldas[0][i - 1] != 0) {
			megoldas[0][i] = 1;
		}
	}
	for (short i = 1; i < sor; i++) {
		for (short j = 1; j < oszlop; j++) {
			if (bitmatrix[i][j] != 0) {
				megoldas[i][j] = megoldas[i - 1][j] + megoldas[i][j - 1];
			}
		}
	}
	return megoldas;
}

void kiir(vector <vector<long long>>& megoldas) {
	cout << megoldas[megoldas.size() - 1][megoldas[megoldas.size() - 1].size() - 1];
}

int main() {
	short sor, oszlop;
	vector<vector<short>> bitmatrix;
	beolvas(sor, oszlop, bitmatrix);

	vector<vector<long long>> megoldas = UtakSzama(sor, oszlop, bitmatrix);

	kiir(megoldas);
	return 0;
}