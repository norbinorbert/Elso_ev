#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool prim(long long szam) {
	if (szam < 2) {
		return false;
	}
	else {
		if (szam % 2 == 0) {
			return (szam == 2);
		}
		else {
			if (szam <= 7) {
				return true;
			}
			else {
				if ((szam - 1) % 6 != 0 && (szam + 1) % 6 != 0) {
					return false;
				}
				else {
					int gyok = sqrt(szam);
					for (int i = 3; i <= gyok; i += 2) {
						if (szam % i == 0) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

vector<int> vegek = { 1, 3, 7, 9 };

void backtrack(long long& temp_eredmeny, int n, int m, vector<vector<int>>& szamok) {
	if (szamok[n - 1][m - 1] != 0) {
		temp_eredmeny++;
		return;
	}
	int i, j, k, l;
	bool volt_nullas = false;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (szamok[i][j] == 0) {
				volt_nullas = true;
				for (k = 0; k < 4; k++) {
					if ((i == 0 || j == 0) && (k == 0 || k==3)) {
						continue;
					}
					bool sorprim = false, oszlopprim = false;
					if (i == 0) {
						oszlopprim = true;
					}
					else {
						long long szam = 0;
						for (l = 0; l < i; l++) {
							szam = szam * 10 + szamok[l][j];
						}
						szam = szam * 10 + vegek[k];
						if (prim(szam)) {
							oszlopprim = true;
						}
						else {
							continue;
						}
					}
					if (j == 0) {
						sorprim = true;
					}
					else {
						long long szam = 0;
						for (l = 0; l < j; l++) {
							szam = szam * 10 + szamok[i][l];
						}
						szam = szam * 10 + vegek[k];
						if (prim(szam)) {
							sorprim = true;
						}
					}
					if (sorprim && oszlopprim) {
						szamok[i][j] = vegek[k];
						backtrack(temp_eredmeny, n, m, szamok);
						szamok[i][j] = 0;
					}
				}
			}
			if (volt_nullas) {
				return;
			}
		}
		if (volt_nullas) {
			return;
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> szamok(n, vector<int>(m, 0));
	vector<int> kezdet = { 2, 3, 5, 7 };
	long long eredmeny = 0;
	for (int i = 0; i < 4; i++) {
		szamok[0][0] = kezdet[i];
		long long temp_eredmeny = 0;
		backtrack(temp_eredmeny, n, m, szamok);
		eredmeny += temp_eredmeny;
	}
	cout << eredmeny;
	return 0;
}