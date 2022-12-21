/*Boda Norbert
511-es csoport
Lab6/04
Adott egy 𝑛 egész szám. Határozzuk meg a legkisebb olyan 𝑚 > 0 természetes
számot, amelyre 𝑚 számjegyeinek szorzata egyenlő 𝑛-el!*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void beolvas(int& szam) {
	cin >> szam;
}

short torzstenyezokre_bontas(int& szam, vector<int>& torzstenyezok) {
	int szam_masolat = szam;
	short i = 2;
	while (i <= szam_masolat && szam_masolat != 1) {
		if (i >= 10) {
			return i;
		}
		while (szam_masolat % i == 0) {
			torzstenyezok[i]++;
			szam_masolat /= i;
		}
		i++;
	}
	return i - 1;
}

string szamjegy_sorozat(int& szam) {
	//ha a szam 0-as, akkor 10-et kell kiirni, mert m>0
	if (szam == 0) {
		return "10";
	}
	if (szam == 1) {
		return "1";
	}
	vector<int> szamjegyek(10); //a legnagyobb szamjegy amire szukseg lesz az a 9-es, ezert 10 elemu a vektor(0-tol szamozva)
	short legnagyobb_torzstenyezo = torzstenyezokre_bontas(szam, szamjegyek);
	//ha torzstenyezokre bontjuk a szamot es a legnagyobb torzstenyezo tobb, mint 2 szamjegyu, akkor nem lehet szorzatkent felirni
	if (legnagyobb_torzstenyezo >= 10) {
		return "-1";
	}
	//a 3-asokat 9-re alakitja, igy rovidebb lesz a szam
	while (szamjegyek[3] > 1) {
		szamjegyek[9]++;
		szamjegyek[3] -= 2;
	}
	//a 2-eseket 8-ra alakitja, igy rovidebb lesz a szam
	while (szamjegyek[2] > 2) {
		szamjegyek[8]++;
		szamjegyek[2] -= 3;
	}
	//ha maradt meg 3-as es 2-es, akkor 6-ost alkot belole
	if (szamjegyek[3] == 1 && szamjegyek[2] > 0) {
		szamjegyek[6]++;
		szamjegyek[3]--;
		szamjegyek[2]--;
	}
	//ha 2 darab 2-es maradt akkor 4-est alkot belole
	if (szamjegyek[2] == 2) {
		szamjegyek[4]++;
		szamjegyek[2] -= 2;
	}
	//stringbe epul fel a szam, hogy nagyon nagy bemenetre is biztosan mukodjon
	string megoldas = "";
	for (int i = 2; i <= 9; i++) {
		while (szamjegyek[i] > 0) {
			megoldas += to_string(i);
			szamjegyek[i]--;
		}
	}
	return megoldas;
}

void kiir(string& megoldas) {
	cout << megoldas;
}

int main() {
	int szam;
	beolvas(szam);

	string megoldas = szamjegy_sorozat(szam);

	kiir(megoldas);
	return 0;
}