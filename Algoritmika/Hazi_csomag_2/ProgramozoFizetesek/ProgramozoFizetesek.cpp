/*Boda Norbert
511-es
Lab2/05
Adott n programozó fizetése. Válogassuk szét őket a fizetésük alapján. Az
első csoportba azok kerülnek, akiknek a fizetésük nagyobb mint felso_hatar EUR, a
másodikba a megmaradtak közül azok, akiknek a fizetése nagyobb mint also_hatar EUR,
a harmadikban maradnak a többiek (a sorrend nem fontos). Törekedjünk egyetlen
tömbbel dolgozni és abban elvégezni a szétválogatást, nem elég a kiíratásban
csoportokra osztani a számokat.*/

#include <iostream>
#include <vector>

#define also_hatar 700
#define felso_hatar 1000

using namespace std;

void beolvas(int& fizetesek_szama, vector<int>& fizetesek) {
	cin >> fizetesek_szama;
	int temp_fizetes;
	for (int i = 0; i < fizetesek_szama; i++) {
		cin >> temp_fizetes;
		fizetesek.push_back(temp_fizetes);
	}
	return;
}

void kiir(vector<int>& fizetesek) {
	bool kozepes = false, kicsi = false;
	for (int i = 0; i < fizetesek.size(); i++) {
		if (fizetesek[i] <= felso_hatar && !kozepes) {
			kozepes = true;
			cout << endl;
		}
		if (fizetesek[i] <= also_hatar && !kicsi) {
			kicsi = true;
			cout << endl;
		}
		cout << fizetesek[i] << " ";
		if (i == fizetesek.size() - 1) {
			if (!kozepes) {
				cout << endl;
			}
			if (!kicsi) {
				cout << endl;
			}
		}
	}
	return;
}

void rendez(vector <int>& fizetesek, int hatar, int& e, int u) {
	//ha 1 elemu a vector akkor nem kell rendezni
	if (fizetesek.size() == 1) {
		return;
	}

	//szetvalogatas programozasi tetel
	int seged = fizetesek[e];
	while (e < u) {
		while (e < u && fizetesek[u] <= hatar) {
			u--;
		}
		if (e < u) {
			fizetesek[e] = fizetesek[u];
			e++;
			while (e < u && fizetesek[e] > hatar) {
				e++;
			}
		}
		if (e < u) {
			fizetesek[u] = fizetesek[e];
			u--;
		}
	}
	fizetesek[e] = seged;
	if (fizetesek[e] > hatar) {
		e++;
	}
	return;
}

int main() {
	int	fizetesek_szama;
	vector<int> fizetesek;

	beolvas(fizetesek_szama, fizetesek);

	int e = 0, u = fizetesek.size() - 1;
	rendez(fizetesek, felso_hatar, e, u);
	rendez(fizetesek, also_hatar, e, u);

	kiir(fizetesek);

	return 0;
}