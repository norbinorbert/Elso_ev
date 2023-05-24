#include "binomialis_kupac.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <thread>
#include <locale>

using namespace std;

#define MAX_FELADAT_HOSSZ 5000
#define MAX_FELADATOK_SZAMA 100

void beolvas(queue<pair<int, binomialis_kupac*>>&);
void sablon_szoveg_kiirasa(int);

int main() {
	locale::global(locale("")); 
	cout << "\033[7m";
	cout << "Üdv újra!" << endl;
	int feladatok_szama = 0;
	queue<pair<int, binomialis_kupac*>> sor;
	binomialis_kupac server;
	beolvas(sor);
	int opcio = -1;
	while (opcio != 0) {
		sablon_szoveg_kiirasa(feladatok_szama);
		cin >> opcio;
		switch (opcio) {
		case 1: {
			system("CLS");
			if (feladatok_szama == 0) {
				cout << "Nincs elvégezendö feladat." << endl;
			}
			else {
				unsigned int ido = server.minimum();
				server.torol_minimum();
				feladatok_szama--;
				cout << "Feladat elvégzése..." << endl;
				this_thread::sleep_for(chrono::milliseconds(ido));
				cout << "Feladat elvégezve." << endl;
			}
			break;
		}
		case 2: {
			if (feladatok_szama == 0) {
				system("CLS");
				cout << "Nincs elvégezendö feladat." << endl;
				break;
			}
			cout << "Hány feladatot szeretne elvégezni? Írja be a számot: ";
			int szam;
			cin >> szam;
			system("CLS");
			if (szam > feladatok_szama) {
				cout << "Nincs ennyi feladat. Maradék feladat elvégzése..." << endl;
				szam = feladatok_szama;
			}
			else {
				cout << "Feladatok elvégzése (ez lehet bele fog telni egy kis idöbe)..." << endl;
			}
			for (int i = 0; i < szam; i++) {
				unsigned int ido = server.minimum();
				server.torol_minimum();
				feladatok_szama--;
				this_thread::sleep_for(chrono::milliseconds(ido));
			}
			cout << szam << " feladat elvégezve." << endl;
			break;
		}
		case 3: {
			if (feladatok_szama == MAX_FELADATOK_SZAMA) {
				system("CLS");
				cout << "A server tele van." << endl;
				break;
			}
			cout << "Adja meg kb mennyi idöt tart a feladat elvégzése (milliszekundumban): ";
			unsigned int ido;
			cin >> ido;
			system("CLS");
			if (ido > MAX_FELADAT_HOSSZ) {
				cout << "Sajnálom, de ilyen hosszú feladatot nem tudok elvégezni." << endl;
				break;
			}
			server.beszur(ido);
			feladatok_szama++;
			cout << ido << " milliszekundumot tartó feladat beszúrva." << endl;
			break;
		}
		case 4: {
			if (sor.size() == 0) {
				system("CLS");
				cout << "A várakozási sor üres" << endl;
				break;
			}
			if (feladatok_szama + sor.front().first > MAX_FELADATOK_SZAMA) {
				system("CLS");
				cout << "Nem lehet beengedni a következö felhasználót, mivel nem fér el az összes feladat a serverre" << endl;
				cout << "Kérem végezzen el legalább " << feladatok_szama + sor.front().first - MAX_FELADATOK_SZAMA << " feladatot elöször" << endl;
				break;
			}
			binomialis_kupac* tmp = sor.front().second;
			int felhasznalo_feladatok_szama = sor.front().first;
			sor.pop();
			server.egyesit(tmp);
			feladatok_szama += felhasznalo_feladatok_szama;
			system("CLS");
			cout << "Felhasználó beengedve." << endl;
			break;
		}
		case 5: {
			system("CLS");
			cout << "A sorban " << sor.size() << " felhasználó várakozik." << endl;
			break;
		}
		case 6: {
			cout << "Add meg, hogy a felhasználó hány feladatot szeretne elvégezni: ";
			int szam;
			cin >> szam;
			binomialis_kupac* felhasznalo = new binomialis_kupac;
			for (int i = 1; i <= szam; i++) {
				cout << endl << "Add meg, hogy a(z) " << i << ". feladat elvégzése kb mennyi idöt tart (milliszekundumban): ";
				unsigned ido;
				cin >> ido;
				felhasznalo->beszur(ido);
			}
			sor.push({ szam, felhasznalo });
			system("CLS");
			cout << "Új felhasználó beszúrva." << endl;
			break;
		}
		case 7: {
			system("CLS");
			if (feladatok_szama > 0) {
				cout << "A következö feladat " << server.minimum() << " milliszekundumba fog telni." << endl;
			}
			else {
				cout << "Nincs elvégezendö feladat." << endl;
			}
			break;
		}
		case 0: {
			cout << "Server leállítása..." << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
			break;
		}
		default: {
			system("CLS");
			cout << "Nincs ilyen opció!" << endl;
			break;
		}
		}
	}
	return 0;
}

void beolvas(queue<pair<int, binomialis_kupac*>>& sor) {
	ifstream fin("be1.txt");
	int felhasznalok_szama;
	fin >> felhasznalok_szama;
	for (int i = 0; i < felhasznalok_szama; i++) {
		int felhasznalo_feladatok_szama;
		fin >> felhasznalo_feladatok_szama;
		binomialis_kupac* felhasznalo = new binomialis_kupac;
		for (int i = 0; i < felhasznalo_feladatok_szama; i++) {
			int feladat_ideje;
			fin >> feladat_ideje;
			felhasznalo->beszur(feladat_ideje);
		}
		sor.push({ felhasznalo_feladatok_szama, felhasznalo });
	}
	fin.close();
}

void sablon_szoveg_kiirasa(int feladatok_szama) {
	cout << endl << "A server jelenleg " << feladatok_szama << " feladatot tartalmaz" << endl;
	cout << "1. Egy feladat elvégzése" << endl;
	cout << "2. Több feladat elvégzése" << endl;
	cout << "3. Új feladat létrehozása" << endl;
	cout << "4. Következö felhasználó beengedése a serverre" << endl;
	cout << "5. Várakozási sor információinak lekérdezése" << endl;
	cout << "6. Új felhasználó beszúrása a várakozási sorba" << endl;
	cout << "7. Következö feladat idejének lekérdezése" << endl;
	cout << endl << "0. Server leállítása" << endl;
	cout << endl << "Válasszon egy opciót: ";
}