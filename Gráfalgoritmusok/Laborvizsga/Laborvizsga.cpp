//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <queue>

using namespace std;

struct Elek {
	int u, v, suly;
};

void beolvas(int&, int&, vector<vector<int>>&);
void atalakit(int, int, vector<vector<int>>&, vector<vector<int>>&);
void matrix_kiir(vector<vector<int>>&);
void legnepszerubb(vector<vector<int>>&);
void feszitofa(vector<vector<int>>&);
void nincs_barat(vector<vector<int>>&);
void legrovidebb_ut(int, vector<vector<int>>&);
void kiir(int, vector<long long>&, vector<int>&);
void kiir_szulok(int, vector<int>&);

int main() {
	int szemelyek_szama, elek_szama;
	vector<vector<int>> incidencia_matrix;
	beolvas(szemelyek_szama, elek_szama, incidencia_matrix);

	vector<vector<int>> szomszedsagi_matrix(szemelyek_szama + 1, vector<int>(szemelyek_szama + 1, 0));
	atalakit(szemelyek_szama, elek_szama, incidencia_matrix, szomszedsagi_matrix);
	cout << "Szomszedsagi matrix:" << endl;
	matrix_kiir(szomszedsagi_matrix);

	legnepszerubb(szomszedsagi_matrix);

	feszitofa(szomszedsagi_matrix);

	nincs_barat(incidencia_matrix);

	int forras = 1;
	legrovidebb_ut(forras, szomszedsagi_matrix);
	return 0;
}

void beolvas(int& szemelyek_szama, int& elek_szama, vector<vector<int>>& incidencia_matrix) {
	ifstream fin("stranger.txt");
	fin >> szemelyek_szama >> elek_szama;
	incidencia_matrix.resize(szemelyek_szama + 1, vector<int>(elek_szama + 1, 0));
	for (int i = 1; i <= szemelyek_szama; i++) {
		for (int j = 1; j <= elek_szama; j++) {
			fin >> incidencia_matrix[i][j];
		}
	}
	fin.close();
}

void atalakit(int szemelyek_szama, int elek_szama, vector<vector<int>>& incidencia_matrix, vector<vector<int>>& szomszedsagi_matrix) {
	for (int i = 1; i <= elek_szama; i++) {
		int bemeno = 0, kimeno = 0, suly = 0;
		for (int j = 1; j <= szemelyek_szama; j++) {
			if (incidencia_matrix[j][i] == 1) {
				bemeno = j;
			}
			if (incidencia_matrix[j][i] != 1 && incidencia_matrix[j][i] != 0) {
				kimeno = j;
				suly = incidencia_matrix[j][i];
			}
		}
		szomszedsagi_matrix[bemeno][kimeno] = suly;
	}
}

void matrix_kiir(vector<vector<int>>& matrix) {
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = 1; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void legnepszerubb(vector<vector<int>>& szomszedsagi_matrix) {
	cout << "Legnepszerubb szemely: ";
	pair<int, int> legnepszerubb = { -1, -1 };
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		int fokszam = 0;
		for (int j = 1; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[j][i] != 0) {
				fokszam++;
			}
		}
		if (fokszam > legnepszerubb.first) {
			legnepszerubb.first = fokszam;
			legnepszerubb.second = i;
		}
	}
	cout << legnepszerubb.second << endl;
}

void feszitofa(vector<vector<int>>& szomszedsagi_matrix) {
	priority_queue<pair<int, int>> elek;
	vector<vector<int>> iranyitatlan_matrix(szomszedsagi_matrix.size(), vector<int>(szomszedsagi_matrix.size(), 0));
	for (int i = 1; i < iranyitatlan_matrix.size(); i++) {
		for (int j = 1; j < iranyitatlan_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] != 0) {
				iranyitatlan_matrix[i][j] = iranyitatlan_matrix[j][i] = szomszedsagi_matrix[i][j];
			}
		}
	}
	vector<int> szulo(iranyitatlan_matrix.size(), -1);
	vector<bool> volt(iranyitatlan_matrix.size(), false);
	int suly = 0;
	elek.push({ 0, 1 });
	while (!elek.empty()) {
		int csomopont = elek.top().second;
		if (volt[csomopont]) {
			elek.pop();
			continue;
		}
		volt[csomopont] = true;
		suly -= elek.top().first;
		elek.pop();

		for (int i = 1; i < iranyitatlan_matrix[csomopont].size(); i++) {
			if (iranyitatlan_matrix[csomopont][i] != 0 && !volt[i]) {
				elek.push({ -iranyitatlan_matrix[csomopont][i], i });
				szulo[i] = csomopont;
			}
		}
	}
	cout << "Minimalis feszitofa sulya: " << suly << endl;
	cout << "Minimalis feszitofa elei:" << endl;
	for (int i = 2; i < szulo.size(); i++) {
		cout << szulo[i] << " " << i << endl;
	}
}

void nincs_barat(vector<vector<int>>& incidencia_matrix) {
	cout << "Szemelyek, akiknek nincs baratjuk: ";
	for (int i = 1; i < incidencia_matrix.size(); i++) {
		int fokszam = 0;
		for (int j = 1; j < incidencia_matrix[i].size(); j++) {
			if (incidencia_matrix[i][j] != 0) {
				fokszam++;
			}
		}
		if (fokszam == 0) {
			cout << i << " ";
		}
	}
	cout << endl;
}

void legrovidebb_ut(int forras, vector<vector<int>>& szomszedsagi_matrix) {
	vector<Elek> elek;
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		for (int j = 1; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] != 0) {
				elek.push_back({ i, j, szomszedsagi_matrix[i][j] });
			}
		}
	}

	bool kor = false;
	vector<int> szulok(szomszedsagi_matrix.size(), -1);
	vector<long long> tavolsag(szomszedsagi_matrix.size(), INT_MAX);
	tavolsag[forras] = 0;

	for (int k = 1; k < szomszedsagi_matrix.size(); k++) {
		for (int i = 0; i < elek.size(); i++) {
			int csomopont = elek[i].u;
			int szomszedos_csomopont = elek[i].v;
			int suly = elek[i].suly;
			if (suly + tavolsag[csomopont] < tavolsag[szomszedos_csomopont]) {
				tavolsag[szomszedos_csomopont] = suly + tavolsag[csomopont];
				szulok[szomszedos_csomopont] = csomopont;
			}
		}
	}

	for (int i = 1; i < elek.size(); i++) {
		int csomopont = elek[i].u;
		int szomszedos_csomopont = elek[i].v;
		int suly = elek[i].suly;
		if (suly + tavolsag[csomopont] < tavolsag[szomszedos_csomopont]) {
			kor = true;
			break;
		}
	}
	if (kor) {
		cout << "Negativ kor volt talalva" << endl;
	}
	else {
		kiir(forras, tavolsag, szulok);
	}
}

void kiir(int forras, vector<long long>& tavolsag, vector<int>& szulok) {
	for (int i = 1; i < tavolsag.size(); i++) {
		if (i != forras) {
			cout << "Legrovidebb ut hossza " << forras << "-bol " << i << "-be: ";
			if (tavolsag[i] == INT_MAX) {
				cout << "nem elerheto";
			}
			else {
				cout << tavolsag[i];
				cout << " ||| A legrovidebb ut: ";
				kiir_szulok(i, szulok);
			}
		}
		cout << endl;
	}
}

void kiir_szulok(int forras, vector<int>& szulok) {
	if (szulok[forras] != -1) {
		kiir_szulok(szulok[forras], szulok);
		cout << szulok[forras] << " ";
	}
}