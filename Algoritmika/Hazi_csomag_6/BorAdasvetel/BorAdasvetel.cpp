/*Boda Norbert
511-es csoport
Lab6/03
Egy falu főútcáján 𝑛 lakos él, minden két egymás melletti ház között
ugyanakkora a távolság. A falu jó bortermő vidéken található, így a lakók
szívesen fogyasztanak, de adnak is el bort. Érdekes módon a falun belül a
kereslet és a kínálat mindig egyenlő. Tudván, hogy két egymás melletti ház
között szállítani egy liter bort mindig egy egységnyi munkába kerül és ismervén,
hogy melyik lakos hány liter bort szeretne eladni vagy vásárolni, határozzuk
meg a minimális munkamennyiséget, amely szükséges ahhoz, hogy minden lakos
igénye ki legyen elégítve.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& lakosok_szama, vector<int>& bor) {
	cin >> lakosok_szama;
	bor.resize(lakosok_szama);
	for (int i = 0; i < lakosok_szama; i++) {
		cin >> bor[i];
	}
}

unsigned long long munka_szamitas(int& lakosok_szama, vector<int>& bor) {
	if (bor.size() == 1) {
		return 0;
	}
	long long jelenlegi_bor = 0;
	unsigned long long munka = 0;
	int elozo_vasarlo_index = 0;
	//megkeresi melyik lakos akar vasarolni
	while (bor[elozo_vasarlo_index] >= 0) {
		elozo_vasarlo_index++;
	}
	for (int i = 0; i < bor.size(); i++) {
		while (bor[i] > 0) {
			//ha a kereslet nagyobb vagy egyenlo, mint a jelenlegi lakos kinalata akkor az osszes bort eladja
			if (bor[i] <= abs(bor[elozo_vasarlo_index])) {
				jelenlegi_bor += bor[i];
				bor[i] = 0;
				munka += jelenlegi_bor * abs(i - elozo_vasarlo_index);
				bor[elozo_vasarlo_index] += jelenlegi_bor;
				jelenlegi_bor = 0;
			}
			//ha a kereslet kisebb, mint a jelenegi lakos kinalata,
			//akkor csak a bor egy reszet adja el a jelenlegi vasarlonak es a tobbit egy masiknak
			else {
				jelenlegi_bor += abs(bor[elozo_vasarlo_index]);
				bor[i] -= abs(bor[elozo_vasarlo_index]); 
				munka += jelenlegi_bor * abs(i - elozo_vasarlo_index);
				bor[elozo_vasarlo_index] += jelenlegi_bor;
				jelenlegi_bor = 0;
				while (elozo_vasarlo_index < bor.size() - 1 && bor[elozo_vasarlo_index] >= 0) {
					elozo_vasarlo_index++;
				}
			}
		}
	}
	return munka;
}

void kiir(unsigned long long& munka) {
	cout << munka;
}

int main() {
	int lakosok_szama;
	vector<int> bor;
	beolvas(lakosok_szama, bor);

	unsigned long long munka = munka_szamitas(lakosok_szama, bor);

	kiir(munka);
	return 0;
}