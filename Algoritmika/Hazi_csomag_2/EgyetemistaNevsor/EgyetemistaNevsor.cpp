/*Boda Norbert
511-es csoport
Lab2/07
Adottak az elsőéves egyetemisták névsorai (abc sorrendben), csoportonként.
Állítsunk elő ezekből egyetlen névsort, mely szintén abc sorrendben van!*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void beolvas(vector<string>& csoport) {
	string temp;
	short csoport_nagysag;
	cin >> csoport_nagysag;
	while (csoport.size() != 0) {
		csoport.pop_back();
	}
	for (short i = 0; i <= csoport_nagysag; i++) {
		getline(cin, temp);
		csoport.push_back(temp);
	}
	return;
}

void masol(vector<string>& bemenet, vector<string>& cel) {
	cel.clear();
	for (short i = 0; i < bemenet.size(); i++) {
		cel.push_back(bemenet[i]);
	}
	bemenet.clear();
	return;
}

//osszefesules programozasi tetel
void osszefesules(vector<string>& elso, vector<string>& masodik, vector<string>& eredmeny) {
	string orszem = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	//nem letezhet olyan nev a vectorban, amely az "orszem" utan kovetkezhet az abeceben, ezert ezt a vectorok vegere tesszuk
	elso.push_back(orszem);
	masodik.push_back(orszem);

	short i = 0, j = 0;
	while (i < elso.size()-1 || j < masodik.size()-1) {
		if (strcmp(elso[i].c_str(), masodik[j].c_str()) < 0) {
			eredmeny.push_back(elso[i]);
			i++;
		}
		else {
			eredmeny.push_back(masodik[j]);
			j++;
		}
	}

	return;
}

void kiir(vector<string>& eredmeny, int db) {
	for (short i = db; i < eredmeny.size(); i++) {
		cout << eredmeny[i] << endl;
	}
	return;
}

int main() {
	short csoportok_szama; 
	cin >> csoportok_szama;
	vector<string> csoport_elozo, csoport_mostani, temp_eredmeny;

	if (csoportok_szama == 1) {
		beolvas(csoport_elozo);
		kiir(csoport_elozo, csoportok_szama);
		return 0;
	}

	for (short i = 0; i < csoportok_szama; i++) {
		csoport_mostani.clear();

		beolvas(csoport_mostani);

		osszefesules(csoport_elozo, csoport_mostani, temp_eredmeny);

		masol(temp_eredmeny, csoport_elozo);
	}

	kiir(csoport_elozo, csoportok_szama);
	return 0;
}