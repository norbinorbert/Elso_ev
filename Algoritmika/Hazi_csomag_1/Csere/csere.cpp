/* Boda Norbert
511-es csoport
Lab1/01
Hasonlitsuk ossze ket egesz tipusu valtozo cserejenek sebesseget harom kulonbozo modszerrel:
 segedvaltozoval
 osszeadassal es kivonassal
 xor cserevel*/

#include <iostream>
#include <ctime>

using namespace std;

int main() {
	unsigned long szam1, szam2;
	cin >> szam1 >> szam2;
	//lementi a jelenlegi idot egy valtozoba, majd kesobb ezek kulonbsege lesz a futasi ido
	float ido_kezdeti = clock();
	//segedvaltozoval valo csere
	for (int i = 0; i <= 100000000; i++) {
		int temp = szam1;
		szam1 = szam2;
		szam2 = temp;
	}
	float ido_1 = clock();
	//osszeadas es kivonassal valo csere
	for (int i = 0; i <= 100000000; i++) {
		szam1 = szam1+szam2;
		szam2 = szam1 - szam2;
		szam1 = szam1 - szam2;
	}
	float ido_2 = clock();
	//xor csere
	for (int i = 0; i <= 100000000; i++) {
		szam1 = szam1 xor szam2;
		szam2 = szam1 xor szam2;
		szam1 = szam1 xor szam2;
	}
	float ido_vegso = clock();
	cout << szam1 << " " << szam2;
	cerr << endl << "Segedvaltozot hasznalva mert ido: " << (ido_1 - ido_kezdeti) / CLOCKS_PER_SEC << "masodperc";
	cerr << endl << "Osszeadast es kivonast hasznalva mert ido: " << (ido_2 - ido_1) / CLOCKS_PER_SEC << "masodperc";
	cerr << endl << "Xor cseret hasznalva mert ido: " << (ido_vegso - ido_2) / CLOCKS_PER_SEC << "masodperc";
	return 0;
}