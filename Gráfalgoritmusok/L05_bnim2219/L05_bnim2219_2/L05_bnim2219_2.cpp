//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>

using namespace std;

struct csomopont {
	int magassag, folyam;
};

struct el {
	int u, v;
	int kapacitas, folyam;
};

void beolvas(int&, int&, int&, vector<el>&);
int pumpalo_emelo(int, int, vector<el>&, vector<csomopont>&);
void init(int, vector<el>&, vector<csomopont>&);
pair<int, int> lehet_pumpalni(int, int, vector<el>&, vector<csomopont>&);
void pumpalas(int, int, vector<el>&, vector<csomopont>&);
int lehet_emelni(int, int, vector<el>&, vector<csomopont>&);
void emeles(int, vector<el>&, vector<csomopont>&);

int main() {
	int csomopontok_szama, forras, nyelo;
	vector<el> elek;
	beolvas(csomopontok_szama, forras, nyelo, elek);

	vector<csomopont> csp(csomopontok_szama + 1, { 0, 0 });
	int max_folyam = pumpalo_emelo(forras, nyelo, elek, csp);

	ofstream fout("2_ki.txt");
	fout << max_folyam;
	fout.close();
	return 0;
}

void beolvas(int& csomopontok_szama, int& forras, int& nyelo, vector<el>& elek) {
	ifstream fin("2_be.txt");
	fin >> csomopontok_szama >> forras >> nyelo;
	int kezdopont, vegpont, suly;
	while (fin >> kezdopont >> vegpont >> suly) {
		el tmp;
		tmp.u = kezdopont;
		tmp.v = vegpont;
		tmp.kapacitas = suly;
		tmp.folyam = 0;
		elek.push_back(tmp);
	}
	fin.close();
}

int pumpalo_emelo(int forras, int nyelo, vector<el>& elek, vector<csomopont>& csp) {
	init(forras, elek, csp);
	while (true) {
		pair<int, int> a = lehet_pumpalni(forras, nyelo, elek, csp);
		if (a != make_pair(-1, -1)) {
			pumpalas(a.first, a.second, elek, csp);
			continue;
		}

		int u = lehet_emelni(forras, nyelo, elek, csp);
		if (u != -1) {
			emeles(u, elek, csp);
			continue;
		}
		break;
	}
	return csp[nyelo].folyam;
}

void init(int forras, vector<el>& elek, vector<csomopont>& csp) {
	csp[forras].magassag = csp.size() - 1;
	for (int i = 0; i < elek.size(); i++) {
		if (elek[i].u == forras) {
			elek[i].folyam = elek[i].kapacitas;
			csp[elek[i].v].folyam += elek[i].kapacitas;
			csp[forras].folyam -= elek[i].kapacitas;
			elek.push_back({elek[i].v, forras, 0, -elek[i].folyam});
		}
	}
}

pair<int, int> lehet_pumpalni(int forras, int nyelo, vector<el>& elek, vector<csomopont>& csp) {
	for (int i = 1; i < csp.size(); i++) {
		if (i != forras && i != nyelo && csp[i].folyam>0) {
			for (int j = 0; j < elek.size(); j++) {
				if (elek[j].u == i && (elek[j].kapacitas != elek[j].folyam) && csp[i].magassag > csp[elek[j].v].magassag) {
					return { elek[j].u, elek[j].v };
				}
			}
		}
	}
	return { -1, -1 };
}

void pumpalas(int u, int v, vector<el>& elek, vector<csomopont>& csp) {
	int i = 0;
	while (elek[i].u != u || elek[i].v != v) {
		i++;
	}
	int delta = min(csp[u].folyam, elek[i].kapacitas - elek[i].folyam);
	elek[i].folyam += delta;

	i = 0;
	while (i < elek.size() && (elek[i].u != v || elek[i].v != u)) {
		i++;
	}
	if (i == elek.size()) {
		elek.push_back({v, u, delta, 0});
	}
	else {
		elek[i].folyam -= delta;
	}
	csp[u].folyam -= delta;
	csp[v].folyam += delta;
}

int lehet_emelni(int forras, int nyelo, vector<el>& elek, vector<csomopont>& csp) {
	for (int i = 1; i < csp.size(); i++) {
		if (i != forras && i != nyelo && csp[i].folyam > 0) {
			return i;
		}
	}
	return -1;
}

void emeles(int u, vector<el>& elek, vector<csomopont>& csp) {
	int minimum = INT_MAX;
	int v = 0;
	for (int i = 0; i < elek.size(); i++) {
		if (elek[i].u == u && elek[i].folyam != elek[i].kapacitas) {
			minimum = min(minimum, csp[elek[i].v].magassag);
		}
	}
	csp[u].magassag = 1 + minimum;
}
