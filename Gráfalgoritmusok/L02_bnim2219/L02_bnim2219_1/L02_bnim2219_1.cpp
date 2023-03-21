//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

void beolvas(int&, int&, vector<vector<int>>&);
void DFS(vector<vector<int>>&);
void DFS_visit(vector<vector<int>>&, int csomopont, vector<bool>&);
void BFS(vector<vector<int>>&);
void queue_vizsgalas(queue<int>&, vector<bool>&, vector<vector<int>>&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);
	
	DFS(szomszedsagi_lista);

	BFS(szomszedsagi_lista);
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
		szomszedsagi_lista[vegpont].push_back(kezdopont);
	}
}

//melysegi bejaras
void DFS(vector<vector<int>>& szomszedsagi_lista) {
	vector<bool> volt(szomszedsagi_lista.size(), false);
	cout << "Melysegi bejaras: ";
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		if (!volt[i]) {
			volt[i] = true;
			DFS_visit(szomszedsagi_lista, i, volt);
		}
	}
	cout << endl;
}

//melysegi bejaras rekurziv resze
void DFS_visit(vector<vector<int>>& szomszedsagi_lista, int csomopont, vector<bool>& volt) {
	cout << csomopont << " ";
	for (int i = 1; i < szomszedsagi_lista[csomopont].size(); i++) {
		if (!volt[szomszedsagi_lista[csomopont][i]]) {
			volt[szomszedsagi_lista[csomopont][i]] = true;
			DFS_visit(szomszedsagi_lista, szomszedsagi_lista[csomopont][i], volt);
		}
	}
}

//szelessegi bejaras
void BFS(vector<vector<int>>& szomszedsagi_lista) {
	cout << "Szelessegi bejaras: ";
	vector<bool> volt(szomszedsagi_lista.size(), false);
	queue<int> q;
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		if (!volt[i]) {
			q.push(i);
			volt[i] = true;
			queue_vizsgalas(q, volt, szomszedsagi_lista);
		}
	}
	cout << endl;
}

//a queue-ban levo csomopontokon megy vegig amig nem lesz ures, illetve uj csomopontokat rak be ha szukseges
void queue_vizsgalas(queue<int>& q, vector<bool>& volt, vector<vector<int>>& szomszedsagi_lista) {
	while (!q.empty()) {
		int csomopont = q.front();
		q.pop();
		cout << csomopont << " ";
		for (int j = 1; j < szomszedsagi_lista[csomopont].size(); j++) {
			if (!volt[szomszedsagi_lista[csomopont][j]]) {
				q.push(szomszedsagi_lista[csomopont][j]);
			}
			volt[szomszedsagi_lista[csomopont][j]] = true;
		}
	}
}