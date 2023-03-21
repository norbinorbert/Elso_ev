//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void beolvas(int&, int&, vector<vector<int>>&);
bool DFS(vector<vector<int>>&);
void DFS_visit(vector<vector<int>>&, int csomopont, vector<short>&, bool&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	if (DFS(szomszedsagi_lista)) {
		cout << "igen";
	}
	else {
		cout << "nem";
	}

	return 0;
}

//file-bol beolvassa az eleket es egy szomszedsagi listat epit fel
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

//melysegi bejaras, illetve visszateriti ha van vagy nincs kor a grafban
bool DFS(vector<vector<int>>& szomszedsagi_lista) {
	vector<short> allapot(szomszedsagi_lista.size(), 0);
	bool kor = false;
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		if (allapot[i] == 0) {
			DFS_visit(szomszedsagi_lista, i, allapot, kor);
		}
		if (kor) {
			return true;
		}
	}
	return false;
}

//melysegi bejaras rekurziv resze, itt hatarozza meg ha van kor a grafban
void DFS_visit(vector<vector<int>>& szomszedsagi_lista, int csomopont, vector<short>& allapot, bool& kor) {
	allapot[csomopont] = 1;
	for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
		//ha egy csomopont mar feldolgozas alatt van es ujbol elerunk hozza akkor biztos, hogy kor van a grafban
		if (allapot[szomszedsagi_lista[csomopont][i]] == 1) {
			kor = true;
		}
		if (allapot[szomszedsagi_lista[csomopont][i]] == 0) {
			DFS_visit(szomszedsagi_lista, szomszedsagi_lista[csomopont][i], allapot, kor);
		}
	}
	allapot[csomopont] = 2;
}