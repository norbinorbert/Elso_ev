/*Boda Norbert
511-es csoport
Lab4/07
Írjunk rekurzív algoritmust, amely kiszámítja egy 𝑛-ed fokú polinom értékét
egy adott valós 𝑥 pontban! Ne használjunk ismétlő struktúrát a beolvasáson
kívül!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& fokszam, vector<double>& egyutthatok, double& x) {
	cin >> fokszam;
	egyutthatok.resize(fokszam + 1);
	for (short i = fokszam; i >= 0; i--) {
		cin >> egyutthatok[i];
	}
	cin >> x;
}

double polinom(vector<double>& egyutthatok, double& x, short index, short& fokszam) {
	if (index == fokszam) {
		return egyutthatok[index];
	}
	return polinom(egyutthatok, x, index + 1, fokszam) * x + egyutthatok[index];
}

void kiir(double& eredemeny) {
	cout << eredemeny;
}

int main() {
	short fokszam;
	double x;
	vector<double> egyutthatok;
	beolvas(fokszam, egyutthatok, x);

	double eredmeny = polinom(egyutthatok, x, 0, fokszam);
	
	kiir(eredmeny);
	return 0;
}