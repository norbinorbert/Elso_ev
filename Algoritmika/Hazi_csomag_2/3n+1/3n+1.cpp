/*Boda Norbert
511-es csoport
Lab2/09
Ismert sejtés, miszerint ha egy adott 𝑛 természetes számot ismételten alávetünk
a következő feldolgozásnak, eljutunk az 1-es számhoz: ha 𝑛 páros, akkor elosztjuk
2-vel, ha 𝑛 páratlan, megszorozzuk 3-mal és az eredményhez hozzáadunk 1-et.
Azoknak a lépéseknek a számát, amelyek egy adott 𝑛-ből az 1-hez vezetnek,
karakterisztikának nevezzük. Írjunk programot, amely meghatározza azt az 𝑛
számot, amely az [𝑥, 𝑦] intervallumhoz tartozik és amelynek a karakterisztikája
a legnagyobb!
*/
#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& x, short& y) {
	cin >> x >> y;
}

void karakterisztika_szamolas(short x, short y, vector<int>& karakterisztika) {
	int szam=0;
	//ahanyszor kiszamol egy szamot azt megjegyzi, hogy ne kelljen ujbol dolgozzon vele,
	//mivel annak a karakterisztikaja biztosan kisebb lesz, mint a kiindulopont
	vector<int> v(y+1);

	for (int i = y; i >= x; i--) {
		int temp_karakterisztika = 0;
		if (v[i] == 0)
		{
			szam = i;
			v[szam] = 1;
		}
		while (szam != 1) {
			if (szam % 2 == 0) {
				szam /= 2;
				temp_karakterisztika++;
			}
			else {
				szam = 3 * szam + 1;
				temp_karakterisztika++;
			}
			if (szam < y) {
				if (v[szam] == 0) {
					v[szam] = 1;
				}
			}
		}
		karakterisztika[i] = temp_karakterisztika;
	}
	return;
}

void kiir_max_karakterisztika(short x, short y,vector<int> karakterisztika) {
	int max_karakterisztika = karakterisztika[y], szam=y;
	//maximum kivalsztas programozasi tetel
	for (int i = y-1; i >=x; i--) {
		if (karakterisztika[i] > max_karakterisztika) {
			max_karakterisztika = karakterisztika[i];
			szam = i;
		}
	}

	cout << szam << " " << max_karakterisztika;
	return;
}

int main() {
	short x, y;
	beolvas(x, y);

	vector<int> karakterisztika(y + 1);

	karakterisztika_szamolas(x, y, karakterisztika);

	kiir_max_karakterisztika(x, y, karakterisztika);

	return 0;
}