/*Boda Norbert
511-es csoport
Lab7/03
Határozzuk meg oszd meg és uralkodj módszerrel egy 𝑛 elemű sorozat többségi
elemét, ha létezik ilyen, anélkül, hogy rendeznénk azt!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& elemek_szama, vector<int>& elemek) {
	cin >> elemek_szama;
	elemek.resize(elemek_szama);
	for (int i = 0; i < elemek_szama; i++) {
		cin >> elemek[i];
	}
}

int keres_tobbsegi_elem(vector<int>& elemek, int bal, int jobb) {
	if (bal == jobb) {
		return elemek[bal];
	}
	if (jobb - bal == 1) {
		if (elemek[bal] == elemek[jobb]) {
			return elemek[bal];
		}
		else {
			return -1;
		}
	}
	int kozep = (bal + jobb) / 2;
	int bal_tobbsegi = keres_tobbsegi_elem(elemek, bal, kozep);
	int jobb_tobbsegi = keres_tobbsegi_elem(elemek, kozep + 1, jobb);
	if (bal_tobbsegi == jobb_tobbsegi) {
		return bal_tobbsegi;
	}
	else {
		int szamlalo_bal = 0, szamlalo_jobb = 0;
		for (int i = bal; i <= jobb; i++) {
			if (elemek[i] == bal_tobbsegi) {
				szamlalo_bal++;
			}
			if (elemek[i] == jobb_tobbsegi) {
				szamlalo_jobb++;
			}
		}
		if (szamlalo_bal >= ((jobb + 1 - bal) / 2 + 1)) {
			return bal_tobbsegi;
		}
		if (szamlalo_jobb >= ((jobb + 1 - bal) / 2 + 1)) {
			return jobb_tobbsegi;
		}
		return -1;
	}
}

void kiir(int& tobbsegi_elem) {
	cout << tobbsegi_elem;
}

int main() {
	int elemek_szama;
	vector<int> elemek;
	beolvas(elemek_szama, elemek);

	int tobbsegi_elem = keres_tobbsegi_elem(elemek, 0, elemek.size() - 1);

	kiir(tobbsegi_elem);

	return 0;
}