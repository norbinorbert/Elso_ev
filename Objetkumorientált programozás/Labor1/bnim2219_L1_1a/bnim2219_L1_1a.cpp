/*Boda Norbert, 511-es csoport*/

#include <iostream>
#include <ctime>

using namespace std;

int veletlenSzam(int a, int b);
void jatek(int generaltSzam);

int main() {
	int generalt_szam = veletlenSzam(1, 100);
	jatek(generalt_szam);
	return 0;
}

int veletlenSzam(int a, int b) {
	srand(time(NULL));
	int c = max(a, b) - min(a, b) + 1;
	int szam = rand() % c;
	return szam + min(a, b);
}

void jatek(int generaltSzam) {
	cout << "Tipp: ";
	int tipp;
	cin >> tipp;
	if (tipp < generaltSzam) {
		cout << "nagyobb\n";
		jatek(generaltSzam);
		return;
	}
	else {
		if (tipp == generaltSzam) {
			cout << "gratulalok\n";
			return;
		}
		else {
			cout << "kisebb\n";
			jatek(generaltSzam);
			return;
		}
	}
}
