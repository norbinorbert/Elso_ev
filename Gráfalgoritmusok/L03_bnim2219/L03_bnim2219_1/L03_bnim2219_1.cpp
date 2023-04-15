//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

void beolvas(int&, int&, vector<vector<pair<int, int>>>&);
void Prim(int, int, vector<vector<pair<int, int>>>&);
void kiir(int, vector<int>&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<pair<int, int>>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	Prim(csomopontok_szama, elek_szama, szomszedsagi_lista);
	return 0;
}

//file-bol beolvassa az eleket es felepit egy szomszedsagi listat
void beolvas(int& csomopontok_szama, int& elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	ifstream fin("graf.in");
	fin >> csomopontok_szama >> elek_szama;
	szomszedsagi_lista.resize(csomopontok_szama + 1, vector < pair<int, int>>(1, { 0, 0 }));
	for (int i = 0; i < elek_szama; i++) {
		int kezdopont, vegpont, suly;
		fin >> kezdopont >> vegpont >> suly;
		szomszedsagi_lista[kezdopont].push_back({ vegpont, suly });
		szomszedsagi_lista[vegpont].push_back({ kezdopont, suly });
	}
	fin.close();
}

void Prim(int csomopontok_szama, int elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	int feszitofa_koltsege = 0;
	priority_queue<pair<int, int>> elek;

	//eltarolja minden csomopont szulejet a feszitofaban
	vector<int> szulok(csomopontok_szama + 1, -1);

	//a tavolsagok a kivalasztott elek sulyai lesznek
	vector<int> tavolsag_szulotol(csomopontok_szama + 1, INT_MAX);

	vector<bool> volt(csomopontok_szama + 1, false);

	//a par elso eleme a suly (a szulotol szamolt tavolsag), masodik a csomopont
	elek.push({ 0, 1 });
	tavolsag_szulotol[1] = 0;

	int kivalasztott_csomopontok_szama = 0;
	while (!elek.empty() && kivalasztott_csomopontok_szama < csomopontok_szama) {
		int csomopont = elek.top().second;
		if (volt[csomopont]) {
			elek.pop();
			continue;
		}
		kivalasztott_csomopontok_szama++;
		//mivel ellentetes elojellel voltak beteve a sulyok, ezert kivonast kell vegezni
		feszitofa_koltsege -= elek.top().first;
		elek.pop();
		volt[csomopont] = true;
		//bejarja a jelenlegi csomopont szomszedait es frissiti az ezekhez tartozo adatokat
		for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
			int szomszedos_csomopont = szomszedsagi_lista[csomopont][i].first;
			int suly = szomszedsagi_lista[csomopont][i].second;
			if (!volt[szomszedos_csomopont] && suly < tavolsag_szulotol[szomszedos_csomopont]) {
				tavolsag_szulotol[szomszedos_csomopont] = suly;
				szulok[szomszedos_csomopont] = csomopont;
				//az elsobbsegi sorba ellentetes elojellel teszi be a sulyokat, mert mindig a legnagyobb elemet veszi ki, nekunk pedig a legkisebb kell
				elek.push({ -suly, szomszedos_csomopont });
			}
		}
	}
	kiir(feszitofa_koltsege, szulok);
}

void kiir(int feszitofa_koltsege, vector<int>& szulok) {
	ofstream fout("graf.out");
	fout << feszitofa_koltsege << endl;
	for (int i = 1; i < szulok.size(); i++) {
		if (szulok[i] != -1) {
			fout << i << " " << szulok[i] << endl;
		}
	}
	fout.close();
}