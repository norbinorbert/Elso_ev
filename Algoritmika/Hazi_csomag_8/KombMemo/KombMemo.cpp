/*Boda Norbert
511-es csoport
Lab8/02
Számoljátok ki 𝑛 elem 𝑘-ad rendű kombinációinak számát feljegyzéses módszerrel!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& elemek_szama, short& kombinacio_rendje) {
	cin >> elemek_szama >> kombinacio_rendje;
}

void init_memo(vector<vector<long long>>& kombinaciok) {
	for (short i = 1; i < kombinaciok.size(); i++) {
		kombinaciok[i].resize(i + 1);
		for (short j = 0; j < kombinaciok[i].size(); j++) {
			kombinaciok[i][j] = -1;
		}
	}
	kombinaciok[1][0] = 1;
	kombinaciok[1][1] = 1;
}

long long kombinaciok_memo(short elemek_szama, short kombinacio_rendje, vector<vector<long long>>& kombinaciok) {
	if (kombinaciok[elemek_szama][kombinacio_rendje] != -1) {
		return kombinaciok[elemek_szama][kombinacio_rendje];
	}
	else {
		if (kombinacio_rendje == 0) {
			kombinaciok[elemek_szama][kombinacio_rendje] = kombinaciok_memo(elemek_szama - 1, kombinacio_rendje, kombinaciok);
		}
		else if (kombinacio_rendje == elemek_szama) {
			kombinaciok[elemek_szama][kombinacio_rendje] = kombinaciok_memo(elemek_szama - 1, kombinacio_rendje - 1, kombinaciok);
		}
		else {
			kombinaciok[elemek_szama][kombinacio_rendje] = kombinaciok_memo(elemek_szama - 1, kombinacio_rendje, kombinaciok) +
				kombinaciok_memo(elemek_szama - 1, kombinacio_rendje - 1, kombinaciok);
		}
		return kombinaciok[elemek_szama][kombinacio_rendje];
	}
}

int main() {
	short elemek_szama, kombinacio_rendje;
	beolvas(elemek_szama, kombinacio_rendje);
	vector<vector<long long>> kombinaciok(elemek_szama + 1, vector<long long>());

	init_memo(kombinaciok);

	cout << kombinaciok_memo(elemek_szama, kombinacio_rendje, kombinaciok);
	return 0;
}