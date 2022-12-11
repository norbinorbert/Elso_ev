/*Boda Norbert
511-es csoport
Lab4/06
Írjunk rekurzív algoritmust, amely kiír egy 𝑛 természetes számot törzstényezőkre
bontva! Ne használjunk egyáltalán ismétlő struktúrát!
*/

#include <iostream>
#include <cmath>

using namespace std;

void beolvas(unsigned int& szam) {
	cin >> szam;
}

void torzstenyezok(unsigned int szam, unsigned int oszto, short hatvany) {
	if (szam == 0) {
		return;
	}

	if (szam == 1) {
		if (hatvany > 1) {
			cout << oszto << "^" << hatvany;
		}
		if (hatvany == 1) {
			cout << oszto;
		}
		return;
	}

	if (hatvany == 0 && oszto > sqrt(szam)) {
		cout << szam;
		return;
	}

	if (szam % oszto == 0) {
		return torzstenyezok(szam / oszto, oszto, hatvany + 1);
	}
	else {
		if (hatvany > 1) {
			cout << oszto << "^" << hatvany << "*";
			hatvany = 0;
		}
		else if (hatvany == 1) {
			cout << oszto << "*";
			hatvany = 0;
		}

		if (oszto == 2) {
			return torzstenyezok(szam, oszto + 1, hatvany);
		}
		//a prim osztok (6k-1) vagy (6k+1) alakuak lehetnek, ezert csak ezeket vizsgalja
		if (oszto == 3 || (oszto + 1) % 6 == 0) {
			return torzstenyezok(szam, oszto + 2, hatvany);
		}
		else {
			return torzstenyezok(szam, oszto + 4, hatvany);
		}
	}
}

int main() {
	unsigned int szam;
	beolvas(szam);

	torzstenyezok(szam, 2, 0);
	return 0;
}