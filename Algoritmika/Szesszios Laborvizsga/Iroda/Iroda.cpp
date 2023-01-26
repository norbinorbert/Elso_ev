#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

void beolvas(int& n, vector<int>& idok) {
	cin >> n;
	idok.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> idok[i];
	}
}

void CountSort(vector<int>& idok) {
	vector<int> darab(1000001, 0);
	for (int i = 0; i < idok.size(); i++) {
		darab[idok[i]]++;
	}
	vector<int> temp;
	for (int i = 0; i < darab.size(); i++) {
		while (darab[i] > 0) {
			temp.push_back(i);
			darab[i]--;
		}
	}
	idok = temp;
}

double Iroda(int n, vector<int>& idok) {
	CountSort(idok);
	double varakozas = 0;
	long long eltelt_ido = idok[0];
	for (int i = 1; i < idok.size(); i++) {
		varakozas += eltelt_ido;
		eltelt_ido += idok[i];
	}
	double megoldas = varakozas / n;
	return megoldas;
}

void kiir(double& megoldas) {
	cout << fixed << setprecision(2) << megoldas;
}

int main() {
	int n;
	vector<int> idok;
	beolvas(n, idok);

	double megoldas = Iroda(n, idok);

	kiir(megoldas);
	return 0;
}