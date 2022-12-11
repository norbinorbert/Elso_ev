/*Boda Norbert
511-es
Lab2/04
Adott egy csoport év végi vizsgajegyeinek listája. Töröljük ki az 5-ösnél
kisebb jegyeket a listából. A módósítást a beolvasott tömbben kell elvégezni,
nem elég csak kiíratni az eredményt.*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& jegyek_szama, vector<double>& jegyek) {
	cin >> jegyek_szama;
	double temp_jegy;
	for (int i = 0; i < jegyek_szama; i++) {
		cin >> temp_jegy;
		jegyek.push_back(temp_jegy);
	}
	return;
}

//kivalogatas helyben programozasi tetel
void torol(vector<double>& jegyek){
	int i = 0;
	while (i < jegyek.size()) {
		if (jegyek[i] < 5) {
			jegyek[i] = jegyek[jegyek.size() - 1];
			jegyek.pop_back();
		}
		else {
			i++;
		}
	}
	return;
}

void kiir(vector<double>& jegyek) {
	for (int i = 0; i < jegyek.size(); i++) {
		cout << jegyek[i] << " ";
	}
	return;
}

int main() {
	int	jegyek_szama;
	vector<double> jegyek;

	beolvas(jegyek_szama, jegyek);	

	torol(jegyek);

	kiir(jegyek);

	return 0;
}