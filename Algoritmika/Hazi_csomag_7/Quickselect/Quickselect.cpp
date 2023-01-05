/*Boda Norbert
511-es csoport
Lab7/02
Adott egy 𝑛 elemű tömb, mely 64 bites valós számokat tartalmaz és egy 𝑘
természetes szám. Határozzuk meg a tömb 𝑘. legkisebb elemét, anélkül, hogy
rendeznénk azt, vagy használnánk az nth_element függvényt!*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& vector_hossza, int& elem_szama, vector<double>& szamok) {
	cin >> vector_hossza >> elem_szama;
	szamok.resize(vector_hossza);
	for (int i = 0; i < vector_hossza; i++) {
		cin >> szamok[i];
	}
}

int feloszt(vector<double>& szamok, int bal, int jobb) {
	double strazsa = szamok[jobb];
	int i = bal - 1;
	for (int j = bal; j <= jobb - 1; j++) {
		if (szamok[j] <= strazsa) {
			i++;
			swap(szamok[i], szamok[j]);
		}
	}
	swap(szamok[i + 1], szamok[jobb]);
	return i;
}

void quicksort(int& elem_szama, vector<double>& szamok, int bal, int jobb) {
	if (bal < jobb) {
		int m = feloszt(szamok, bal, jobb);
		if (m < elem_szama - 1) {
			quicksort(elem_szama, szamok, m + 1, jobb);
		}
		else {
			quicksort(elem_szama, szamok, bal, m);
		}
	}
}

void kiir(int& megoldas_index, vector<double>& szamok) {
	cout << szamok[megoldas_index - 1];
}

int main() {
	int vector_hossza, elem_szama;
	vector<double> szamok;
	beolvas(vector_hossza, elem_szama, szamok);

	quicksort(elem_szama, szamok, 0, szamok.size() - 1);

	kiir(elem_szama, szamok);
	return 0;
}