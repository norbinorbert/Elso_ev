//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

void beolvas(int&, int&, vector<vector<int>>&);
void paros_graf(vector<vector<int>>&);
void halmazok_felepitese(queue<pair<int, bool>>&, vector<int>&, vector<int>&, vector<bool>&, vector<vector<int>>&);
bool nincs_el(vector<vector<int>>&, vector<int>&);

int main() {
	int csomopontok_szama, elek_szama;
	vector<vector<int>> szomszedsagi_lista;
	beolvas(csomopontok_szama, elek_szama, szomszedsagi_lista);

	paros_graf(szomszedsagi_lista);
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

//szelessegi bejarast vegez, majd meghatarozza ha a graf paros vagy nem
void paros_graf(vector<vector<int>>& szomszedsagi_lista) {
	vector<int> elso_halmaz, masodik_halmaz;
	vector<bool> volt(szomszedsagi_lista.size(), false);
	queue<pair<int, bool>> q;
	for (int i = 1; i < szomszedsagi_lista.size(); i++) {
		if (!volt[i]) {
			//true az elso halmaz, false a masodik
			q.push({ i, true });
			volt[i] = true;
			halmazok_felepitese(q, elso_halmaz, masodik_halmaz, volt, szomszedsagi_lista);
		}
	}

	if (nincs_el(szomszedsagi_lista, elso_halmaz) && nincs_el(szomszedsagi_lista, masodik_halmaz)) {
		cout << "igen";
	}
	else {
		cout << "nem";
	}
	cout << endl;
}

//queue kezelese, illetve csomopontok elosztasa
void halmazok_felepitese(queue<pair<int, bool>>& q, vector<int>& elso_halmaz, vector<int>& masodik_halmaz, vector<bool>& volt, vector<vector<int>>& szomszedsagi_lista){
	while (!q.empty()) {
		pair<int, bool> csomopont = q.front();
		q.pop();
		//a szelessegi bejaras soran ket halmazba osztja a csomopontokat, mindegyik csomopont egy kulonbozo halmazba kerul, mint a szomszedja
		if (csomopont.second) {
			elso_halmaz.push_back(csomopont.first);
		}
		else {
			masodik_halmaz.push_back(csomopont.first);
		}
		for (int j = 1; j < szomszedsagi_lista[csomopont.first].size(); j++) {
			if (!volt[szomszedsagi_lista[csomopont.first][j]]) {
				q.push({ szomszedsagi_lista[csomopont.first][j], !csomopont.second });
			}
			volt[szomszedsagi_lista[csomopont.first][j]] = true;
		}
	}
}

//ellenorzi, ha a halmazokban levo csomopontok kozott van-e el
bool nincs_el(vector<vector<int>>& szomszedsagi_lista, vector<int>& halmaz) {
	for (int i = 0; i < halmaz.size(); i++) {
		vector<bool> szomszed(szomszedsagi_lista.size(), false);
		for (int j = 1; j < szomszedsagi_lista[halmaz[i]].size(); j++) {
			szomszed[szomszedsagi_lista[halmaz[i]][j]] = true;
		}
		for (int j = i + 1; j < halmaz.size(); j++) {
			if (szomszed[halmaz[j]]) {
				return false;
			}
		}
	}
	return true;
}