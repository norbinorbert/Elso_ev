//Boda Norbert, 511

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(vector<pair<int, int>>&);
void opt2(vector<pair<int, int>>&);
vector<int> kezdeti_ut(vector<pair<int, int>>&);
double ut_hossza(vector<int>&, vector<pair<int, int>>&);
double tavolsag(pair<int, int>, pair<int, int>);
void kiir(double, vector<int>&, vector<pair<int, int>>&);

int main() {
	vector<pair<int, int>> varos;
	beolvas(varos);

	opt2(varos);
	return 0;
}

//filebol valo beolvasas
void beolvas(vector<pair<int, int>>& varos) {
	//feltetelezve van, hogy a fileban novekvo sorrendben van a varosok sorszama, illetve 1-tol vannak sorszamozva
	varos.push_back({0, 0});
	ifstream fin("tsp1.txt");
	int sorszam, x, y;
	while (fin >> sorszam >> x >> y) {
		varos.push_back({ x, y });
	}
	fin.close();
}

//2-opt algoritmus
void opt2(vector<pair<int, int>>& varos) {
	vector<int> ut = kezdeti_ut(varos);
	double hossz = ut_hossza(ut, varos);
	int n = ut.size();
	long long iteraciok = 0;
	vector<int> ismetelt_konfiguracio;
	bool lehet_jobb = true;
	while (lehet_jobb) {
		if (iteraciok % 2 == 1) {
			if (ut == ismetelt_konfiguracio) {
				break;
			}
			ismetelt_konfiguracio = ut;
		}
		lehet_jobb = false;
		for (int i = 0; i <= n - 2; i++) {
			for (int j = i + 1; j <= n - 1; j++) {
				double delta = -tavolsag(varos[ut[i]], varos[ut[(i + 1) % n]]) - tavolsag(varos[ut[j]], varos[ut[(j + 1) % n]]) +
								tavolsag(varos[ut[i]], varos[ut[j]]) + tavolsag(varos[ut[(i + 1) % n]], varos[ut[(j + 1) % n]]);
				if (delta < 0) {
					reverse(ut.begin() + i + 1, ut.begin() + j + 1);
					hossz += delta;
					lehet_jobb = true;
				}
			}
		}
		iteraciok++;
	}
	kiir(hossz, ut, varos);
}

//kezdeti ut: 1->2->3->....->varosok szama->1
vector<int> kezdeti_ut(vector<pair<int, int>>& varos) {
	vector<int> ut;
	for (int i = 1; i < varos.size(); i++) {
		ut.push_back(i);
	}
	ut.push_back(1);
	return ut;
}

//kiszamolja a jelenlegi ut hosszat
double ut_hossza(vector<int>& ut, vector<pair<int, int>>& varos) {
	double hossz = 0;
	for (int i = 0; i < ut.size() - 1; i++) {
		hossz += tavolsag(varos[ut[i]], varos[ut[i + 1]]);
	}
	return hossz;
}

//visszateriti ket pont kozotti tavolsagot
double tavolsag(pair<int, int> a, pair<int, int> b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

//kiirja a tavolsagot es az utat (varosok sorszamait)
void kiir(double hossz, vector<int>& ut, vector<pair<int, int>>& varos) {
	ofstream fout("output.txt");
	fout << hossz << endl;
	cout << hossz << endl;
	for (int i = 0; i < ut.size(); i++) {
		fout << ut[i] << " ";
		cout << ut[i] << " ";
	}
	fout.close();
}