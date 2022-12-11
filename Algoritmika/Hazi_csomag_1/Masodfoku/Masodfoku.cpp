/*Boda Norbert
511-es csoport
Lab1/07
Irjunk algoritmust az ax2+bx+c = 0 valos egyutthatoju egyenlet megoldasara!
Az egyutthatok 128-bites valos szamok (long double). */

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	long double a, b, c, delta;
	cin >> a >> b >> c;
	if (a == 0) {
		cerr << "Az egyenlet nem masodfoku.";
		return 0;
	}
	delta = b * b - 4 * a * c;
	if (delta > 0) {
		long double gyok1 = (-b - sqrt(delta)) / (2 * a);
		//mivel a round utasitas egesz szamra kerekit, ezert beszorozza a gyokoket 10-el,
		//majd elosztja oket 10-el kerekites utan, hogy az 1 tizedes pontossag maradjon meg
		gyok1 *= 10;
		gyok1 = round(gyok1);
		gyok1 /= 10;
		long double gyok2 = (-b + sqrt(delta)) / (2 * a);
		gyok2 *= 10;
		gyok2 = round(gyok2);
		gyok2 /= 10;
		cout << gyok1 << " " << gyok2;
	}
	else if(delta==0) {
		cerr << "Az egyenletnek csak egy valos gyoke van.";
	}
	else {
		cerr << "Az egyenletnek nincs valos megoldasa.";
	}
	return 0;
}