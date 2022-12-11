/*Boda Norbert
511-es csoport
Lab2/10
Adott a következő sorozat, amelynek minden elemét – az elsőt kivéve – az
előző elem segítségével generáljuk: 1, 11, 21, 1211, 111221, . . .
A generálási szabály a következő:
• megszámoljuk, balról jobbra haladva az előző érték számjegyeit
• az új értéket úgy kapjuk meg, hogy beírjuk a régi érték összes számjegyeinek
előfordulási számát és az illető számjegyet
Határozzuk meg az 𝑛-edik elemét a sorozatnak!*/

#include <iostream>
#include <string>

using namespace std;

void beolvas(short& n) {
	cin >> n;
	return;
}

string sorozat_generalas(string elozo_elem) {
	string mostani_elem = "", szamjegyek_szama;
	char szamjegy = elozo_elem[0];
	int szamlalo = 0;
	for (int i = 0; i < elozo_elem.size(); i++) {

		if (elozo_elem[i] == szamjegy) {
			szamlalo++;
			if (i == elozo_elem.size() - 1) {
				szamjegyek_szama = to_string(szamlalo);
				mostani_elem = mostani_elem + szamjegyek_szama + szamjegy;
			}
		}

		if(elozo_elem[i] != szamjegy) {
			szamjegyek_szama = to_string(szamlalo);
			mostani_elem = mostani_elem + szamjegyek_szama + szamjegy;
			szamjegy = elozo_elem[i];
			szamlalo = 1;
			if (i == elozo_elem.size() - 1) {
				szamjegyek_szama = to_string(szamlalo);
				mostani_elem = mostani_elem + szamjegyek_szama + szamjegy;
			}
		}
	}

	return mostani_elem;
}

void kiir(string& sorozat_eleme) {
	cout << sorozat_eleme;
	return;
}

int main() {
	short n;
	beolvas(n);
	string sorozat[41];
	sorozat[1] = "1";

	//sorozatszamitas programozasi tetel
	for (short i = 2; i <= n; i++) {
		sorozat[i] = sorozat_generalas(sorozat[i - 1]);
	}

	kiir(sorozat[n]);

	return 0;
}