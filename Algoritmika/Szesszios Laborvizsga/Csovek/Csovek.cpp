#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void beolvas(int& n, vector<unsigned int>& csovek) {
	cin >> n;
	csovek.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> csovek[i];
	}
}

void Csovek(int& n, vector<unsigned int>& csovek, unsigned long long& megoldas) {
	vector<vector<unsigned long long>> matrix(n + 1, vector<unsigned long long>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				matrix[i][j] = csovek[i - 1];
			}
			else if (i < j) {
				int k = 0;
				unsigned long long temp = 0;
				while (k < i) {
					temp = max(temp, matrix[i - k][j - i]);
					k++;
				}
				matrix[i][j] = temp + csovek[i - 1];
			}
			megoldas = max(megoldas, matrix[i][j]);
		}
	}
}

void kiir(unsigned long long& megoldas) {
	cout << megoldas;
}

int main() {   
	int n;
	vector<unsigned int> csovek;
	beolvas(n, csovek);

	unsigned long long megoldas = 0;
	Csovek(n, csovek, megoldas);

	kiir(megoldas);
	return 0;
}