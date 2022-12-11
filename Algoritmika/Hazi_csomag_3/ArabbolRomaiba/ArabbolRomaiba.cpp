/*Boda Norbert
511-es csoport
Lab3/06
Adott egy arab szám, írjuk ki római számjegyekkel!
*/

#include <iostream>
#include <string>

using namespace std;

void beolvas(short& arab_szam) {
	cin >> arab_szam;
	return;
}

string atalakit(short arab_szam) {
	string egy = "I", ot = "V", tiz = "X", otven = "L", szaz = "C", otszaz = "D", ezer = "M", otezer = "_V", romai_ujszam = "";
	short szam_masolat = arab_szam, szamlalo = 1;

	while (szam_masolat > 0) {
		//megnezi az arab szam utolso szamjegyet es az alapjan epiti tovabb a romai szamot
		short szamjegy = szam_masolat % 10;

		if (szamjegy == 1) {
			//a szamlalo valtozo segitsegevel tudja, hogy az egyesek, tizesek, szazasok vagy ezresek poziciojat epiti fel jelenleg
			if (szamlalo == 1) {
				romai_ujszam = egy + romai_ujszam;
			}
			else if (szamlalo == 10) {
				romai_ujszam = tiz + romai_ujszam;
			}
			else if (szamlalo == 100) {
				romai_ujszam = szaz + romai_ujszam;
			}
			else if (szamlalo == 1000) {
				romai_ujszam = ezer + romai_ujszam;
			}
		}

		if (szamjegy == 2) {
			if (szamlalo == 1) {
				romai_ujszam = egy + egy + romai_ujszam;
			}
			else if (szamlalo == 10) {
				romai_ujszam = tiz + tiz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = szaz + szaz + romai_ujszam;

			}
			else if (szamlalo == 1000) {
				romai_ujszam = ezer + ezer + romai_ujszam;

			}
		}

		if (szamjegy == 3) {
			if (szamlalo == 1) {
				romai_ujszam = egy + egy + egy + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = tiz + tiz + tiz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = szaz + szaz + szaz + romai_ujszam;

			}
			else if (szamlalo == 1000) {
				romai_ujszam = ezer + ezer + ezer + romai_ujszam;

			}
		}

		if (szamjegy == 4) {
			if (szamlalo == 1) {
				romai_ujszam = egy + ot + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = tiz + otven + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = szaz + otszaz + romai_ujszam;

			}
			else if (szamlalo == 1000) {
				romai_ujszam = ezer + ezer + ezer + ezer + romai_ujszam;

			}
		}

		if (szamjegy == 5) {
			if (szamlalo == 1) {
				romai_ujszam = ot + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = otven + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = otszaz + romai_ujszam;

			}
			else if (szamlalo == 1000) {
				romai_ujszam = ezer + ezer + ezer + ezer + ezer + romai_ujszam;

			}
		}

		if (szamjegy == 6) {
			if (szamlalo == 1) {
				romai_ujszam = ot + egy + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = otven + tiz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = otszaz + szaz + romai_ujszam;

			}
		}

		if (szamjegy == 7) {
			if (szamlalo == 1) {
				romai_ujszam = ot + egy + egy + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = otven + tiz + tiz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = otszaz + szaz + szaz + romai_ujszam;

			}
		}

		if (szamjegy == 8) {
			if (szamlalo == 1) {
				romai_ujszam = ot + egy + egy + egy + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = otven + tiz + tiz + tiz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = otszaz + szaz + szaz + szaz + romai_ujszam;

			}
		}

		if (szamjegy == 9) {
			if (szamlalo == 1) {
				romai_ujszam = egy + tiz + romai_ujszam;

			}
			else if (szamlalo == 10) {
				romai_ujszam = tiz + szaz + romai_ujszam;

			}
			else if (szamlalo == 100) {
				romai_ujszam = szaz + ezer + romai_ujszam;

			}
		}

		szam_masolat /= 10;
		szamlalo *= 10;
	}

	return romai_ujszam;
}

void kiir(string& romai_szam) {
	cout << romai_szam;
	return;
}

int main() {
	short arab_szam;
	beolvas(arab_szam);

	string romai_szam = atalakit(arab_szam);

	kiir(romai_szam);
}