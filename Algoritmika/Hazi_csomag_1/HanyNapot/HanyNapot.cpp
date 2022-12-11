/*Boda Norbert
511-es csoport
Lab1/09
Szamitsuk ki, hany napot eltunk a mai nappal bezarolag! Ha valaki januar
1.-en szuletett, akkor januar 2.-an elt 1 napot.*/

#include <iostream>
#include <string>

using namespace std;

//az alprogram felbont egy datumot kulon ev, honap es napra
void string_felbontas(string datum, string& ev, string& honap, string& nap) {
	int szamlalo = 0;
	for (int i = 0; i < datum.size(); i++) {
		if (datum[i] == '.') {
			szamlalo++;
		}
		else {
			if (szamlalo == 0) {
				ev += datum[i];
			}
			if (szamlalo == 1) {
				honap+= datum[i];
			}
			if (szamlalo == 2) {
				nap += datum[i];
			}
		}
	}
	return;
}

int main() {
	string szuletesi_datum, jelenlegi_datum;
	getline(cin, szuletesi_datum);
	getline(cin, jelenlegi_datum);
	string ev1_string = "", honap1_string = "", nap1_string = "", ev2_string = "", honap2_string = "", nap2_string = "";
	string_felbontas(szuletesi_datum, ev1_string, honap1_string, nap1_string);
	string_felbontas(jelenlegi_datum, ev2_string, honap2_string, nap2_string);
	//a stringeket atalakitja integerbe, hogy szamoljon segitsegukkel
	int ev1 = stoi(ev1_string), honap1 = stoi(honap1_string), nap1 = stoi(nap1_string);
	int ev2 = stoi(ev2_string), honap2 = stoi(honap2_string), nap2 = stoi(nap2_string);
	int napok_szama = 0;
	//ha a szuletesi ev szokoev es a honap februaron tul van akkor mar nem kell az a +1 napot szamolni, ezert a szamlalot -1-tol inditja
	if (((ev1 % 4 == 0 && ev1 % 100 != 0) || ev1 % 400 == 0) && (honap1 < honap2) && honap1 <= 2) {
		napok_szama = -1;
	}
	//szamolja egyesevel a napokat, amig eler a kovetkezo honap azon napjahoz, amelyik megegyezik a jelenlegi datum napjaval
	while (nap1 != nap2) {
		napok_szama++;
		nap1++;
		if ((honap1 == 1 || honap1 == 3 || honap1 == 5 || honap1 == 7 || honap1 == 8 || honap1 == 10 || honap1 == 12) && nap1>31) {
			nap1 -= 31;
			honap1++;
		}
		if ((honap1 == 4 || honap1 == 6 || honap1 == 9 || honap1 == 11) && nap1 > 30) {
			nap1 -= 30;
			honap1++;
		}
		if (honap1 == 2) {
			if ((ev1 % 4 == 0 && ev1 % 100 != 0) || ev1 % 400 == 0) {
				if (nap1 > 29) {
					nap1 -= 29;
					honap1++;
				}
			}
			else {
				if (nap1 > 28) {
					nap1 -= 28;
					honap1++;
				}
			}
		}
	}
	//szamolja a honapokban levo napokat, amig eler a kovetkezo ev azon honapjahoz, amelyik megegyezik a jelenlegi datum honapjaval
	while (honap1 != honap2) {
		if (honap1 == 1 || honap1 == 3 || honap1 == 5 || honap1 == 7 || honap1 == 8 || honap1 == 10 || honap1 == 12) {
			napok_szama += 31;
		}
		if (honap1 == 4 || honap1 == 6 || honap1 == 9 || honap1 == 11) {
			napok_szama += 30;
		}
		if (honap1 == 2) {
			if ((ev1 % 4 == 0 && ev1 % 100 != 0) || ev1 % 400 == 0) {
				napok_szama += 29;
			}
			else {
				napok_szama += 28;
			}
		}
		honap1++;
		if (honap1 > 12) {
			honap1 -= 12;
			ev1++;
		}
	}
	//szamolja az evekben levo napokat, amig eler a jelenlegi datumig
	for (int i = ev1; i < ev2; i++) {
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
			napok_szama += 366;
		}
		else {
			napok_szama += 365;
		}
	}
	cout << napok_szama;
	return 0;
}