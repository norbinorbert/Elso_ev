/*Boda Norbert
511-es csoport
Lab1/06
Adott harom szigoruan pozitiv 64-bites valos szam (double): a, b, c. Kepezhetike ezek a szamok egy haromszog oldalait?
Ha igen, hatarozzuk meg es irjuk ki a haromszogbe irt, illetve a haromszog kore irt kor sugarat! Ha nem, irjunk ki -1-et!
*/
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	bool haromszog = false;
	//akkor tudunk meghatarozni haromszoget, ha barmely 2 oldal hosszanak osszege nagyobb a harmadik oldalnal
	if (a + b > c && a + c > b && b + c > a) {
		haromszog = true;
	}
	double kore_irt_kor, bele_irt_kor;
	if(haromszog){
		double felkerulet = (a + b + c) / 2;
		//Heron keplete
		double terulet = sqrt(felkerulet * (felkerulet - a) * (felkerulet - b) * (felkerulet - c));
		bele_irt_kor = 2 * terulet / (a + b + c);
		kore_irt_kor = (a * b * c) / (4 * terulet);
		//beszorozza a sugarat 1000-el, egeszre kerekit, majd 1000-el oszt, hogy maradjon meg a 3 tizedes pontossag
		bele_irt_kor *= 1000;
		bele_irt_kor = round(bele_irt_kor);
		bele_irt_kor /= 1000;
		kore_irt_kor *= 1000;
		kore_irt_kor = round(kore_irt_kor);
		kore_irt_kor /= 1000;
		cout << bele_irt_kor << " " << kore_irt_kor;
	}
	else {
		cout << -1;
	}
	return 0;
}