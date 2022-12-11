/*Boda Norbert
511-es csoport
Lab5/02
Helyezzünk el 𝑛 darab királynőt egy 𝑛 × 𝑛-es sakktáblán minden lehetséges
módon, úgy, hogy ne üssék egymást. Számoljuk meg, hogy hányféleképpen
lehetséges ez és írassuk ki a megadott sorszámú konfigurációkat a lexikografikus
sorrendet tekintve.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(int& sakktabla_merete, int& megoldasok_szama, vector<unsigned long long>& konfiguraciok) {
	cin >> sakktabla_merete >> megoldasok_szama;
	konfiguraciok.resize(megoldasok_szama);
	for (int i = 0; i < megoldasok_szama; i++) {
		cin >> konfiguraciok[i];
	}
}

void general_kiralynok(int& sakktabla_merete, int& konfiguracio_index, vector<unsigned long long>& konfiguraciok, vector<bool>& oszlop, vector<bool>& foatlo,
	vector<bool>& mellekatlo, vector<vector<string>>& temp_megoldas, vector<vector<vector<string>>>& megoldasok, int sor, unsigned long long& megoldasok_szama) {
	if (sor == sakktabla_merete) {
		megoldasok_szama++;
		for (int i = 0; i < konfiguraciok.size(); i++) {
			//ha a jelenlegi eredmenyt kerte a bemenet akkor azt lementi a megfelelo helyre
			if (megoldasok_szama == konfiguraciok[i]) {
				for (int j = 0; j < megoldasok[i].size(); j++) {
					for (int k = 0; k < megoldasok[i][j].size(); k++) {
						megoldasok[i][j][k] = temp_megoldas[j][k];
					}
				}
			}
		}
		return;
	}
	for (int i = 0; i < sakktabla_merete; i++) {
		//ha le lehet tenni kiralynot a jelenlegi poziciora akkor ezt megteszi es meghivja a kovetkezo sorra a fuggvenyt
		if (!oszlop[i] && !foatlo[sor - i + sakktabla_merete - 1] && !mellekatlo[sor+i]) {
			oszlop[i] = true;
			mellekatlo[sor + i] = true;
			foatlo[sor - i + sakktabla_merete - 1] = true;
			temp_megoldas[sor][i] = 'Q';
			general_kiralynok(sakktabla_merete, konfiguracio_index, konfiguraciok, oszlop, foatlo, mellekatlo, temp_megoldas, megoldasok, sor + 1, megoldasok_szama);
			temp_megoldas[sor][i] = '.';
			foatlo[sor - i + sakktabla_merete - 1] = false;
			mellekatlo[sor + i] = false;
			oszlop[i] = false;
		}
	}
}

vector<vector<vector<string>>> kiralynok(int& sakktabla_merete, int& kiirando_megoldasok_szama, vector<unsigned long long>& konfiguraciok, unsigned long long& megoldasok_szama) {
	vector<vector<vector<string>>> megoldasok(kiirando_megoldasok_szama, vector<vector<string>>(sakktabla_merete, vector<string>(sakktabla_merete, ".")));
	vector<vector<string>> temp_megoldas(sakktabla_merete, vector<string>(sakktabla_merete, "."));
	vector<bool> oszlop(sakktabla_merete, false), foatlo(2 * sakktabla_merete - 1, false), mellekatlo(2 * sakktabla_merete - 1, false);

	int konfiguracio_index = 0;
	general_kiralynok(sakktabla_merete, konfiguracio_index, konfiguraciok, oszlop, foatlo, mellekatlo, temp_megoldas, megoldasok, 0, megoldasok_szama);
	return megoldasok;
}

void kiir(vector<vector<vector<string>>>& megoldasok, unsigned long long& megoldasok_szama) {
	for (int i = 0; i < megoldasok.size(); i++) {
		for (int j = 0; j < megoldasok[i].size(); j++) {
			for (int k = 0; k < megoldasok[i][j].size(); k++) {
				cout << megoldasok[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << megoldasok_szama;
}

int main() {
	int sakktabla_merete, kiirando_megoldasok_szama;
	vector<unsigned long long> konfiguraciok;
	beolvas(sakktabla_merete, kiirando_megoldasok_szama, konfiguraciok);

	unsigned long long megoldasok_szama = 0;
	int konfiguracio_index = 0;
	vector<vector<vector<string>>> megoldasok = kiralynok(sakktabla_merete, kiirando_megoldasok_szama, konfiguraciok, megoldasok_szama);

	kiir(megoldasok, megoldasok_szama);
	return 0;
}