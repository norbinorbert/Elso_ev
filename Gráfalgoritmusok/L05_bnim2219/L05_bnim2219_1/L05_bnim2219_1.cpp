//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>

using namespace std;

void beolvas(int&, int&, int&, vector<vector<int>>&);
bool BFS(vector<int>&, int, int, vector<vector<int>>&);
void Edmonds_Karp(vector<vector<int>>&, int, int);
void kiir(int, vector<vector<int>>&, int, int);

int main() {
	int csomopontok_szama, forras, nyelo;
	vector<vector<int>> szomszedsagi_matrix;
	beolvas(csomopontok_szama, forras, nyelo, szomszedsagi_matrix);

	Edmonds_Karp(szomszedsagi_matrix, forras, nyelo);
	return 0;
}

void beolvas(int& csomopontok_szama, int& forras, int& nyelo, vector<vector<int>>& szomszedsagi_matrix) {
	ifstream fin("1_be.txt");
	fin >> csomopontok_szama >> forras >> nyelo;
	int kezdopont, vegpont, suly;
	szomszedsagi_matrix.resize(csomopontok_szama + 1, vector<int>(csomopontok_szama + 1, 0));
	while(fin >> kezdopont >> vegpont >> suly) {
		szomszedsagi_matrix[kezdopont][vegpont] = suly;
	}
	fin.close();
}

 bool BFS(vector<int>& szulo, int forras, int nyelo, vector<vector<int>>& szomszedsagi_matrix) {
	vector<bool> volt(szomszedsagi_matrix.size(), false);
	queue<int> q;
	q.push(forras);
	volt[forras] = true;
	while (!q.empty()) {
		int csomopont = q.front();
		q.pop();
		for (int szomszed = 1; szomszed < szomszedsagi_matrix[csomopont].size(); szomszed++) {
			if (szomszedsagi_matrix[csomopont][szomszed] != 0 && !volt[szomszed]) {
				q.push(szomszed);
				szulo[szomszed] = csomopont;
				volt[szomszed] = true;
			}
		}
	}
	return volt[nyelo];
}

 void Edmonds_Karp(vector<vector<int>>& szomszedsagi_matrix, int forras, int nyelo) {
	 int max_folyam = 0;
	 vector<int> szulo(szomszedsagi_matrix.size(), -1);
	 vector<vector<int>> rezidualis = szomszedsagi_matrix;
	 while (BFS(szulo, forras, nyelo, rezidualis)) {
		 int u, v;
		 int resz_folyam = INT_MAX;
		 v = nyelo;
		 while (v != forras) {
			 u = szulo[v];
			 resz_folyam = min(resz_folyam, rezidualis[u][v]);
			 v = szulo[v];
		 }
		 v = nyelo;
		 while (v != forras) {
			 u = szulo[v];
			 rezidualis[u][v] -= resz_folyam;
			 rezidualis[v][u] += resz_folyam;
			 v = szulo[v];
		 }
		 max_folyam += resz_folyam;
	 }
	 kiir(max_folyam, rezidualis, forras, nyelo);
 }

 void kiir(int max_folyam, vector<vector<int>>& rezidualis, int forras, int nyelo) {
	 ofstream fout("1_ki.txt");
	 fout << max_folyam << endl;
	 vector<bool> volt(rezidualis.size(), false);
	 queue<int> q;
	 q.push(forras);
	 volt[forras] = true;
	 while (!q.empty()) {
		 int csomopont = q.front();
		 fout << csomopont << " ";
		 q.pop();
		 for (int szomszed = 1; szomszed < rezidualis[csomopont].size(); szomszed++) {
			 if (rezidualis[csomopont][szomszed] != 0 && !volt[szomszed]) {
				 q.push(szomszed);
				 volt[szomszed] = true;
			 }
		 }
	 }
	 fout << "; ";
	 for (int i = 1; i < volt.size(); i++) {
		 if (!volt[i]) {
			 fout << i << " ";
		 }
	 }
	 fout.close();
 }