/*Boda Norbert
511-es csoport
Lab6/01
Adott egy 𝑛 × 𝑚-es mátrix. Határozzuk meg azt a legnagyobb 𝑛 elemű
összeget, amelyet úgy kapunk meg, hogy minden elem a mátrix különböző
soraiból “származik” és az 𝑖. sorból kiválasztott elem kisebb mint az 𝑖+ 1. sorból
kiválasztott elem.*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void beolvas(short& sor, short& oszlop, vector<vector<int>>& szamok) {
	cin >> sor >> oszlop;
	szamok.resize(sor, vector<int>(oszlop));
	for (short i = 0; i < sor; i++) {
		for (short j = 0; j < oszlop; j++) {
			cin >> szamok[i][j];
		}
	}
}

//megkeresi az utolso sor maximummat
int maximum_kereses(short sor, short& oszlop, vector<vector<int>>& szamok) {
	int maximum = szamok[sor][0];
	for (short j = 0; j < oszlop; j++) {
		if (szamok[sor][j] > maximum) {
			maximum = szamok[sor][j];
		}
	}
	return maximum;
}

//megkeresi a megadott sor maximumat, amelyik kisebb kell legyen, mint az utani levo sor maximuma
int kisebb_maximum_kereses(short sor, short& oszlop, vector<vector<int>>& szamok, bool& letezik, int legnagyobb) {
	short j = 0;
	int maximum = szamok[sor][0];
	while (maximum >= legnagyobb && j < oszlop) {
		maximum = szamok[sor][j];
		j++;
	}
	if (j == oszlop) {
		//ha nem talalt kisebb maximumot akkor egy bool valtozo segitsegevel megadja, hogy nem letezik
		if (maximum >= legnagyobb) {
			letezik = false;
			return 0;
		}
		//ha a maximum a sor utolso eleme akkor visszaterite
		else {
			return maximum;
		}
	}
	//ha az elozo ciklus utan a j!=oszlop, akkor vegig megy a sor tobbi elemen is
	while(j < oszlop) {
		if (szamok[sor][j] > maximum && szamok[sor][j] < legnagyobb) {
			maximum = szamok[sor][j];
		}
		j++;
	}
	return maximum;
}

void osszeg_szamitas(short& sor, short& oszlop, vector<vector<int>>& szamok, long long& megoldas, bool& letezik) {
	//megkeresi az utolso sor legnagyobb elemet es hozzaadja az osszeghez
	int maximum = maximum_kereses(sor - 1, oszlop, szamok);
	megoldas += maximum;
	short i = sor - 2;
	//megkeresi az osszes sor maximumat, illetve ha nem letezik, akkor a megfelelo bool valtozot atallitja
	while (i >= 0 && letezik) {
		maximum = kisebb_maximum_kereses(i, oszlop, szamok, letezik, maximum);
		megoldas += maximum;
		i--;
	}
}

void kiir(long long& megoldas, bool& letezik) {
	if (letezik) {
		cout << megoldas;
	}
	else {
		cout << " nincs megoldas";
	}
}

int main() {
	short sor, oszlop;
	vector<vector<int>> szamok;
	beolvas(sor, oszlop, szamok);
	
	long long megoldas = 0;
	bool letezik = true;
	osszeg_szamitas(sor, oszlop, szamok, megoldas, letezik);

	kiir(megoldas, letezik);
	return 0;
}