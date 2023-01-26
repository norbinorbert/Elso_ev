#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void beolvas(short& n, short& m) {
	cin >> n >> m;
}

void kiir(vector<int>& megoldas) {
	for (int i = 0; i < megoldas.size(); i++) {
		cout << megoldas[i] << " ";
	}
	cout << endl;
}

void general_Injektiv(short n, short m, vector<int>& megoldas, vector<bool>& volt) {
	if (megoldas.size() == n) {
		kiir(megoldas);
		return;
	}
	for (int i = 1; i <= m; i++) {
		if (!volt[i]) {
			volt[i] = true;
			megoldas.push_back(i);
			general_Injektiv(n, m, megoldas, volt);
			volt[i] = false;
			megoldas.pop_back();
		}
	}
}

void Injektiv(short n, short m) {
	vector<int> megoldas;
	vector<bool> volt(m + 1, false);
	general_Injektiv(n, m, megoldas, volt);
}

int main() {
	short n, m;
	beolvas(n, m);

	Injektiv(n, m);

	return 0;
}