/*Boda Norbert
511-es csoport
Lab8/09
A virágüzlet ablakában 𝑣 váza áll, melyekbe 𝑓 csokor virágot szeretnénk
elhelyezni. A vázákat nem mozdíthatjuk el és a sorszámuk megadja, hogy
hogyan helyeszkednek el balról jobbra. A virágcsokrok sorszáma megadja, hogy
egymáshoz képést hogyan kell elhelyeznünk őket, vagyis egy 𝑖 virágcsokor mindig
egy 𝑗 virágcsokor baloldalán kell legyen, ha 𝑖 < 𝑗. Ha ismerjük, hogy egy adott
virágcsokor egy adott vázába helyezve milyen esztétikai értéket nyújt, határozzuk
meg a maximális esztétikai értéket, amelyet elérhetünk és egy olyan elhelyezést,
amely ezt lehetővé teszi!*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void beolvas(short& viragok, short& vazak, vector<vector<short>>& ertekek) {
	cin >> viragok >> vazak;
	ertekek.resize(viragok);
	for (short i = 0; i < viragok; i++) {
		ertekek[i].resize(vazak);
		for (short j = 0; j < vazak; j++) {
			cin >> ertekek[i][j];
		}
	}
}

short keres_max_ertek_index(short sor, short legnagyobb_oszlop, vector<vector<pair<short, short>>>& esztetika) {
	if (legnagyobb_oszlop < 0) {
		return -1;
	}
	short index = legnagyobb_oszlop;
	for (short i = legnagyobb_oszlop - 1; i >= 0; i--) {
		if (esztetika[sor][i].first > esztetika[sor][index].first) {
			index = i;
		}
	}
	return index;
}

vector<vector<pair<short, short>>> Viraguzlet(short viragok, short vazak, vector<vector<short>>& ertekek) {
	vector<vector<pair<short, short>>> esztetika(viragok, vector<pair<short, short>>(vazak, { SHRT_MIN, -1 }));
	for (short i = 0; i < vazak; i++) {
		esztetika[0][i].first = ertekek[0][i]; //az elso sor esztetikai ertekeinek az osszege valtozatlan marad
	}
	for (int i = 1; i < viragok; i++) {
		for (short j = i; j < vazak; j++) {
			short index = keres_max_ertek_index(i - 1, j - 1, esztetika); //megkeresi az elozo sorban a legnagyobb esztetikai ertek indexet
			esztetika[i][j].first = ertekek[i][j] + esztetika[i - 1][index].first; //a par elso fele az eddigi esztetikai ertek
			esztetika[i][j].second = index; //a par masodik fele az elozo virag indexe
		}
	}
	return esztetika;
}

short keres_max_index(vector<vector<pair<short, short>>>& esztetika) {
	short index = 0;
	for (short i = 1; i < esztetika[esztetika.size() - 1].size(); i++) {
		if (esztetika[esztetika.size() - 1][i].first > esztetika[esztetika.size() - 1][index].first) {
			index = i;
		}
	}
	return index;
}

void kiir_viragok(short index, vector<vector<pair<short, short>>>& esztetika, short sor) {
	if (sor != 0) {
		kiir_viragok(esztetika[sor][index].second, esztetika, sor - 1);
	}
	cout << index + 1 << " "; //kiirja rekurzivan az index + 1et, mert 0-tol van szamozva, illetve igy novekvo sorrendben lesz a kiiras
}

void kiir(vector<vector<pair<short, short>>>& esztetika) {
	short index = keres_max_index(esztetika); //megkeresi a legnagyobb esztetikai erteket
	cout << esztetika[esztetika.size() - 1][index].first << endl;
	kiir_viragok(index, esztetika, esztetika.size() - 1);
}

int main() {
	short viragok, vazak;
	vector<vector<short>> ertekek;
	beolvas(viragok, vazak, ertekek);

	vector<vector<pair<short, short>>> esztetika = Viraguzlet(viragok, vazak, ertekek);

	kiir(esztetika);
}