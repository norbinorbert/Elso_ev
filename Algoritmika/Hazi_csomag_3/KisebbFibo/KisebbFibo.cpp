/*Boda Norbert
511-es csoport
Lab3/03
Írjunk algoritmust, amely megadja a Fibonacci-sorozat egy adott 𝑥 számnál kisebb elemeinek számát!
A Fibonacci-sorozat nulladik elemét nem kell figyelembe venni.*/
#include <iostream>
#include <climits>

using namespace std;

void beolvas(unsigned long long& szam) {
	cin >> szam;
	return;
}

short Fibonacci_szamok_szama(unsigned long long& szam) {
	if (szam == 0 || szam == 1) {
		return 0;
	}
	unsigned long long f0 = 0, f1 = 1;
	short szamlalo = 1;
	unsigned long long f2 = f0 + f1;
	while (f2 < szam && ULLONG_MAX-f1 >= f0) {
		szamlalo++;

		f0 = f1;
		f1 = f2;
		f2 = f0 + f1;
	}

	return szamlalo;
}

void kiir(short& szamlalo, unsigned long long& szam) {
	cout << szamlalo << " darab kisebb elem van a Fibonacci-sorozatban, mint " << szam;
	return;
}

int main() {
	unsigned long long szam;
	beolvas(szam);

	short szamlalo = Fibonacci_szamok_szama(szam);

	kiir(szamlalo, szam);
	return 0;
}