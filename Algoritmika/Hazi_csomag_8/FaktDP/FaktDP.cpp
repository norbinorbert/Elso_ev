/*Boda Norbert
511-es csoport
Lab8/03
Számoljátok ki 𝑛 faktoriálisát a dinamikus programozás módszerével!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& szam) {
	cin >> szam;
}

vector<long long> faktorialis_szamolas(short& szam) {
	vector<long long> faktorialisok(szam + 1);
	faktorialisok[0] = 1;
	for (short i = 1; i <= szam; i++) {
		faktorialisok[i] = i * faktorialisok[i - 1];
	}
	return faktorialisok;
}

void kiir(vector<long long>& faktorialisok, short& szam) {
	cout << faktorialisok[szam];
}

int main() {
	short szam;
	beolvas(szam);
	vector<long long> faktorialisok = faktorialis_szamolas(szam);
	kiir(faktorialisok, szam);
	return 0;
}