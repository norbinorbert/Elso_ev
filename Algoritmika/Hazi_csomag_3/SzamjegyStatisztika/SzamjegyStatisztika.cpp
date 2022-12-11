/*Boda Norbert
511-es csoport
Lab3/10
Határozzuk meg, hogy melyik számjegyet hányszor kell leírnunk, ha egyenként
minden természetes számot le akarunk írni az [𝑥, 𝑦] intervallumból!*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void beolvas(string& elso, string& masodik) {
	cin >> elso >> masodik;
	return;
}

//megszamolja, hogy hanyszor kell leirni egy szamjegyet 1 es a szam kozott
void vizsgal(string& szam, vector<unsigned long long>& statisztika) {
	string szam_masolat = szam;
	int hatvany = szam.size() - 1, tizes_szorzo = 1, szamlalo = 1, prev_szamjegy = 0;

	for (int i = 1; i < hatvany; i++) {
		tizes_szorzo *= 10;
		szamlalo++;
	}

	for (int i = 0; i < szam.size(); i++) {
		int szamjegy = (int)(szam[i]) - 48;

		//legutolso szamjegy lekezelese
		if (i == szam.size() - 1) {
			int j;
			if (szam.size() == 1) {
				j = 1;
			}
			else {
				//pelda: 123 --> 023
				szam_masolat[i - 1] = '0';
				//pelda: temp = 23
				int temp = stoi(szam_masolat);
				//pelda: statisztika[1] += 24 (100-tol 123-ig 24 darab van)
				statisztika[prev_szamjegy] += temp + 1;

				//ha a szam tobb, mint 2 szamjegyu akkor a nullasok szamat is kell novelni
				if (szam.size() == 2) {
					j = 1;
				}
				else {
					j = 0;
				}

				while (j < prev_szamjegy) {
					statisztika[j] += 10;
					j++;
				}
				j = 0;
			}
			while (j <= szamjegy) {
				statisztika[j]++;
				j++;
			}
			break;
		}

		//n * 10^(n-1) -> 10 hatvanyokig egy adott szamjegy 1-9 kozott
		for (int j = 0; j <= 9; j++) {
			statisztika[j] += szamjegy * szamlalo * tizes_szorzo;
		}
		if (i != 0) {
			szam_masolat[i-1] = '0';
			int temp = stoi(szam_masolat);
			statisztika[prev_szamjegy] += temp + 1;

			for (int j = 1; j < prev_szamjegy; j++) {
				statisztika[j] += tizes_szorzo*100;
			}
		}
		tizes_szorzo /= 10;
		szamlalo--;
		prev_szamjegy = szamjegy;
	}
	//0-asok kivonasa, mert beloluk kevesebb szokott lenni, mint a tobbi szamjegybol
	if (szam.size() > 2) {
		statisztika[0] -= 11;
	}
	if (szam.size() == 2) {
		statisztika[0] -= 1;
	}

	return;
}

//az elso szam szamjegyei hozzaadasa a statisztikahoz
void szamjegy_hozzaadas(vector<unsigned long long>& statisztika1, string& elso) {
	int elso_masolat = stoi(elso);
	while (elso_masolat > 0) {
		statisztika1[elso_masolat % 10]--;
		elso_masolat /= 10;
	}
	return;
}

//vegeredmeny vector kiszamitasa
void kulonbseg(vector<unsigned long long>& statisztika, vector<unsigned long long>& statisztika2, vector<unsigned long long>& statisztika1) {
	for (short i = 0; i <= 9; i++) {
		statisztika[i] = statisztika2[i] - statisztika1[i];
	}
	return;
}

//0 szamjegyek kezelese, amelyek a "vizsgal" alporgramban nem lettek helyesen kiszamolva
void nullasok_kezelese(string& szam, vector<unsigned long long>& statisztika){
	int hatvany = 100;
	int szam_masolat = stoi(szam);
	if (szam_masolat >= 1000) {
		szam_masolat /= 100;
		while (szam_masolat > 0) {
			if (szam_masolat % 10 == 0) {
				statisztika[0] -= hatvany;
			}
			szam_masolat /= 10;
			hatvany *= 10;
		}
	}
	return;
}

void kiir(vector<unsigned long long>& statisztika) {
	for (short i = 0; i <= 9; i++) {
		cout << statisztika[i] << " ";
	}
	return;
}

int main() {
	string elso, masodik;
	beolvas(elso, masodik);

	//10 szamjegy miatt 10-es nagysagu vectorok kellenek
	vector<unsigned long long> statisztika1(10), statisztika2(10), statisztika(10);
	vizsgal(elso, statisztika1);
	vizsgal(masodik, statisztika2);

	szamjegy_hozzaadas(statisztika1, elso);

	nullasok_kezelese(elso, statisztika1);
	nullasok_kezelese(masodik, statisztika2);

	kulonbseg(statisztika, statisztika2, statisztika1);

	kiir(statisztika);
	return 0;
}