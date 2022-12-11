/*Boda Norbert
511-es csoport
Lab2/06
Ismerjük két szám prímszám osztóit, határozzuk meg a két szám legkisebb
közös többszörösének prímszám osztóit! (A két számot nem ismerjük, csupán a
prim osztóikat).*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void beolvas(string& osztok) {
	getline(cin, osztok);
	return;
}

void feloszt(string& osztok_s, vector<unsigned long long>& osztok) {
	stringstream osztok_ss;
	osztok_ss << osztok_s;
	unsigned long long temp_szam;
	while (osztok_ss >> temp_szam) {
		osztok.push_back(temp_szam);
	}
	return;
}

//masolas programozasi tetel
void masol(vector<unsigned long long>& osztok, vector<unsigned long long>& eredmeny) {
	for (short i = 0; i < osztok.size(); i++) {
		eredmeny.push_back(osztok[i]);
	}
	return;
}

//egyesites programozasi tetel
void egyesit(vector<unsigned long long>& osztok1, vector<unsigned long long>& osztok2, vector<unsigned long long>& eredmeny) {
	masol(osztok1, eredmeny);
	for (short j = 0; j < osztok2.size(); j++) {
		short i = 0;
		while (i < osztok1.size() && osztok1[i] != osztok2[j]) {
			i++;
		}
		if (i >= osztok1.size()) {
			eredmeny.push_back(osztok2[j]);
		}
	}
	return;
}

void kiir(vector<unsigned long long>& eredmeny) {
	for (short i = 0; i < eredmeny.size(); i++) {
		cout << eredmeny[i] << " ";
	}
	return;
}

int main() {
	string osztok1_s, osztok2_s;
	beolvas(osztok1_s);
	beolvas(osztok2_s);

	vector<unsigned long long> osztok1, osztok2, eredmeny;
	feloszt(osztok1_s, osztok1);
	feloszt(osztok2_s, osztok2);

	egyesit(osztok1, osztok2, eredmeny);

	kiir(eredmeny);

	return 0;
}