/*Boda Norbert
511-es csoport	
Lab5/04
Legyen 𝑛 építőkocka, amelyek 1-től 𝑛-ig vannak címkézve. Beolvassuk az
oldalaik hosszát és a színüket. Írjunk ki minden 𝑘 kockából álló tornyot, amelyeket
úgy építhetünk fel, hogy nem teszünk egymásra azonos színű kockát és oldalaik
mérete (lentről felfele) szigorúan csökkenő sorozatot alkotnak.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(short& kockak_szama, short& torony_magassaga, vector<string>& szinek, vector<unsigned int>& hosszak) {
	cin >> kockak_szama >> torony_magassaga;
	szinek.resize(kockak_szama);
	hosszak.resize(kockak_szama);
	for (int i = 0; i < kockak_szama; i++) {
		cin >> szinek[i] >> hosszak[i];
	}
}

void general_torony(short& kockak_szama, short& torony_magassaga, vector<string>& szinek, vector<unsigned int>& hosszak,
	short szamlalo, vector<unsigned int>& temp_megoldas, vector<vector<unsigned int>>& megoldas, string prev_szin, vector<bool>& volt) {

	if (szamlalo == torony_magassaga) {
		megoldas.push_back(temp_megoldas);
		return;
	}

	for (int i = 0; i < kockak_szama; i++) {

		//ha nincs kocka a toronyban akkor leteszi az elsot
		if (szamlalo == 0) {
			temp_megoldas[szamlalo] = i + 1;
			volt[i] = true;
			general_torony(kockak_szama, torony_magassaga, szinek, hosszak, szamlalo + 1, temp_megoldas, megoldas, szinek[i], volt);
			volt[i] = false;
		}
		
		//ha mar van kocka a toronyban akkor megnezi, hogy melyik a kovetkezo kocka amelyet ra tud tenni
		else {
			if (!volt[i]) {
				if (hosszak[i] < hosszak[temp_megoldas[szamlalo - 1] - 1] && szinek[i] != prev_szin) {
					temp_megoldas[szamlalo] = i + 1;
					volt[i] = true;
					general_torony(kockak_szama, torony_magassaga, szinek, hosszak, szamlalo + 1, temp_megoldas, megoldas, szinek[i], volt);
					volt[i] = false;
				}
			}
		}
	}
}

vector<vector<unsigned int>> torony(short& kockak_szama, short& torony_magassaga, vector<string>& szinek, vector<unsigned int>& hosszak) {
	vector<unsigned int> temp_megoldas(torony_magassaga);
	vector<vector<unsigned int>> megoldas;
	vector<bool> volt(kockak_szama, false);

	general_torony(kockak_szama, torony_magassaga, szinek, hosszak, 0, temp_megoldas, megoldas, "", volt);
	return megoldas;
}

void kiir(vector<vector<unsigned int>>& megoldas) {
	//ha nincs megoldas kiir -1-et
	if (megoldas.size() == 0) {
		cout << -1;
		return;
	}
	for (int i = 0; i < megoldas.size(); i++) {
		for (int j = 0; j < megoldas[i].size(); j++) {
			cout << megoldas[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	short kockak_szama, torony_magassaga;
	vector<string> szinek;
	vector<unsigned int> hosszak;
	beolvas(kockak_szama, torony_magassaga, szinek, hosszak);

	vector<vector<unsigned int>> megoldas = torony(kockak_szama, torony_magassaga, szinek, hosszak);

	kiir(megoldas);
	return 0;
}