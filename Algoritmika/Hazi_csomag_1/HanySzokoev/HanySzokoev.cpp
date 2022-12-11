/*Boda Norbert
511-es csoport
Lab1/08
Szamitsuk ki hany szokoev volt/lesz ket kulonbozo evszam kozott! A ket
evszam elojel nelkuli 32-bites egesz.*/

#include <iostream>

using namespace std;

int main() {
	unsigned long ev1, ev2, szokoevek_szama;
	cin >> ev1 >> ev2;
	//az ev1-bol ki kell vonni 1-et ha oszthato 4-el, hogy ez is legyen beleszamolva az intervallumba
	while (ev1 % 4 == 0) {
		ev1--;
	}
	//kiszamitja hany szokoev telt el az ev2-ig, illetve az ev1-ig es kiszamolja a kulonbseguket,
	//hogy tudja meg hany szokoev telt el a ketto kozott
	szokoevek_szama = (ev2 / 4 - ev2 / 100 + ev2 / 400) - (ev1 / 4 - ev1 / 100 + ev1 / 400);
	cout << szokoevek_szama;
	return 0;
}