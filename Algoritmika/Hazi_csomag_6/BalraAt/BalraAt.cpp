/*Boda Norbert
511-es csoport
Lab6/06
Szeptember 15-én az iskola igazgatója felkéri az első osztályos gyermekeket,
hogy forduljanak arccal felé, majd abból a célból, hogy felvezethesse őket az
osztálytermekbe, kiadja a parancsot: “Balra át!”. A gyermekek bizonytalanok.
Van, aki balra fordul, van, aki jobbra. Aki szemben találja magát a mellette
állóval, azt hiszi, hogy rosszul fordult és egy időegység alatt egyszer sarkon
fordul. Adott egy bizonyos kezdeti konfiguráció, amely a “Balra át!” parancs
után alakult ki. Állapítsuk meg, hány időegység alatt „nyugszik meg” a sor.*/

#include <iostream>
#include <string>

using namespace std;

void beolvas(string& sor) {
	cin >> sor;
}

unsigned long long balra_at(string& sor) {
	unsigned long long megoldas_balrol = 0, megoldas_jobbrol = 0;
	int bal = 0;
	while (bal < sor.size() && sor[bal] == 'b') {
		bal++;
	}
	int jobb = sor.size() - 1;
	while (0 <= jobb && sor[jobb] == 'j') {
		jobb--;
	}
	int szamlalo = 0;
	for (int i = bal; i <= jobb; i++) {
		if (sor[i] == 'j') {
			szamlalo++;
		}
		else {
			if (i - bal - 1 > szamlalo) {
				megoldas_balrol++;
			}
			else {
				megoldas_balrol = szamlalo;
			}
		}
	}
	szamlalo = 0;
	for (int i = jobb; i >= bal; i--) {
		if (sor[i] == 'b') {
			szamlalo++;
		}
		else {
			if (jobb - i > szamlalo) {
				megoldas_jobbrol++;
			}
			else {
				megoldas_jobbrol = szamlalo;
			}
		}
	}

	return max(megoldas_balrol, megoldas_jobbrol);
}


void kiir(unsigned long long& megoldas) {
	cout << megoldas;
}

int main() {
	string sor;
	beolvas(sor);

	unsigned long long megoldas = balra_at(sor);

	kiir(megoldas);
	return 0;
}