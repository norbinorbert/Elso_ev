/*Boda Norbert
511-es csoport
Lab7/10
Adott egy 𝑛 számjegyű szám. Emeljük négyzetre!*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(short& szamjegyek_szama, short& parok_szama, vector<pair<int, int>>& kiirando_parok, string& szam){
	cin >> szamjegyek_szama >> parok_szama;
	for (short i = 0; i < parok_szama; i++) {
		int first, second;
		cin >> first >> second;
		kiirando_parok.push_back({ first, second });
	}
	cin >> szam;
}

//string osszeadas
void osszead(string& szam1, string& szam2) {
	unsigned int i = 0, carry = 0;
	while (i < szam1.size() && i < szam2.size()) {
		short szamjegy = (szam1[szam1.size() - i - 1] - '0') + (szam2[szam2.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1[szam1.size() - i - 1] = szamjegy + '0';
		i++;
	}
	while (i < szam1.size()) {
		short szamjegy = (szam1[szam1.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1[szam1.size() - i - 1] = szamjegy + '0';
		i++;
	}
	while (i < szam2.size()) {
		short szamjegy = (szam2[szam2.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1 = to_string(szamjegy) + szam1;
		i++;
	}
	if (carry) {
		szam1 = "1" + szam1;
	}
}

//string kivonas
void kivon(string& szam1, string& szam2) {
	unsigned int i = 0;
	while (i < szam2.size()) {
		if (szam1[szam1.size() - i - 1] >= szam2[szam2.size() - i - 1]) {
			short szamjegy = (szam1[szam1.size() - i - 1] - '0') - (szam2[szam2.size() - i - 1] - '0');
			szam1[szam1.size() - i - 1] = szamjegy + '0';
		}
		else {
			short szamjegy = ((szam1[szam1.size() - i - 1] - '0') + 10) - (szam2[szam2.size() - i - 1] - '0');
			szam1[szam1.size() - i - 1] = szamjegy + '0';
			unsigned int temp_index = i;
			while (szam1[szam1.size() - temp_index - 2] == '0') {
				szam1[szam1.size() - temp_index - 2] = '9';
				temp_index++;
			}
			szamjegy = (szam1[szam1.size() - temp_index - 2] - '0' - 1);
			szam1[szam1.size() - temp_index - 2] = szamjegy + '0';
		}
		i++;
	}
}

//ha a string elejen leteznek felesleges nullasok akkor azokat eltunteti
void nullasok_eltuntetese(string& szam) {
	if (szam[0] == '0') {
		unsigned int j = 0;
		while (j < szam.size() && szam[j] == '0') {
			j++;
		}
		string masolat = "";
		if (j < szam.size()) {
			while (j < szam.size()) {
				masolat = masolat + szam[j];
				j++;
			}
			szam = masolat;
		}
		else {
			szam = "0";
		}
	}
}

//Karatsuba algoritmusa stringekre atalakitva
string Karatsuba(string szam, short szamjegyek_szama) {
	if (szamjegyek_szama <= 9) { 
		//unsigned long long alakban ossze lehet szorozni legtobb 9 szamjegyu szamokat
		unsigned long long eredmeny = stoull(szam);
		eredmeny = eredmeny * eredmeny;
		return to_string(eredmeny);
	}
	else {
		short uj_szamjegyek_szama = szamjegyek_szama / 2;
		string a, b; //a = szam / (10^uj_szamjegyek_szama); b = szam % (10^uj_szamjegyek_szama)
		short i = 0;
		while (i < uj_szamjegyek_szama) {
			a = a + szam[i];
			i++;
		}
		while (i < szamjegyek_szama) {
			b = b + szam[i];
			i++;
		}

		string osszeg = a;
		osszead(osszeg, b); //osszeg = a + b

		string e = Karatsuba(a, a.size()); //e = a^2
		nullasok_eltuntetese(e);

		string f = Karatsuba(b, b.size()); //f = b^2
		nullasok_eltuntetese(f);

		string g = Karatsuba(osszeg, osszeg.size()); //g = (a+b)^2
		nullasok_eltuntetese(g);

		string reszeredmeny1 = e, reszeredmeny2 = g;
		kivon(reszeredmeny2, e);
		kivon(reszeredmeny2, f); //reszeredmeny2 = (g - e - f)

		if (szamjegyek_szama % 2 == 1) {
			uj_szamjegyek_szama++;
		}

		for (int i = 0; i < 2 * uj_szamjegyek_szama; i++) {
			reszeredmeny1 = reszeredmeny1 + "0"; //reszeredmeny1 = (10^(2*uj_szamjegyek_szama)) * e
		}
		for (int i = 0; i < uj_szamjegyek_szama; i++) {
			reszeredmeny2 = reszeredmeny2 + "0"; //reszeredmeny2 = (10^uj_szamjegyek_szama) * (g - e - f)
		}
		osszead(reszeredmeny1, reszeredmeny2);
		osszead(reszeredmeny1, f);

		return reszeredmeny1;
	}
}

void kiir(string megoldas, vector<pair<int, int>>& kiirando_parok) {
	for (unsigned int i = 0; i < kiirando_parok.size(); i++) {
		for (int j = kiirando_parok[i].first - 1; j <= kiirando_parok[i].second - 1; j++) {
			cout << megoldas[j];
		}
		cout << endl;
	}
}

int main() {
	short szamjegyek_szama, parok_szama;
	vector<pair<int, int>> kiirando_parok;
	string szam;
	beolvas(szamjegyek_szama, parok_szama, kiirando_parok, szam);
	
	string megoldas = Karatsuba(szam, szamjegyek_szama);
	
	kiir(megoldas, kiirando_parok);
	return 0;
}