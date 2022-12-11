/*Boda Norbert
511-es csoport
Lab1/02
Hasonlitsuk ossze egy ismetlodo ciklus sebesseget amely a beolvasott szam
gyokeig megy el, haromfelekeppen implementalva:
 while (i*i <= n)
 sqrt(n)-t segedvaltozoba mentve a ciklus elott
 while (i <= sqrt(n))
Teszteljuk a harom valtozatot n kulonbozo ertekeire 10 es 1 000 000 000 kozott
*/

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{
	unsigned long long n;
	cin >> n;
	int iteraciok_szama = 0, i=1;
	//lementi a jelenlegi idot egy valtozoba, majd kesobb ezek kulonbsege lesz a futasi ido
	float ido_kezdeti = clock();
	//elso modszer

	double gyok = sqrt(n);
	for (int j = 0; j < 1000000; j++) {
		while (i <= gyok) {
			iteraciok_szama++;
			i++;
		}
	}
	float ido_1 = clock();
	//masodik modszer
	//double gyok = sqrt(n);
	i = 1;
	iteraciok_szama = 0;
	for (int j = 0; j < 1000000; j++) {
		
		while (i * i <= n) {
			iteraciok_szama++;
			i++;
		}
	}
	float ido_2 = clock();
	//harmadik modszer
	i = 1;
	iteraciok_szama = 0;
	for (int j = 0; j < 1000000; j++) {
		while (i <= sqrt(n)) {
			iteraciok_szama++;
			i++;
		}
	}
	float ido_vegso = clock();
	
	cout << iteraciok_szama;

	cerr << endl << "while (i*i <= n) modszerrel mert ido: " << (ido_1 - ido_kezdeti) / CLOCKS_PER_SEC << " masodperc";
	cerr << endl << "sqrt(n)-t segedvaltozoba mentve a ciklus elott modszerrel mert ido:" << (ido_2 - ido_1) / CLOCKS_PER_SEC << " masodperc";
	cerr << endl << "while (i <= sqrt(n)) modszerrel mert ido: " << (ido_vegso - ido_2) / CLOCKS_PER_SEC << " masodperc";
	return 0;
}