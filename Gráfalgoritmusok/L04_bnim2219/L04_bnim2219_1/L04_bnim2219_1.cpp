//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

void beolvas(int&, int&, int&, vector<vector<pair<int, int>>>&);
void Dijkstra(int, int, int, vector<vector<pair<int, int>>>&);
void kiir(vector<int>&, vector<int>&, int);
void kiir_rekurziv(int, vector<int>&, vector<int>&, ofstream&);

int main() {
	int csomopontok_szama, elek_szama, kiindulasi_pont;
	vector<vector<pair<int, int>>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, kiindulasi_pont, szomszedsagi_lista);

	Dijkstra(csomopontok_szama, elek_szama, kiindulasi_pont, szomszedsagi_lista);
	return 0;
}

//file-bol beolvassa az eleket es felepit egy szomszedsagi listat
void beolvas(int& csomopontok_szama, int& elek_szama, int& kiindulasi_pont, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	ifstream fin("graf.in");
	fin >> csomopontok_szama >> elek_szama >> kiindulasi_pont;
	szomszedsagi_lista.resize(csomopontok_szama + 1, vector < pair<int, int>>(1, { 0, 0 }));
	for (int i = 0; i < elek_szama; i++) {
		int kezdopont, vegpont, suly;
		fin >> kezdopont >> vegpont >> suly;
		szomszedsagi_lista[kezdopont].push_back({ vegpont, suly });
	}
	fin.close();
}

void Dijkstra(int csomopontok_szama, int elek_szama, int kiindulasi_pont, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	priority_queue<pair<int, int>> elek;

	//eltarolja minden csomopont szulejet
	vector<int> szulok(csomopontok_szama + 1, -1);

	//a tavolsagok a kivalasztott elek sulyai lesznek
	vector<int> tavolsag(csomopontok_szama + 1, INT_MAX);

	vector<bool> volt(csomopontok_szama + 1, false);

	//a par elso eleme a tavolsag, masodik a csomopont
	elek.push({ 0, kiindulasi_pont });
	tavolsag[kiindulasi_pont] = 0;

	int kivalasztott_csomopontok_szama = 0;
	while (!elek.empty() && kivalasztott_csomopontok_szama < csomopontok_szama) {
		int csomopont = elek.top().second;
		if (volt[csomopont]) {
			elek.pop();
			continue;
		}
		kivalasztott_csomopontok_szama++;
		elek.pop();
		volt[csomopont] = true;
		//bejarja a jelenlegi csomopont szomszedait es frissiti az ezekhez tartozo adatokat
		for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
			int szomszedos_csomopont = szomszedsagi_lista[csomopont][i].first;
			int suly = szomszedsagi_lista[csomopont][i].second;
			if (!volt[szomszedos_csomopont] && suly + tavolsag[csomopont] < tavolsag[szomszedos_csomopont]) {
				tavolsag[szomszedos_csomopont] = suly + tavolsag[csomopont];
				szulok[szomszedos_csomopont] = csomopont;
				//az elsobbsegi sorba ellentetes elojellel teszi be a sulyokat, mert mindig a legnagyobb elemet veszi ki, nekunk pedig a legkisebb kell
				elek.push({ -(tavolsag[szomszedos_csomopont]), szomszedos_csomopont});
			}
		}
	}
	kiir(szulok, tavolsag, kiindulasi_pont);
}

void kiir(vector<int>& szulok, vector<int>& tavolsag, int kiindulasi_pont) {
	ofstream fout("graf.out");
	for (int i = 1; i < szulok.size(); i++) {
		if (szulok[i] != -1) {
			fout << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
			fout << "A legrovidebb ut " << i << "-ba: " << kiindulasi_pont << " ";
			kiir_rekurziv(i, szulok, tavolsag, fout);
			fout << endl;
		}
		else {
			if (i != kiindulasi_pont) {
				fout << "A legrovidebb ut hossza " << i << "-ba: " << "nem elerheto" << endl;
				fout << "A legrovidebb ut " << i << "-ba: " << "nem elerheto" << endl;
			}
		}
	}
	fout.close();
}

//kiirja az utat
void kiir_rekurziv(int csomopont, vector<int>& szulok, vector<int>& tavolsag, ofstream& fout) {
	if (szulok[csomopont] != -1) {
		kiir_rekurziv(szulok[csomopont], szulok, tavolsag, fout);
		fout << csomopont << " ";
	}
}