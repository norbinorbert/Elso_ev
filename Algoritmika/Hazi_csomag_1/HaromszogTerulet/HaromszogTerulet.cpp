/*Boda Norbert
511-es csoport
Lab1/04
Szamitsuk ki egy haromszog teruletet, ha ismerjuk oldalainak a hosszat! Az
oldalak hosszai 64-bites valos szamok (double).*/


#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double oldal1, oldal2, oldal3;
	cin >> oldal1 >> oldal2 >> oldal3;
	double felkerulet = (oldal1 + oldal2 + oldal3) / 2;
	// hasznaljuk Heron kepletet a terulet kiszamitasara
	double terulet = sqrt(felkerulet * (felkerulet - oldal1) * (felkerulet - oldal2) * (felkerulet - oldal3));
	//mivel a round fuggveny egesz szamra kerekit, ezert beszorozzuk az eredeti teruletet 100-al, majd kerekites utan elosztjuk 100-al
	terulet *= 100;
	terulet = round(terulet);
	terulet /= 100;
	cout << terulet;
	return 0;
}
