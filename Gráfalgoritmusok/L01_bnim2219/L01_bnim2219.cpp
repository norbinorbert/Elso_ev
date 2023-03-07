/*Boda Norbert, 511-es csoport*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void felepit_szomszedsagi_matrix(int& csucsok_szama, int& elek_szama, vector<vector<int>>& szomszedsagi_matrix);
void kiir_matrix(vector<vector<int>>& szomszedsagi_matrix);
void felepit_incidencia_matrix(int csucsok_szama, int elek_szama, vector<vector<int>>& szomszedsagi_matrix, vector<vector<int>>& incidencia_matrix);
void felepit_szomszedsagi_lista(int csucsok_szama, int elek_szama, vector<vector<int>>& incidencia_matrix, vector<vector<pair<int, int>>>& szomszedsagi_lista);
void kiir_matrix(vector<vector<pair<int, int>>>& matrix);
void felepit_elek_listaja(int csucsok_szama, int elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista, vector<vector<int>>& elek_listaja);
void kiir_izolalt_csomopontok(vector<vector<int>>& szomszedsagi_matrix);
void kiir_vegpontok(vector<vector<int>>& incidencia_matrix);
void regularis_graf_vizsgalat(vector<vector<int>>& szomszedsagi_matrix);

int main() {
	int csucsok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_matrix;
	felepit_szomszedsagi_matrix(csucsok_szama, elek_szama, szomszedsagi_matrix);
	cout << "Szomszedsagi matrix: " << endl;
	kiir_matrix(szomszedsagi_matrix);

	vector<vector<int>> incidencia_matrix;
	felepit_incidencia_matrix(csucsok_szama, elek_szama, szomszedsagi_matrix, incidencia_matrix);
	cout << "Incidencia matrix: " << endl;
	kiir_matrix(incidencia_matrix);

	vector<vector<pair<int, int>>> szomszedsagi_lista;
	felepit_szomszedsagi_lista(csucsok_szama, elek_szama, incidencia_matrix, szomszedsagi_lista);
	cout << "Szomszedsagi lista: " << endl;
	kiir_matrix(szomszedsagi_lista);

	vector<vector<int>> elek_listaja;
	felepit_elek_listaja(csucsok_szama, elek_szama, szomszedsagi_lista, elek_listaja);
	cout << "Elek listaja: " << endl;
	kiir_matrix(elek_listaja);

	kiir_izolalt_csomopontok(szomszedsagi_matrix);
	
	kiir_vegpontok(incidencia_matrix);

	regularis_graf_vizsgalat(szomszedsagi_matrix);
	return 0;
}

//beolvassa a csucsok es elek szamat, illetve felepiti a szomszedsagi matrixot
void felepit_szomszedsagi_matrix(int& csucsok_szama, int& elek_szama, vector<vector<int>>& szomszedsagi_matrix) {
	ifstream cin("graf.in");
	cin >> csucsok_szama >> elek_szama;
	szomszedsagi_matrix.resize(csucsok_szama + 1, vector<int>(csucsok_szama + 1, 0));
	for (int i = 1; i <= elek_szama; i++) {
		int u, v, suly;
		cin >> u >> v >> suly;
		szomszedsagi_matrix[u][v] = suly;
		szomszedsagi_matrix[v][u] = suly;
	}
}

//kiir egy matrixot 1-tol indexelve
void kiir_matrix(vector<vector<int>>& matrix) {
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = 1; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//szomszedsagi matrix segitsegevel felepit egy incidencia matrixot
void felepit_incidencia_matrix(int csucsok_szama, int elek_szama, vector<vector<int>>& szomszedsagi_matrix, vector<vector<int>>& incidencia_matrix) {
	incidencia_matrix.resize(csucsok_szama + 1, vector<int>(elek_szama + 1, 0));
	int jelenlegi_el_index = 1;
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		for (int j = i; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] != 0) {
				//a matrix 0. soraban lesznek eltarolva az illeto elek sulyai
				incidencia_matrix[0][jelenlegi_el_index] = szomszedsagi_matrix[i][j];
				incidencia_matrix[i][jelenlegi_el_index]++;
				incidencia_matrix[j][jelenlegi_el_index]++;
				jelenlegi_el_index++;
			}
		}
	}
}

//incidencia matrix segitsegevel felepit egy szomszedsagi listat
void felepit_szomszedsagi_lista(int csucsok_szama, int elek_szama, vector<vector<int>>& incidencia_matrix, vector<vector<pair<int, int>>>& szomszedsagi_lista) {
	szomszedsagi_lista.resize(csucsok_szama + 1, vector<pair<int, int>>(1, { 0, 0 }));
	for (int j = 1; j <= elek_szama; j++) {
		int csomopont1 = 0, csomopont2 = 0;
		for (int i = 1; i <= csucsok_szama; i++) {
			if (incidencia_matrix[i][j] != 0) {
				if (csomopont2 == 0 && csomopont1 != 0) {
					csomopont2 = i;
				}
				if (csomopont1 == 0) {
					csomopont1 = i;
				}
			}
		}
		if (csomopont1 != 0 && csomopont2 != 0) {
			//a pair elso eleme a csomopont amivel szomszedos, a masodik elem pedig az el sulya ami osszekoti oket
			szomszedsagi_lista[csomopont1].push_back({ csomopont2, incidencia_matrix[0][j] });
			szomszedsagi_lista[csomopont2].push_back({ csomopont1, incidencia_matrix[0][j] });
		}
		else if (csomopont1 != 0 || csomopont2 != 0) {
			szomszedsagi_lista[max(csomopont1, csomopont2)].push_back({ max(csomopont1, csomopont2), incidencia_matrix[0][j] });
		}
	}
}

//ugyanaz, mint az elozo kiiras, csak mas a bemeneti adattipus
void kiir_matrix(vector<vector<pair<int, int>>>& matrix) {
	for (int i = 1; i < matrix.size(); i++) {
		cout << i << ": ";
		for (int j = 1; j < matrix[i].size(); j++) {
			cout << matrix[i][j].first << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//szomszedsagi lista segitsegevel felepiti az elek listajat
void felepit_elek_listaja(int csucsok_szama, int elek_szama, vector<vector<pair<int, int>>>& szomszedsagi_lista, vector<vector<int>>& elek_listaja) {
	elek_listaja.resize(elek_szama + 1, vector<int>(1, 0));
	int jelenlegi_el_sorszama = 1;
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		for (int j = 1; j < szomszedsagi_lista[i].size(); j++) {
			if (i <= szomszedsagi_lista[i][j].first) {
				elek_listaja[jelenlegi_el_sorszama].push_back(i);
				elek_listaja[jelenlegi_el_sorszama].push_back(szomszedsagi_lista[i][j].first);
				elek_listaja[jelenlegi_el_sorszama].push_back(szomszedsagi_lista[i][j].second);
				jelenlegi_el_sorszama++;
			}
		}
	}
}

//szomszedsagi matrix segitsegevel meghatarozza es kiirja az izolalt pontokat
void kiir_izolalt_csomopontok(vector<vector<int>>& szomszedsagi_matrix) {
	bool kiiras = false, szoveg = false;
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		int szamlalo = 0;
		for (int j = 1; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] != 0) {
				szamlalo++;
			}
		}
		if (szamlalo == 0) {
			if (!szoveg) {
				cout << "Izolalt csomopontok sorszama: ";
				szoveg = true;
			}
			cout << i << " ";
			kiiras = true;
		}
	}
	if (!kiiras) {
		cout << "Nincsenek izolalt pontok a grafban.";
	}
	cout << endl << endl;
}

//incidencia matrix segitsegevel meghatarozza es kiirja a vegpontokat
void kiir_vegpontok(vector<vector<int>>& incidencia_matrix) {
	vector<int> szamlalo(incidencia_matrix.size(), 0);
	for (int i = 1; i < incidencia_matrix.size(); i++) {
		for (int j = 1; j < incidencia_matrix[i].size(); j++) {
			szamlalo[i] += incidencia_matrix[i][j];
		}
	}
	bool kiiras = false, szoveg = false;
	for (int i = 1; i < szamlalo.size(); i++) {
		if (szamlalo[i] == 1) {
			if (!szoveg) {
				cout << "Vegpontok sorszama: ";
				szoveg = true;
			}
			cout << i << " ";
			kiiras = true;
		}
	}
	if (!kiiras) {
		cout << "Nincsenek vegpontok a grafban.";
	}
	cout << endl << endl;
}

//szomszedsagi matrix segitsegevel meghatarozza ha a graf regularis vagy sem
void regularis_graf_vizsgalat(vector<vector<int>>& szomszedsagi_matrix) {
	vector<int> szamlalo(szomszedsagi_matrix.size(), 0);
	for (int i = 1; i < szomszedsagi_matrix.size(); i++) {
		for (int j = i; j < szomszedsagi_matrix[i].size(); j++) {
			if (szomszedsagi_matrix[i][j] != 0) {
				szamlalo[i]++;
				szamlalo[j]++;
			}
		}
	}

	bool regularis = true;
	for (int i = 2; i < szamlalo.size(); i++) {
		if (szamlalo[i] != szamlalo[i - 1]) {
			regularis = false;
			break;
		}
	}

	if (regularis) {
		cout << "A graf " << szamlalo[1] << "-regularis." << endl;
	}
	else {
		cout << "A graf nem regularis." << endl;
	}
}