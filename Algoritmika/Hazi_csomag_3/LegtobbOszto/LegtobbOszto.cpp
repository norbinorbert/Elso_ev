/*Boda Norbert
511-es csoport
Lab3/09
Keressük meg adott számmal bezárólag a legtöbb osztójú természetes számot!*/

#include <iostream>
#include <cmath>

using namespace std;

void beolvas(int& szam) {
	cin >> szam;
	return;
}

void vizsgal_legtobb_oszto(int& x, int& szam, int& szamlalo) {
	//az 1-nek nincs valodi osztoja, illetve csak 1 osztoja van
	if (x == 1) {
		szam = 1;
		szamlalo = 0;
		return;
	}
	//a 2-es szamnak 2 osztoja van (1, 2), de nincs valodi osztoja, ugyanigy a 3-as szam is, de 2 < 3
	if (x == 2 || x == 3) {
		szam = 2;
		szamlalo = 0;
		return;
	}
	//a 4-nek egyetlen valodi osztoja van (2-es), az 5 pedig primszam
	if (x == 4 || x == 5) {
		szam = 4;
		szamlalo = 1;
	}
	//a 6-os szamtol kezdodoen mindig egy 6-os tobbszorosnek van a legtobb valodi osztoja, 
	//ezert a szamokat [1, 5] intervallumban kulon vannak lekezelve
	int i = x / 2;
	while (i % 6 != 0) {
		i++;
	}
	for (; i <= x; i = i + 6) {
		double gyok = sqrt(i);
		int temp_szamlalo = 0;
		//eleg a szam gyokeig menni es keresni az osztokat, mert ha az oszto<gyok,
		//akkor letezik egy "y" szam, amire: y > gyok ES oszto * y = szam
		for (int oszto = 2; oszto <= gyok; oszto++) {
			if (i % oszto == 0 && oszto != gyok) {
				temp_szamlalo += 2;
			}
			if (i % oszto == 0 && oszto == gyok) {
				temp_szamlalo++;
			}
		}
		if (temp_szamlalo > szamlalo) {
			szamlalo = temp_szamlalo;
			szam = i;
		}
	}
	return;
}

void kiir(int& szamlalo, int& legtobb_osztoju_szam) {
	cout << legtobb_osztoju_szam << " " << szamlalo;
	return;
}

int main() {
	int szam;
	beolvas(szam);

	int szamlalo = 0, legtobb_osztoju_szam = 1;
	vizsgal_legtobb_oszto(szam, legtobb_osztoju_szam, szamlalo);

	kiir(szamlalo, legtobb_osztoju_szam);
	return 0;
}
