#include <iostream>
#include <cmath>

using namespace std;

#define pi 3.14159265358979323846

int wasteful_pek(double oldal, double atmero) {
	int szamlalo = floor(oldal / atmero);
	
	return szamlalo * szamlalo;
}

int efficient_pek(double oldal, double atmero) {
	double sugar = atmero / 2;
	int szamlalo = 0, temp_szamlalo=0;
	double kor_terulet = pi * (sugar * sugar);

	while (oldal > atmero) {
		int temp_szamlalo = wasteful_pek(oldal, atmero);
		double terulet = oldal * oldal;
		double uj_terulet = terulet - temp_szamlalo * kor_terulet;
		szamlalo += temp_szamlalo;
		oldal = sqrt(uj_terulet);
	}

	return szamlalo;
}

int main() {
	double terulet = 0, atmero, oldal;
	int szamlalo_elso_pek = 0, szamlalo_masodik_pek = 0;
	cin >> oldal >> atmero;

	szamlalo_elso_pek = wasteful_pek(oldal, atmero);
	szamlalo_masodik_pek = efficient_pek(oldal, atmero);
	
	cout << szamlalo_masodik_pek - szamlalo_elso_pek;
	return 0;
}