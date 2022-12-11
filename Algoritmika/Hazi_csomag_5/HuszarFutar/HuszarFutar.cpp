/*Boda Norbert
511-es csoport
Lab5/06
Egy 𝑛 × 𝑛 méretű sakktáblán az (𝑥, 𝑦) pozíción található egy futár és az
(𝑥0, 𝑦0) pozíción egy ló. A lónak el kell jutnia erről a helyről az (𝑥1, 𝑦1) pozícióra,
anélkül, hogy egy bizonyos négyzetre többször lépne illetve, hogy olyan helyen
állna meg, ahonnan a futár kiütheti. Írjuk ki, hogy hányféleképpen lehetséges ez!*/

#include <iostream>
#include <vector>

using namespace std;

const short lehetseges_lepesek = 8; //mindig 8 lehetseges lepes kozul tud a lo valasztani

struct koordinatak {
	short x, y;
}futar, lo, cel;

void beolvas(short& tabla_merete) {
	cin >> tabla_merete >> futar.x >> futar.y >> lo.x >> lo.y >> cel.x >> cel.y;
}

bool lehet_lepni(short& tabla_merete, koordinatak lepesek, vector<vector<bool>>& lehetseges, vector<vector<bool>>& volt) {
	if (lo.x + lepesek.x >= 0 && lo.x + lepesek.x < tabla_merete && lo.y + lepesek.y >= 0 && lo.y + lepesek.y < tabla_merete) {
		if (lehetseges[lo.x + lepesek.x][lo.y + lepesek.y] && !volt[lo.x + lepesek.x][lo.y + lepesek.y]) {
			return true;
		}
	}
	return false;
}

void general_lepesek(short& tabla_merete, vector<vector<bool>>& lehetseges, vector<vector<bool>>& volt, koordinatak lepesek[], unsigned long long& megoldasok_szama) {
	if (lo.x == cel.x && lo.y == cel.y) {
		megoldasok_szama++;
		return;
	}
	for (short i = 0; i < lehetseges_lepesek; i++) {
		if (lehet_lepni(tabla_merete, lepesek[i], lehetseges, volt)) {
			lo.x += lepesek[i].x;
			lo.y += lepesek[i].y;
			volt[lo.x][lo.y] = true;
			general_lepesek(tabla_merete, lehetseges, volt, lepesek, megoldasok_szama);
			volt[lo.x][lo.y] = false;
			lo.x -= lepesek[i].x;
			lo.y -= lepesek[i].y;
		}
	}
}

unsigned long long HuszarFutar(short& tabla_merete) {
	//mivel 0-tol vannak a vectorok szamozva, ezert minden koordinatabol ki lesz vonva 1
	futar.x -= 1, futar.y -= 1, lo.x -= 1, lo.y -= 1, cel.x -= 1, cel.y -= 1;
	//logikai tombok amik ellenorizik, ha jart mar ott a lo vagy sem, illetve ha lehetseges oda lepni
	vector<vector<bool>> lehetseges(tabla_merete, vector<bool>(tabla_merete, true)), volt(tabla_merete, vector<bool>(tabla_merete, false));
	volt[lo.x][lo.y] = true;
	for (short i = 0; i < tabla_merete; i++) {
		for (short j = 0; j < tabla_merete; j++) {
			if (i + j == futar.x + futar.y || i-j == futar.x-futar.y) {
				lehetseges[i][j] = false;
			}
		}
	}

	koordinatak lepesek[lehetseges_lepesek] = { 1, 2, -1, 2, 2, 1, 2, -1, 1, -2, -1, -2, -2, -1, -2, 1};
	unsigned long long megoldasok_szama = 0;
	general_lepesek(tabla_merete, lehetseges, volt, lepesek, megoldasok_szama);
	return megoldasok_szama;
}

void kiir(unsigned long long& megoldasok_szama) {
	cout << megoldasok_szama;
}

int main() {
	short tabla_merete; 
	beolvas(tabla_merete);

	unsigned long long megoldasok_szama = HuszarFutar(tabla_merete);

	kiir(megoldasok_szama);

	return 0;
}