/*Boda Norbert
511-es csoport
Lab7/09
Egy 𝑓 függvény gyökének azt az 𝑥 pontot nevezzük, amelyre 𝑓(𝑥) = 0. Egy
𝑓 függvény lineáris, ha 𝑓(𝑥) = 𝑎𝑥 + 𝑏 formában írható, ahol 𝑎, 𝑏 ∈ R, 𝑎 ̸= 0.
Határozzuk meg oszd meg és uralkodj módszerrel egy lineáris függvény 𝑥 gyökét
10−6 pontossággal, tudván, hogy 𝑥 ≥ 0*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double lekerdez(double index) {
	double eredmeny;
	cout << 0 << " " << fixed << setprecision(6) << index << endl;
	cin >> eredmeny;
	return eredmeny;
}

bool azonos_elojel(double szam1, double szam2) {
	return((szam1 > 0 && szam2 > 0) || (szam1 < 0 && szam2 < 0));
}

//megkeresi az y szamot amelyik eseten a [0,y] intervallum tartalmazni fogja a fuggveny gyoket
double keres_intervallum(double kezdeti_ertek, double& jelenlegi_index) {
	double uj_ertek = lekerdez(jelenlegi_index);
	if ((uj_ertek == 0) || (!azonos_elojel(kezdeti_ertek, uj_ertek))) {
		return uj_ertek;
	}

	jelenlegi_index *= 2;
	return keres_intervallum(kezdeti_ertek, jelenlegi_index);
}

//megkeresi az adott f(x) = y ellentettjet, ha letezik. Ha nem letezik akkor az x es y part beteszi a vektorba
double keres_ellentett(double x, double y, vector<pair<double, double>>& parok) {
	int i = 0;
	while (i < parok.size()) {
		if (abs(parok[i].second) == y) {
			return parok[i].first;
		}
		i++;
	}
	parok.push_back({ x, y });
	return -1;
}

void kiir_megoldas(double index) {
	cout << 1 << " " << fixed << setprecision(6) << index << endl;
}

void fuggveny_gyoke(double bal, double jobb, double bal_ertek, double jobb_ertek, vector<pair<double, double>>& parok) {
	double kozep = (bal + jobb) / 2;
	double kozep_ertek = lekerdez(kozep);
	if (kozep_ertek == 0) {
		kiir_megoldas(kozep);
		return;
	}

	double index = keres_ellentett(kozep, kozep_ertek, parok);
	if (index != -1) { 
		//ha letezik ellentett akkor a fuggveny gyoke a ket ellentett ertek kozott lesz
		//ha f(x1) = -f(x2), akkor f((x1 + x2) / 2) = 0, mert a fuggveny linearis
		kiir_megoldas((index + kozep) / 2);
		return;
	}

	if (!azonos_elojel(bal_ertek, kozep_ertek)) {
		fuggveny_gyoke(bal, kozep, bal_ertek, kozep_ertek, parok);
		return;
	}
	else {
		fuggveny_gyoke(kozep, jobb, kozep_ertek, jobb_ertek, parok);
		return;
	}
}

int main() {
	vector<pair<double, double>> parok;
	double bal_ertek = lekerdez(0), jobb = 1, jobb_ertek;
	if (bal_ertek == 0) {
		kiir_megoldas(0);
		return 0;
	}
	else {
		jobb_ertek = keres_intervallum(bal_ertek, jobb); //exponencialis kereses
		if (jobb_ertek == 0) {
			kiir_megoldas(jobb);
			return 0;
		}
	}

	//az intervallum ket szelso ertekenek lementese
	parok.push_back({ 0, bal_ertek });
	parok.push_back({ jobb, jobb_ertek });

	fuggveny_gyoke(0, jobb, bal_ertek, jobb_ertek, parok);
	return 0;
}