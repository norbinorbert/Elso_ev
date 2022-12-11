/*Boda Norbert
511-es csoport
Lab4/02
Rendezzünk egy 𝑛 elemű tömböt minimumkiválasztásra épülő rendezéssel!
*/

#include <iostream>
#include <vector>

using namespace std;

void beolvas(short& hossz, vector<long long>& szamok) {
	cin >> hossz;
	long long temp;
	for (short i = 0; i < hossz; i++) {
		cin >> temp;
		szamok.push_back(temp);
	}
}

void rendez_min(vector<long long>& szamok) {
	for (short i = 0; i < szamok.size()-1; i++) {
		short min_index = i;
		for (short j = i + 1; j < szamok.size(); j++) {
			if (szamok[min_index] > szamok[j]) {
				min_index = j;
			}
		}
		swap(szamok[i], szamok[min_index]);
	}
}

void kiir(vector<long long>& szamok) {
	for (short i = 0; i < szamok.size(); i++) {
		cout << szamok[i] << endl;
	}
}

int main() {
	short hossz;
	vector<long long> szamok;
	beolvas(hossz, szamok);

	rendez_min(szamok);

	kiir(szamok);
	return 0;
}