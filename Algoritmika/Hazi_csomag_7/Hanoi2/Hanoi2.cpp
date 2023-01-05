/*Boda Norbert
511-es csoport
Lab7/06
Adott a Hanoi-tornyok feladata, ahol az 1-es rúdról kell a 3-as rúdra átpakoljunk 𝑛 korongot, a 2-es rúd segítségével. Oldjuk meg a feladatot abban az
esetben, ha a 2-es és 3-as rudak között nem szabad korongot mozgatni, vagyis
minden mozgatásban szerepelnie kell az 1-es rúdnak.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& korongok_szama) {
	cin >> korongok_szama;
}

//mas elnevezes: A = honnnan, C = hova, B = seged
void general_Hanoi(short korongok_szama, short honnan, short hova, short seged, vector<pair<short, short>>& megoldas) {
	if (seged == 1) {
		general_Hanoi(korongok_szama, honnan, seged, hova, megoldas);
		general_Hanoi(korongok_szama, seged, hova, honnan, megoldas);
	}
	else {
		if (korongok_szama == 1) {
			megoldas.push_back({ honnan, hova });
		}
		else {
			general_Hanoi(korongok_szama - 1, honnan, seged, hova, megoldas);
			general_Hanoi(1, honnan, hova, seged, megoldas);
			general_Hanoi(korongok_szama - 1, seged, hova, honnan, megoldas);
		}
	}
}

vector<pair<short, short>> Hanoi(short korongok_szama) {
	vector<pair<short, short>> megoldas;
	if (korongok_szama == 0) {
		return megoldas;
	}
	general_Hanoi(korongok_szama, 1, 3, 2, megoldas);
	return megoldas;
}

void kiir(vector<pair<short, short>>& megoldas) {
	for (int i = 0; i < megoldas.size(); i++) {
		cout << megoldas[i].first << " " << megoldas[i].second << endl;
	}
}

int main() {
	short korongok_szama;
	beolvas(korongok_szama);

	vector<pair<short, short>> megoldas = Hanoi(korongok_szama);

	kiir(megoldas);
	return 0;
}