/*Boda Norbert
511-es csoport
Lab6/09
Egy online áruház 𝑛 terméket kínál eladásra és mindegyikre ismert a profit
mely az eladásából származik és a határidő, ameddig el lehet adni. Mivel az
áruháznak nagyon kevés alkalmazottja van, egy napon csak egy terméket tud
eladni. Határozzuk meg a maximális profitot amire az áruház szert tehet!*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(short& termekek_szama, vector<pair<short, short>>& termekek) {
	cin >> termekek_szama;
	termekek.resize(termekek_szama+1);
	termekek[0] = { 10001, 10001 };
	for (short i = 1; i <= termekek_szama; i++) {
		cin >> termekek[i].first >> termekek[i].second;
	}
}

short keres_hatarido(vector<pair<short, short>>& termekek) {
	short legkesobbi = termekek[1].second;
	for (short i = 1; i < termekek.size(); i++) {
		if (legkesobbi < termekek[i].second) {
			legkesobbi = termekek[i].second;
		}
	}
	return legkesobbi;
}

bool csokkeno(pair<short, short>& elso, pair<short, short>& masodik) {
	if (elso.first == masodik.first) {
		return (elso.second > masodik.second);
	}
	return (elso.first > masodik.first);
}

unsigned long long profit_szamolas(vector<pair<short, short>>& termekek) {
	if (termekek.size() == 1) {
		return 0;
	}
	sort(termekek.begin(), termekek.end(), csokkeno);
	short legkesobbi_hatarido = keres_hatarido(termekek);
	unsigned long long profit = 0;
	vector<short> profitok(legkesobbi_hatarido + 1, 0);
	for (short i = 1; i < termekek.size(); i++) {
		if (profitok[termekek[i].second] == 0) {
			profitok[termekek[i].second] = termekek[i].first;
		}
		else {
			short j = termekek[i].second;
			while (j >= 1 && profitok[j] != 0) {
				j--;
			}
			if (j > 0) {
				profitok[j] = termekek[i].first;
			}
		}
	}

	for (short i = 1; i < profitok.size(); i++) {
		profit += profitok[i];
	}

	return profit;
}

void kiir(unsigned long long& profit) {
	cout << profit;
}

int main() {
	short termekek_szama;
	vector<pair<short, short>> termekek;
	beolvas(termekek_szama, termekek);

	unsigned long long profit = profit_szamolas(termekek);

	kiir(profit);
	return 0;
}