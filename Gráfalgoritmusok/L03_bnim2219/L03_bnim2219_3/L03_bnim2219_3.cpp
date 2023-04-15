//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

void beolvas(int&, int&, vector<vector<int>>&);
void StrongConnect(int, int, vector<vector<int>>&);
void DFS_SCC(int, int&, vector<int>&, vector<int>&, vector<bool>&, vector<vector<int>>&, int&, stack<int>&, vector<vector<int>>&, vector<bool>&);
void kiir(vector<vector<int>>&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	StrongConnect(csomopontok_szama, elek_szama, szomszedsagi_lista);

	return 0;
}

//file-bol beolvassa az eleket es egy szomszedsagi listat epit fel
void beolvas(int& csomopontok_szama, int& elek_szama, vector<vector<int>>& szomszedsagi_lista) {
	ifstream fin("graf.in");
	fin >> csomopontok_szama >> elek_szama;
	szomszedsagi_lista.resize(csomopontok_szama + 1, vector<int>(1, 0));
	for (int i = 0; i < elek_szama; i++) {
		int kezdopont, vegpont;
		fin >> kezdopont >> vegpont;
		szomszedsagi_lista[kezdopont].push_back(vegpont);
	}
	fin.close();
}

//seged tombok inicializalasa es a rekurziv fuggveny meghivasa minden csomopontra
void StrongConnect(int csomopontok_szama, int elek_szama, vector<vector<int>>& szomszedsagi_lista) {
	int ido = 0, komponensek_index = -1;
	vector<int> belep(csomopontok_szama + 1, -1);
	vector<int> low(csomopontok_szama + 1, -1);
	vector<bool> vermen(csomopontok_szama + 1, false);
	vector<vector<int>> komponensek;
	stack<int> verem;
	vector<bool> volt(csomopontok_szama + 1, false);
	for (int i = 1; i <= csomopontok_szama; i++) {
		if (!volt[i]) {
			DFS_SCC(i, ido, belep, low, vermen, komponensek, komponensek_index, verem, szomszedsagi_lista, volt);
		}
	}
	kiir(komponensek);
}

//az algoritmus rekurziv resze
void DFS_SCC(int csomopont, int& ido, vector<int>& belep, vector<int>& low, vector<bool>& vermen, vector<vector<int>>& komponensek, 
	int& komponensek_index, stack<int>& verem, vector<vector<int>>& szomszedsagi_lista, vector<bool>& volt) {
	ido++;
	belep[csomopont] = ido;
	low[csomopont] = ido;
	vermen[csomopont] = true;
	verem.push(csomopont);
	volt[csomopont] = true;
	for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
		int szomszed = szomszedsagi_lista[csomopont][i];
		if (belep[szomszed] == -1) {
			DFS_SCC(szomszed, ido, belep, low, vermen, komponensek, komponensek_index, verem, szomszedsagi_lista, volt);
			low[csomopont] = min(low[csomopont], low[szomszed]);
		}
		else if (belep[szomszed] < belep[csomopont] && vermen[szomszed]) {
			low[csomopont] = min(low[csomopont], low[szomszed]);
		}
	}
	if (low[csomopont] == belep[csomopont]) {
		komponensek_index++;
		komponensek.resize(komponensek.size() + 1);
		while (!verem.empty() && belep[verem.top()] >= belep[csomopont]) {
			komponensek[komponensek_index].push_back(verem.top());
			vermen[verem.top()] = false;
			verem.pop();
		}
	}
}

//fileba kiirja az osszefuggo komponenseket
void kiir(vector<vector<int>>& komponensek) {
	ofstream fout("graf.out");
	for (int i = 0; i < komponensek.size(); i++) {
		for (int j = 0; j < komponensek[i].size(); j++) {
			fout << komponensek[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();
}