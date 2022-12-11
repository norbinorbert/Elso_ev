/*Boda Norbert
511-es csoport
Lab2/02
Hat�rozzuk meg egy adott x term�szetes sz�m legkisebb oszt�j�t, amely nagyobb mint 1!*/

#include <iostream>

using namespace std;

void beolvas(unsigned int& szam) {
	cin >> szam;
	return;
}

unsigned int legkisebb_oszto(unsigned int szam) {
	unsigned long long i = 2;
	unsigned int oszto;
	if (szam % i == 0) {
		oszto = i;
	}
	else {
		//szekvencialis kereses programozasi tetel
		i++;
		while (i * i <= szam && szam % i != 0) {
			//2-vel noveljuk az i-t, mert paros osztokat nem kell nezni a 2-es szam utan
			i += 2;
		}
		if (i * i <= szam) {
			oszto = i;
		}
		else {
			oszto = szam;
		}
	}
	return oszto;
}

int main() {
	unsigned int szam;

	beolvas(szam);

	cout << legkisebb_oszto(szam);
	return 0;
}