/*Boda Norbert
511-es csoport
Lab4/04
Rendezzünk egy 𝑛 elemű tömböt leszámláló rendezéssel!
*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& hossz, vector<int>& szamok) {
	cin >> hossz;
	int temp;
	for (int i = 0; i < hossz; i++) {
		cin >> temp;
		szamok.push_back(temp);
	}
}

int maximum_keres(vector<int>& szamok) {
	int maximum = szamok[0];
	for (int i = 1; i < szamok.size(); i++) {
		if (maximum < szamok[i]) {
			maximum = szamok[i];
		}
	}
	return maximum;
}

int minimum_keres(vector<int>& szamok) {
	int minimum = szamok[0];
	for (int i = 1; i < szamok.size(); i++) {
		if (minimum > szamok[i]) {
			minimum = szamok[i];
		}
	}
	return minimum;
}

void count_sort(vector<int>& szamok) {
	int maximum = maximum_keres(szamok);
	int minimum = minimum_keres(szamok);
	vector<int> darab(maximum - minimum + 1);

	//szamok megszamolasa minel kisebb tombot lefoglalva
	for (int i = 0; i < szamok.size(); i++) {
		darab[szamok[i] - minimum]++;
	}
	for (int i = 1; i < darab.size(); i++) {
		darab[i] += darab[i - 1];
	}

	//stabil rendezes
	vector<int> temp(szamok.size());
	for (int i = szamok.size() - 1; i >= 0; i--) {
		temp[darab[szamok[i]-minimum]-1] = szamok[i];
		darab[szamok[i]-minimum]--;
	}
	szamok = temp;
}

void kiir(vector<int>& szamok) {
	for (int i = 0; i < szamok.size(); i++) {
		cout << szamok[i] << endl;
	}
}

int main() {
	int hossz;
	vector<int> szamok;
	beolvas(hossz, szamok);

	count_sort(szamok);

	kiir(szamok);
	return 0;
}