/*Boda Norbert
511-es csoport
Lab7/08
Egy kiállítási csarnokot le fognak fedni előre gyártott műanyaglapokkal. Előbb
felosztották a csarnok alapját négyzet alakú felületekre úgy, hogy a csarnok
belsejében található oszlop pontosan egy ilyen négyzetnyi helyet foglaljon el.
A műanyaglapok három ilyen négyzetet fednek le L-alakban. A tervező rájött,
hogy nem fogja tudni ezekkel lefedni a teljes felületet, ezért kiválasztott egy
2
𝑛 × 2
𝑛 méretű részt a csarnokból, amelyen ott van az oszlop is. Tervezzük meg
a lefedést felhasználva az alakzatot úgy, hogy ne maradjon fedetlen felület a
kiválasztott részben. Ezen alakzat elforgatható három irányba.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& ketto_hatvany, pair<short, short>& oszlop) {
	cin >> ketto_hatvany;
	cin >> oszlop.first >> oszlop.second;
}

void lement(pair<short, short> bal_fent, pair<short, short> jobb_lent, pair<short, short> oszlop, vector<vector<pair<short, short>>>& megoldas, int& megoldas_szama) {
	megoldas.push_back(vector<pair<short, short>>());
	vector<pair<short, short>> parok = { bal_fent , {bal_fent.first, jobb_lent.second}, {jobb_lent.first, bal_fent.second}, jobb_lent };
	for (short i = 0; i < parok.size(); i++) {
		if (parok[i] != oszlop) {
			megoldas[megoldas_szama].push_back(parok[i]);
		}
	}
}

void lement_sarkok(pair<short, short> a, pair<short, short> b, pair<short, short> c, pair<short, short> d, pair<short, short> ures,
	vector<vector<pair<short, short>>>& megoldas, int& megoldas_szama) {
	megoldas.push_back(vector<pair<short, short>>());
	vector<pair<short, short>> parok = { a, b, c, d };
	for (short i = 0; i < parok.size(); i++) {
		if (parok[i] != ures) {
			megoldas[megoldas_szama].push_back(parok[i]);
		}
	}
}

void csarnok_divide(pair<short, short> bal_fent, pair<short, short> jobb_lent, pair<short, short> oszlop, vector<vector<pair<short, short>>>& megoldas, int& megoldas_szama) {
	if (jobb_lent.first - bal_fent.first == 1) {
		lement(bal_fent, jobb_lent, oszlop, megoldas, megoldas_szama);
		megoldas_szama++;
		return;
	}
	pair<short, short> temp_oszlop1(0, 0), temp_oszlop2(0, 0), temp_oszlop3(0, 0), temp_oszlop4(0, 0), ures(0,0);

	temp_oszlop1 = { (bal_fent.first + jobb_lent.first) / 2, (bal_fent.second + jobb_lent.second) / 2 };
	if (!(temp_oszlop1.first < oszlop.first || temp_oszlop1.second < oszlop.second)) {
		temp_oszlop1 = ures;
	}
	temp_oszlop2 = { (bal_fent.first + jobb_lent.first) / 2, (bal_fent.second + jobb_lent.second) / 2 + 1 };
	if (!(temp_oszlop2.first < oszlop.first || temp_oszlop2.second > oszlop.second)) {
		temp_oszlop2 = ures;
	}
	temp_oszlop3 = { (bal_fent.first + jobb_lent.first) / 2 + 1, (bal_fent.second + jobb_lent.second) / 2 };
	if (!(temp_oszlop3.first > oszlop.first || temp_oszlop3.second < oszlop.second)) {
		temp_oszlop3 = ures;
	}
	temp_oszlop4 = { (bal_fent.first + jobb_lent.first) / 2 + 1, (bal_fent.second + jobb_lent.second) / 2 + 1 };
	if (!(temp_oszlop4.first > oszlop.first || temp_oszlop4.second > oszlop.second)) {
		temp_oszlop4 = ures;
	}
	lement_sarkok(temp_oszlop1, temp_oszlop2, temp_oszlop3, temp_oszlop4, { 0,0 }, megoldas, megoldas_szama);
	megoldas_szama++;

	//bal felso negyzet
	if (temp_oszlop1 != ures) {
		csarnok_divide(bal_fent, { (bal_fent.first + jobb_lent.first) / 2, (bal_fent.second + jobb_lent.second) / 2 }, temp_oszlop1, megoldas, megoldas_szama);
	}
	else {
		csarnok_divide(bal_fent, { (bal_fent.first + jobb_lent.first) / 2, (bal_fent.second + jobb_lent.second) / 2 }, oszlop, megoldas, megoldas_szama);
	}

	//jobb felso negyzet
	if (temp_oszlop2 != ures) {
		csarnok_divide({ bal_fent.first, (bal_fent.second + jobb_lent.second) / 2 + 1 }, { (bal_fent.first + jobb_lent.first) / 2, jobb_lent.second }, temp_oszlop2, megoldas, megoldas_szama);
	}
	else {
		csarnok_divide({ bal_fent.first, (bal_fent.second + jobb_lent.second) / 2 + 1 }, { (bal_fent.first + jobb_lent.first) / 2, jobb_lent.second }, oszlop, megoldas, megoldas_szama);
	}

	//bal also negyzet
	if (temp_oszlop3 != ures) {
		csarnok_divide({ (bal_fent.first + jobb_lent.first) / 2 + 1, bal_fent.second }, { jobb_lent.first, (bal_fent.second + jobb_lent.second) / 2 }, temp_oszlop3, megoldas, megoldas_szama);
	}
	else {
		csarnok_divide({ (bal_fent.first + jobb_lent.first) / 2 + 1, bal_fent.second }, { jobb_lent.first, (bal_fent.second + jobb_lent.second) / 2 }, oszlop, megoldas, megoldas_szama);
	}

	//jobb also negyzet
	if (temp_oszlop4 != ures) {
		csarnok_divide({ (bal_fent.first + jobb_lent.first) / 2 + 1, (bal_fent.second + jobb_lent.second) / 2 + 1 }, jobb_lent, temp_oszlop4, megoldas, megoldas_szama);
	}
	else {
		csarnok_divide({ (bal_fent.first + jobb_lent.first) / 2 + 1, (bal_fent.second + jobb_lent.second) / 2 + 1 }, jobb_lent, oszlop, megoldas, megoldas_szama);
	}
}

vector<vector<pair<short, short>>> Csarnok(short& csarnok_hossza, pair<short, short>& oszlop) {
	vector<vector<pair<short, short>>> megoldas;
	int megoldas_szama = 0;
	csarnok_divide({ 1, 1 }, { csarnok_hossza, csarnok_hossza }, oszlop, megoldas, megoldas_szama);
	return megoldas;
}

void count_sort(short csarnok_hossza, vector<vector<pair<short, short>>>& megoldas) {
	vector<int> darab(csarnok_hossza + 1);

	for (int i = 0; i < megoldas.size(); i++) {
		darab[megoldas[i][0].first]++;
	}
	for (int i = 1; i < darab.size(); i++) {
		darab[i] += darab[i - 1];
	}

	//stabil rendezes
	vector<vector<pair<short, short>>> temp(megoldas.size());
	for (int i = megoldas.size() - 1; i >= 0; i--) {
		temp[darab[megoldas[i][0].first] - 1] = megoldas[i];
		darab[megoldas[i][0].first]--;
	}
	megoldas = temp;
}

void kiir(short csarnok_hossza, vector<vector<pair<short, short>>>& megoldas) {
	count_sort(csarnok_hossza, megoldas); //megoldasok rendezese, hogy meglegyen a lexikografikus sorrend
	for (int i = 0; i < megoldas.size(); i++) {
		for (int j = 0; j < megoldas[i].size(); j++) {
			cout << megoldas[i][j].first << " " << megoldas[i][j].second << " ";
		}
		cout << endl;
	}
}

int main() {
	short ketto_hatvany;
	pair<short, short> oszlop;
	beolvas(ketto_hatvany, oszlop);

	short csarnok_hossza = 1;
	for (short i = 0; i < ketto_hatvany; i++) {
		csarnok_hossza *= 2;
	}

	vector<vector<pair<short, short>>> megoldas = Csarnok(csarnok_hossza, oszlop);

	kiir(csarnok_hossza, megoldas);
	return 0;
}