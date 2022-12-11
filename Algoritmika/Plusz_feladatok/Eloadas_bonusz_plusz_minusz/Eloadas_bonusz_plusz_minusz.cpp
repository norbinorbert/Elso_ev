/*Boda Norbert
511-es csoport
Adottak n és s természetes számok (1 ≤ n ≤ 1000, 1 ≤ s ≤ 1000000).
Elhelyezhetjük-e a + és - műveleti jeleket az 1, 2, . . . , n számok közé (ebben a
sorrendben), úgy, hogy az eredmény s legyen? Írjunk ki egy tetszőleges megoldást,
vagy -1-et, ha nem létezik ilyen!*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(short& szamok_szama, int& eredmeny) {
	cin >> szamok_szama >> eredmeny;
}

string megoldas_felepitese(int& eredmeny, vector<char>& temp_muveletek) {
	string megoldas = "1"; //mindig 1-el fog kezdodni a string

	for (short i = 0; i < temp_muveletek.size(); i++) {
		//kiteszi a muveleti jeleket, illetve a szamokat; mivel a ciklus i=0-val kezdodik, 
		//es az elso szam amit ki kell tenni(ha kell) 2-es, ezert i+2-t ad mindig hozza a megoldas stringhez
		megoldas = megoldas + temp_muveletek[i] + to_string(i+2);
	}

	return megoldas;
}

void general_muveletek(short& szamok_szama, vector<char>& jelek, int& eredmeny, int szamlalo, vector<char>& temp_muveletek, bool& van_megoldas, string& megoldas, int temp_eredmeny, short kovetkezo_szam) {
	if (szamlalo == szamok_szama - 1) {
		if (temp_eredmeny == eredmeny) {
			//ha jo az eredmeny akkor felepiti a megoldas stringet es egy bool valtozot igazra allit, hogy ne folytatodjon az alprogram
			megoldas = megoldas_felepitese(eredmeny, temp_muveletek);
			van_megoldas = true;
		}
		return;
	}
	//amig nincs helyes megoldas, addig a "+" es "-" jeleket az osszes lehetseges modon kiteszi a szamok koze
	if (!van_megoldas) {
		for (int i = 0; i < jelek.size(); i++) {
			if (!van_megoldas) {
				temp_muveletek[szamlalo] = jelek[i];
				if (jelek[i] == '+') {
					general_muveletek(szamok_szama, jelek, eredmeny, szamlalo + 1, temp_muveletek, van_megoldas, megoldas, temp_eredmeny + kovetkezo_szam, kovetkezo_szam + 1);
				}
				else {
					general_muveletek(szamok_szama, jelek, eredmeny, szamlalo + 1, temp_muveletek, van_megoldas, megoldas, temp_eredmeny - kovetkezo_szam, kovetkezo_szam + 1);
				}
			}
		}
	}
}

string muveletek(short& szamok_szama, int& eredmeny) {
	vector<char> jelek = { '+', '-'}, temp_muveletek(szamok_szama - 1); //mindig "szamok_szama-1" muvelet lesz kiteve, illetve csak 2 muveletet kell nezni
	bool van_megoldas = false;
	string megoldas = "";
	//Gauss kepletet hasznalva a legnagyobb szam amit el lehet erni az akkor van, ha minden szam koze + jelet teszunk, ennek az eredmenye pedig n(n+1)/2 lesz
	if (eredmeny <= (szamok_szama * (szamok_szama + 1)) / 2) {
		general_muveletek(szamok_szama, jelek, eredmeny, 0, temp_muveletek, van_megoldas, megoldas, 1, 2);
	}
	return megoldas;
}

void kiir(string& megoldas) {
	//ha nincs megoldas akkor -1-et ir ki
	if (megoldas == "") {
		cout << -1;
	}
	else {
		cout << megoldas;
	}
}

int main() {
	short szamok_szama;
	int eredmeny;
	beolvas(szamok_szama, eredmeny);

	string megoldas = muveletek(szamok_szama, eredmeny);

	kiir(megoldas);
	return 0;
}