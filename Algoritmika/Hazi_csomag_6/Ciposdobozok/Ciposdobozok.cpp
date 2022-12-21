/*Boda Norbert
511-es csoport
Lab6/05
Adva van 𝑛+ 1 cipősdoboz és 𝑛 pár cipő, amelyek meg vannak számozva 1-től
𝑛-ig. Az 𝑛 pár cipő 𝑛 + 1 dobozban található, a dobozok közül az egyik üres. El
kell rendezni a cipőket úgy, hogy minden cipő a saját dobozába kerüljön és az üres
doboz a sor végére. Munka közben csak egy pár cipőt szabad kivenni a dobozból,
amelyben található, és azonnal be kell tenni az üres dobozba. Állapítsuk meg a
költöztetések sorozatát minimális számú művelettel.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& cipok_szama, vector<short>& dobozok) {
	cin >> cipok_szama;
	dobozok.resize(cipok_szama + 2);
	for (short i = 1; i < dobozok.size(); i++) {
		cin >> dobozok[i];
	}
}

//megnezi melyik doboz ures es visszateriti az indexet
short ures_doboz_index_kereses(vector<short>& dobozok) {
	short i = 0;
	while (i < dobozok.size()) {
		i++;
		if (dobozok[i] == 0) {
			return i;
		}
	}
	return i;
}

int ciposdobozok(vector<short>& dobozok) {
	int megoldas = 0;
	short ures_index = ures_doboz_index_kereses(dobozok);
	bool csere = false;
	short i = 0;
	bool rendezett;
	do {
		//ha az utolso doboz ures akkor vagy rendezettek a dobozok vagy oda kell helyezni egy cipot amelyik nincs a helyen
		if (ures_index == dobozok.size() - 1) {
			csere = false;
			i = 0;
			//az utolso dobozba beteszi az elso olyan cipot amelyik nincs a helyen
			while (!csere) {
				i++;
				if (i == dobozok.size() - 1) {
					return megoldas;
				}
				if (dobozok[i] != i) {
					swap(dobozok[i], dobozok[ures_index]);
					megoldas++;
					ures_index = i;
					csere = true;
				}
			}
		}

		rendezett = true;
		csere = false;
		i = 0;
		//addig cserelgeti a cipoket az ures es nem ures dobozok kozott ameddig az ures doboz az utolso nem lesz
		while (!csere) {
			i++;
			if (i == dobozok.size()) {
				break;
			}
			if (dobozok[i] != i && i != dobozok.size() - 1) {
				rendezett = false;
			}
			if (dobozok[i] == ures_index) {
				swap(dobozok[i], dobozok[ures_index]);
				megoldas++;
				ures_index = i;
				csere = true;
			}
		}
	} while (!rendezett);

	return megoldas;
}

void kiir(int& megoldas) {
	cout << megoldas;
}

int main() {
	short cipok_szama;
	vector<short> dobozok;
	beolvas(cipok_szama, dobozok);

	int megoldas = ciposdobozok(dobozok);

	kiir(megoldas);
	return 0;
}