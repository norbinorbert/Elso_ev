/*Boda Norbert
511-es csoport
Lab4/09
Implementáljuk rekurzívan az orosz szorzás algoritmusát!*/

#include <iostream>

using namespace std;

void beolvas(unsigned long long& x, unsigned long long& y) {
	cin >> x >> y;
}

unsigned long long orosz(unsigned long long x, unsigned long long y) {
	if (x == 0 || y==0) {
		return 0;
	}
	if (x % 2 == 1) {
		return y + orosz(x / 2, y * 2);
	}
	else {
		return orosz(x / 2, y * 2);
	}
}

void kiir(unsigned long long& megoldas) {
	cout << megoldas;
}

int main() {
	unsigned long long x, y;
	beolvas(x, y);

	unsigned long long megoldas = orosz(x, y);

	kiir(megoldas);
	return 0;
}