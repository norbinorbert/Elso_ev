//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void beolvas(int&, int&, vector<vector<int>>&);
void DFS(vector<vector<int>>&);
void topologiai_rendezes(vector<pair<int, int>>&);
bool csokkeno(pair<int, int>, pair<int, int>);
void DFS_visit(vector<vector<int>>&, int csomopont, vector<pair<int, int>>&, int&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	DFS(szomszedsagi_lista);
	
	return 0;
}

//file-bol beolvassa az eleket es felepit egy szomszedsagi listat
void beolvas(int& csomopontok_szama, int& elek_szama, vector<vector<int>>& szomszedsagi_lista) {
	ifstream cin("graf.in");
	cin >> csomopontok_szama >> elek_szama;
	szomszedsagi_lista.resize(csomopontok_szama + 1, vector<int>(1, 0));
	for (int i = 0; i < elek_szama; i++) {
		int kezdopont, vegpont;
		cin >> kezdopont >> vegpont;
		szomszedsagi_lista[kezdopont].push_back(vegpont);
	}
}

//melysegi bejaras
void DFS(vector<vector<int>>& szomszedsagi_lista) {
	vector<pair<int, int>> allapot(szomszedsagi_lista.size(), { 0, 0 });
	int ido = 0;
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		if (allapot[i].first == 0) {
			DFS_visit(szomszedsagi_lista, i, allapot, ido);
		}
	}
	topologiai_rendezes(allapot);
}

//csokkeno sorrendben rendezi a csomopontokat a vegzesi idejuk szerint, ez lesz a topologiai sorrend
void topologiai_rendezes(vector<pair<int, int>>& allapot) {
	for (int i = 1; i < allapot.size(); i++) {
		allapot[i].second = i;
	}
	sort(allapot.begin() + 1, allapot.end(), csokkeno);
	for (int i = 1; i < allapot.size(); i++) {
		cout << allapot[i].second << " ";
	}
}

//seged fuggveny a rendezeshez
bool csokkeno(pair<int, int> a, pair<int, int> b) {
	return a.first > b.first;
}

//melysegi bejaras rekurziv resze, illetve meghatarozza, hogy mikor fejeztuk be egy csomopont vizsgalasat
void DFS_visit(vector<vector<int>>& szomszedsagi_lista, int csomopont, vector<pair<int, int>>& allapot, int& ido) {
	allapot[csomopont].first = 1;
	ido++;
	for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
		if (allapot[szomszedsagi_lista[csomopont][i]].first == 0) {
			DFS_visit(szomszedsagi_lista, szomszedsagi_lista[csomopont][i], allapot, ido);
		}
	}
	ido++;
	allapot[csomopont].first = ido;
}