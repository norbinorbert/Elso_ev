//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

void beolvas(int&, int&, int&, int&, vector<vector<long long>>&, vector<vector<long long>>&);
void Roy_Floyd_Warshall(int, vector<vector<long long>>&, vector<vector<long long>>&);
void kiir(vector<vector<long long>>&, vector<vector<long long>>&, int, int);

int main() {
	int csucsok_szama, elek_szama, kezdopont, vegpont;
	vector<vector<long long>> szomszedsagi_matrix, kovetkezo;
	beolvas(csucsok_szama, elek_szama, kezdopont, vegpont, szomszedsagi_matrix, kovetkezo);

	Roy_Floyd_Warshall(csucsok_szama, szomszedsagi_matrix, kovetkezo);

	kiir(szomszedsagi_matrix, kovetkezo, kezdopont, vegpont);
	return 0;
}

//beolvassa az eleket egy szomszedsagi matrixba, illetve inicializal egy "kovetkezo" matrixot, ami aminek egy [u][v] mezoje azt jelenti, hogy u-bol 
//melyik csomopontba kell menni a kovetkezo lepesben ahhoz, hogy vegul a v-be jusson el
void beolvas(int& csucsok_szama, int& elek_szama, int& kezdopont, int& vegpont, vector<vector<long long>>& szomszedsagi_matrix, vector<vector<long long>>& kovetkezo) {
	ifstream fin("graf.in");
	fin >> csucsok_szama >> elek_szama >> kezdopont >> vegpont;
	szomszedsagi_matrix.resize(csucsok_szama + 1, vector<long long>(csucsok_szama + 1, INT_MAX));
	kovetkezo.resize(csucsok_szama + 1, vector<long long>(csucsok_szama + 1, -1));
	for (int i = 1; i <= elek_szama; i++) {
		int u, v, suly;
		fin >> u >> v >> suly;
		szomszedsagi_matrix[u][v] = suly;
		kovetkezo[u][v] = v;
	}
	fin.close();
}

//az algoritmus egyszerre frissiti a szomszedsagi matrixot es a kovetkezo matrixot is
void Roy_Floyd_Warshall(int csucsok_szama, vector<vector<long long>>& szomszedsagi_matrix, vector<vector<long long>>& kovetkezo) {
	for (int k = 1; k <= csucsok_szama; k++) {
		for (int i = 1; i <= csucsok_szama; i++) {
			for (int j = 1; j <= csucsok_szama; j++) {
				if (i == j) {
					szomszedsagi_matrix[i][j] = 0;
				}
				if (szomszedsagi_matrix[i][j] > szomszedsagi_matrix[i][k] + szomszedsagi_matrix[k][j]) {
					szomszedsagi_matrix[i][j] = szomszedsagi_matrix[i][k] + szomszedsagi_matrix[k][j];
					kovetkezo[i][j] = kovetkezo[i][k];
				}
			}
		}
	}
}

//fileba kiirja a feladat altal kert adatokat (a valtoztatott szomszedsagi matrixot es a megadott ket csomopont kozott levo utat)
void kiir(vector<vector<long long>>& szomszedsagi_matrix, vector<vector<long long>>& kovetkezo, int kezdopont, int vegpont) {
	ofstream fout("graf.out");
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		for (int j = 1; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] == INT_MAX) {
				fout << "INF ";
			}
			else {
				fout << szomszedsagi_matrix[i][j] << " ";
			}
		}
		fout << endl;
	}
	fout << kezdopont << " ";
	while (kezdopont != vegpont) {
		kezdopont = kovetkezo[kezdopont][vegpont];
		fout << kezdopont << " ";
	}
	fout.close();
}