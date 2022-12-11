/*Boda Norbert
511-es csoport
Lab3/01
Döntsük el egy adott számról, hogy völgyszám-e vagy hegyszám. 
Egy völgyszám számjegyei szigorúan csökkenő sorrendben követik egymást egy bizonyos
elemmel bezárólag, majd azzal kezdődően szigorúan növekvő sorozatot alkotnak.
A hegyszám számjegyei szigorúan növekvő sorrendben követik egymást egy
bizonyos elemmel bezárólag, majd azzal kezdődően szigorúan csökkenő sorozatot
alkotnak.
Írjunk ki egy megfelelő üzenetet, aszerint hogy az adott szám völgyszám-e
vagy hegyszám. Ha a szám nem völgyszám és nem hegyszám, vágjuk le a szám
első néhány számjegyét amíg az így kapott szám völgyszámmá vagy hegyszámmá
válik. Ebben az esetben írjuk ki az adott szám azon részét, amely völgyszám
vagy hegyszám, ha létezik ilyen, vagy megfelelő üzenetet, ha nem.*/

#include <iostream>

using namespace std;

void beolvas(unsigned long long& szam) {
	cin >> szam;
	return;
}

unsigned long long vizsgal(unsigned long long& szam) {
	if (szam <= 100) {
		return -3;
	}

	unsigned long long megoldas = 0, masolat = szam, hatvany = 1;
	bool hegy_vege = false, hegy_eleje = false, volgy_vege = false, volgy_eleje = false;
	short prev_szamjegy = masolat % 10 , szamjegy;
	masolat /= 10;

	while (masolat > 0 && (!hegy_eleje || !hegy_vege) && (!volgy_eleje || !volgy_vege)) {

		szamjegy = masolat % 10;
		//ha azonos szamjegyek vannak egymas mellett akkor azokat elmentjuk a megoldasba, ha szuksegunk lesz ra
		while (szamjegy == prev_szamjegy) {
			megoldas = megoldas + prev_szamjegy * hatvany;
			hatvany *= 10;
			masolat /= 10;
			if (masolat == 0) {
				break;
			}
			prev_szamjegy = szamjegy;
			szamjegy = masolat % 10;
		}

		if (szamjegy > prev_szamjegy) {
			//ha elkezd novekedni es meg nem letezik hegy vagy volgy, akkor ez azt jelenti, 
			//hogy a szam vegen van es hegy kezdodik
			if (!hegy_vege && !volgy_vege) {
				hegy_vege = true;
				while (szamjegy > prev_szamjegy) {
					megoldas = megoldas + prev_szamjegy*hatvany;
					hatvany *= 10;
					masolat /= 10;
					if (masolat == 0) {
						break;
					}
					prev_szamjegy = szamjegy;
					szamjegy = masolat % 10;
				}
			}
			//ha letezik mar volgy kezdete akkor a novekedes a volgy befejezeset jelenti
			if (volgy_vege) {
				volgy_eleje = true;
				while (szamjegy > prev_szamjegy) {
					megoldas = megoldas + prev_szamjegy * hatvany;
					hatvany *= 10;
					masolat /= 10;
					if (masolat == 0) {
						break;
					}
					prev_szamjegy = szamjegy;
					szamjegy = masolat % 10;
				}
			}
		}
		if (szamjegy < prev_szamjegy) {
			//ha elkezd csokkenni, es meg nem letezik hegy vagy volgy, akkor ez azt jelenti,
			//hogy a szam vegen van es volgy kezdodik
			if (!volgy_vege && !hegy_vege) {
				volgy_vege = true;
				while (szamjegy < prev_szamjegy) {
					megoldas = megoldas + prev_szamjegy * hatvany;
					hatvany *= 10;
					masolat /= 10;
					if (masolat == 0) {
						break;
					}
					prev_szamjegy = szamjegy;
					szamjegy = masolat % 10;
				}
			}
			//ha letezik mar hegy kezdete akkor a novekedes a hegy befejezeset jelenti
			if (hegy_vege) {
				hegy_eleje = true;
				while (szamjegy < prev_szamjegy) {
					megoldas = megoldas + prev_szamjegy * hatvany;
					hatvany *= 10;
					masolat /= 10;
					if (masolat == 0) {
						break;
					}
					prev_szamjegy = szamjegy;
					szamjegy = masolat % 10;
				}
			}
		}
	}
	megoldas = megoldas + prev_szamjegy * hatvany;

	if (hegy_vege) {
		if (hegy_eleje) {
			//ha a szam nem erte el a 0-at akkor azt jelenti, hogy "hullamos" es a belole kepezheto hegyszamot kell kiirni
			if (masolat > 0) {
				return megoldas;
			}
			return -1;
		}
		else {
			return -3;
		}
	}
	if (volgy_vege) {
		if (volgy_eleje) {
			//ha a szam nem erte el a 0-at akkor azt jelenti, hogy "hullamos" es a belole kepezheto volgyszamot kell kiirni
			if (masolat > 0) {
				return megoldas;
			}
			return -2;
		}
		else {
			return -3;
		}
	}
}

void kiir(unsigned long long& megoldas) {
	if (megoldas == -1) {
		cout << "hegyszam";
		return;
	}
	if (megoldas == -2) {
		cout << "volgyszam";
		return;
	}
	if (megoldas == -3) {
		cout << "nincs benne hegyszam vagy volgyszam";
		return;
	}
	cout << megoldas;
	return;
}

int main() {
	unsigned long long szam;
	beolvas(szam);

	unsigned long long megoldas = vizsgal(szam);

	kiir(megoldas);

	return 0;
}