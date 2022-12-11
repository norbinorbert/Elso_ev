/*Boda Norbert
511-es csoport
Lab5/03
Adva van egy 𝑛 darab egész számot tartalmazó sorozat. Helyezzünk az
adott számok közé 𝑛 − 1 aritmetikai műveleti jelet a (+, −, *, /) halmazból, úgy,
hogy a kifejezés értéke legyen egyenlő egy adott 𝑥 számmal! A kifejezés értéke
minden lépésben legyen egész szám! A műveleteket nem a matematikából ismert
operátorprecedencia szerint végezzük, hanem megjelenésük sorrendjében.*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void beolvas(int& darab, vector<int>& szamok, int& eredmeny) {
	cin >> darab;
	szamok.resize(darab);
	for (int i = 0; i < darab; i++) {
		cin >> szamok[i];
	}
	cin >> eredmeny;
}

int temp_eredmeny_kiszamolasa(vector<int>& szamok, vector<char>& temp_muveletek, int& eredmeny) {
	int temp_eredmeny = szamok[0];
	for (int i = 1; i < szamok.size(); i++) {

		//0-val valo osztas lekezelese
		if (szamok[i] == 0 && temp_muveletek[i - 1] == '/') {
			if (eredmeny != 0) {
				return 0;
			}
			else {
				return -1;
			}
		}

		//olyan osztas lekezelese amely nem egesz szamot eredmenyez
		else if ((temp_muveletek[i - 1] == '/') && (temp_eredmeny % szamok[i] != 0)) {
			if (eredmeny != 0) {
				return 0;
			}
			else {
				return -1;
			}
		}

		//megfelelo muvelet elvegzese
		else {
			if (temp_muveletek[i - 1] == '+') {
				temp_eredmeny += szamok[i];
			}
			if (temp_muveletek[i - 1] == '-') {
				temp_eredmeny -= szamok[i];
			}
			if (temp_muveletek[i - 1] == '*') {
				temp_eredmeny *= szamok[i];
			}
			if (temp_muveletek[i - 1] == '/') {
				temp_eredmeny /= szamok[i];
			}
		}
	}
	return temp_eredmeny;
}

string temp_megoldas_felepitese(vector<int>& szamok, int& eredmeny, vector<char>& temp_muveletek) {
	string str_eredmeny = to_string(eredmeny), szam = to_string(szamok[0]);
	string temp_megoldas = str_eredmeny + '=' + szam;

	for (int i = 0; i < temp_muveletek.size(); i++) {
		szam = to_string(szamok[i + 1]);
		temp_megoldas = temp_megoldas + temp_muveletek[i] + szam;
	}

	return temp_megoldas;
}

void general_muveletek(vector<int>& szamok, vector<char>& jelek, int& eredmeny, int szamlalo, vector<char>& temp_muveletek, vector<string>& megoldas) {
	if (szamlalo == szamok.size() - 1) {
		int temp_eredmeny = temp_eredmeny_kiszamolasa(szamok, temp_muveletek, eredmeny);
		//megnezi ha a muveleteket felhasznalva jo eredmenyt kap
		if (temp_eredmeny == eredmeny) {
			//felepiti a jelenlegi megoldas stringjet es hozzaadja a megoldas vectorhoz
			string temp_megoldas = temp_megoldas_felepitese(szamok, eredmeny, temp_muveletek);
			megoldas.push_back(temp_megoldas);
		}
		return;
	}

	for (int i = 0; i < jelek.size(); i++) {
		temp_muveletek[szamlalo] = jelek[i];
		general_muveletek(szamok, jelek, eredmeny, szamlalo + 1, temp_muveletek, megoldas);
	}
}

vector<string> muveletek(int& darab, vector<int>& szamok, int& eredmeny) {
	vector<string> megoldas;
	vector<char> jelek = { '+', '-', '*', '/' }, temp_muveletek(darab-1);

	general_muveletek(szamok, jelek, eredmeny, 0, temp_muveletek, megoldas);
	return megoldas;
}

void kiir(vector<string>& megoldas) {
	if (megoldas.size() == 0) {
		cout << -1;
	}
	for (int i = 0; i < megoldas.size(); i++) {
		cout << megoldas[i] << endl;
	}
}

int main() {
	int darab, eredmeny;
	vector<int> szamok;
	beolvas(darab, szamok, eredmeny);

	vector<string> megoldas = muveletek(darab, szamok, eredmeny);
	
	kiir(megoldas);
	return 0;
}