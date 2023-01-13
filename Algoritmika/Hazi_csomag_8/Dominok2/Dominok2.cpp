/*Boda Norbert
511-es csoport
Lab8/03
Adott 𝑛 dominó. Határozzuk meg a leghosszabb olyan sorozatot, mely
közvetlenül egymás után következő dominókból áll és betartja a dominó játék
szabályait. A dominókat el lehet forgatni 180 fokkal.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& dominok_szama, vector<pair<short, short>>& dominok) {
	cin >> dominok_szama;
	dominok.resize(dominok_szama);
	for (int i = 0; i < dominok_szama; i++) {
		cin >> dominok[i].first >> dominok[i].second;
	}
}

void felepit(vector<pair<short, short>>& dominok, vector<vector<int>>& hosszak) {
	hosszak[0][0] = 1;
	hosszak[1][0] = 1;
	for (int i = 1; i < dominok.size(); i++) {
		int hossz1 = 1, hossz2 = 1;
		if (dominok[i].first == dominok[i - 1].second) {
			hossz1 = hosszak[0][i - 1] + 1;
		}
		if (dominok[i].first == dominok[i - 1].first) {
			hossz2 = hosszak[1][i - 1] + 1;
		}
		hosszak[0][i] = max(hossz1, hossz2);

		hossz1 = 1, hossz2 = 1;
		if (dominok[i].second == dominok[i - 1].second) {
			hossz1 = hosszak[0][i - 1] + 1;
		}
		if (dominok[i].second == dominok[i - 1].first) {
			hossz2 = hosszak[1][i - 1] + 1;
		}
		hosszak[1][i] = max(hossz1, hossz2);
	}
}

int keres_max(vector<vector<int>>& hosszak) {
	int maximum = hosszak[0][0];
	for (int i = 0; i < hosszak.size(); i++) {
		for (int j = 0; j < hosszak[i].size(); j++) {
			if (maximum < hosszak[i][j]) {
				maximum = hosszak[i][j];
			}
		}
	}
	return maximum;
}

void kiir(vector<vector<int>>& hosszak) {
	int maximum = keres_max(hosszak);
	cout << maximum << endl;
}

int main() {
	int dominok_szama;
	vector<pair<short, short>> dominok;
	beolvas(dominok_szama, dominok);

	vector<vector<int>> hosszak(2, vector<int>(dominok_szama, 0));
	felepit(dominok, hosszak);

	kiir(hosszak);
	return 0;
}