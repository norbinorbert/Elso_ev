//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

void beolvas(int&, int&, vector<vector<pair<int, int>>>&);
void Johnson(int, int, vector<vector<pair<int, int>>>&);
void uj_csomopont_hozzaadasa(int, vector<vector<pair<int, int>>>&);
vector<long long> Bellman_Ford(int, int, int, vector<vector<pair<int, int>>>&);
void ujrasulyozas(vector<vector<pair<int, int>>>&, vector<long long>&);
void Dijkstra(int, int, int, vector<vector<pair<int, int>>>&, ofstream&, vector<long long>&);
void ujrasulyozas(int kezdo, vector<int>& u, vector<long long>& h);
void kiir(vector<int>&, vector<int>&, int, ofstream&);
void kiir_rekurziv(int, vector<int>&, vector<int>&, ofstream&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<pair<int, int>>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	Johnson(csomopontok_szama, elek_szama, szomszedsagi_lista);
	return 0;
}

//file-bol beolvassa az eleket es felepit egy szomszedsagi listat
void beolvas(int& csomopontok_szama, int& elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	ifstream fin("graf.in");
	fin >> csomopontok_szama >> elek_szama;
	szomszedsagi_lista.resize(csomopontok_szama + 1, vector<pair<int, int>>(1, { 0, 0 }));
	for (int i = 0; i < elek_szama; i++) {
		int kezdopont, vegpont, suly;
		fin >> kezdopont >> vegpont >> suly;
		szomszedsagi_lista[kezdopont].push_back({ vegpont, suly });
	}
	fin.close();
}

void Johnson(int csomopontok_szama, int elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	ofstream fout("graf.out");
	uj_csomopont_hozzaadasa(csomopontok_szama, szomszedsagi_lista);
	vector<long long> extra_tavolsag = Bellman_Ford(csomopontok_szama, elek_szama, 0, szomszedsagi_lista);
	for (int i = 1; i <= csomopontok_szama; i++) {
		Dijkstra(csomopontok_szama, elek_szama, i, szomszedsagi_lista, fout, extra_tavolsag);
	}
	fout.close();
}

//hozzaad egy uj csomopontot a grafhoz, ami minden masik csomoponthoz kapcsolodik 0 sullyal
void uj_csomopont_hozzaadasa(int csomopontok_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	szomszedsagi_lista[0].resize(csomopontok_szama + 1, { 0, 0 });
	for (int i = 1; i < szomszedsagi_lista[0].size(); i++) {
		szomszedsagi_lista[0][i].first = i;
	}
}

vector<long long> Bellman_Ford(int csomopontok_szama, int elek_szama, int kiindulasi_pont, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	//a tavolsagok a kivalasztott elek sulyai lesznek
	vector<long long> extra_tavolsag(csomopontok_szama + 1, INT_MAX);

	extra_tavolsag[kiindulasi_pont] = 0;

	//csomopontok szama - 1 alkalommal frissiti a megfelelo informaciokat
	for (int k = 1; k < csomopontok_szama; k++) {
		//bejarja a szomszedsagi listat, ami az osszes elt tartalmazza
		for (int i = 0; i < szomszedsagi_lista.size(); i++) {
			for (int j = 1; j < szomszedsagi_lista[i].size(); j++) {
				int csomopont = i;
				int szomszedos_csomopont = szomszedsagi_lista[i][j].first;
				int suly = szomszedsagi_lista[i][j].second;
				if (suly + extra_tavolsag[csomopont] < extra_tavolsag[szomszedos_csomopont]) {
					extra_tavolsag[szomszedos_csomopont] = suly + extra_tavolsag[csomopont];
				}
			}
		}
	}
	ujrasulyozas(szomszedsagi_lista, extra_tavolsag);
	return extra_tavolsag;
}

//ujrasulyozza az eleket, ahogy a Johnson algoritmusban elo van irva
void ujrasulyozas(vector<vector<pair<int, int>>>& szomszedsagi_lista, vector<long long>& tavolsag) {
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		for (int j = 1; j < szomszedsagi_lista[i].size(); j++) {
			szomszedsagi_lista[i][j].second = szomszedsagi_lista[i][j].second + tavolsag[i] - tavolsag[szomszedsagi_lista[i][j].first];
		}
	}
}

void Dijkstra(int csomopontok_szama, int elek_szama, int kiindulasi_pont, vector<vector<pair<int, int>>>& szomszedsagi_lista, ofstream& fout, vector<long long>& extra_tavolsag) {
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
				elek.push({ -(tavolsag[szomszedos_csomopont]), szomszedos_csomopont });
			}
		}
	}
	ujrasulyozas(kiindulasi_pont, tavolsag, extra_tavolsag);
	kiir(szulok, tavolsag, kiindulasi_pont, fout);
}

//Dijkstra utan ujbol ujrasulyozza a tavolsagokat, hogy az eredeti graf tavolsagait kapjuk meg
void ujrasulyozas(int kiindulasi_pont, vector<int>& tavolsag, vector<long long>& extra_tavolsag) {
	for (int i = 1; i < tavolsag.size(); i++) {
		tavolsag[i] = tavolsag[i] + extra_tavolsag[i] - extra_tavolsag[kiindulasi_pont];
	}
}

void kiir(vector<int>& szulok, vector<int>& tavolsag, int kiindulasi_pont, ofstream& fout) {
	for (int i = 1; i < szulok.size(); i++) {
		if (szulok[i] != -1) {
			fout << "A legrovidebb ut hossza " << kiindulasi_pont << "-bol " << i << "-ba: " << tavolsag[i] << endl;
			fout << "A legrovidebb ut " << kiindulasi_pont << "-bol " << i << "-ba: " << kiindulasi_pont << " ";
			kiir_rekurziv(i, szulok, tavolsag, fout);
			fout << endl;
		}
		else {
			if (i != kiindulasi_pont) {
				fout << "A legrovidebb ut hossza " << kiindulasi_pont << "-bol " << i << "-ba: " << "nem elerheto" << endl;
				fout << "A legrovidebb ut " << kiindulasi_pont << "-bol " << i << "-ba: " << "nem elerheto" << endl;
			}
		}
	}
}

//kiirja az utat
void kiir_rekurziv(int csomopont, vector<int>& szulok, vector<int>& tavolsag, ofstream& fout) {
	if (szulok[csomopont] != -1) {
		kiir_rekurziv(szulok[csomopont], szulok, tavolsag, fout);
		fout << csomopont << " ";
	}
}