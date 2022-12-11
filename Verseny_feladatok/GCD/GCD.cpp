#include <iostream>

using namespace std;

int main() {
	unsigned long long szam1, szam2, szam3;
	cin >> szam1 >> szam2 >> szam3;
	while (szam1 != szam2 && szam1 != szam3) {
		while (szam1 != szam2) {
			if (szam1 > szam2) {
				szam1 -= szam2;
			}
			else {
				szam2 -= szam1;
			}
		}
		while (szam1 != szam3) {
			if (szam1 > szam3) {
				szam1 -= szam3;
			}
			else {
				szam3 -= szam1;
			}
		}
		while (szam2 != szam3) {
			if (szam2 > szam3) {
				szam2 -= szam3;
			}
			else {
				szam3 -= szam2;
			}
		}
	}
	cout << szam1;
	return 0;
}