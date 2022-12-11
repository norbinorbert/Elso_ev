/*Boda Norbert
511-es csoport
Lab4/03
Rendezzünk egy 𝑛 elemű tömböt beszúró rendezéssel!
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

void rendez_beszuro(vector<long long>& szamok) {
	for (short j = 1; j < szamok.size(); j++) {
		long long seged = szamok[j];
		short i = j - 1;
		while (i >= 0 && szamok[i] > seged) {
			szamok[i + 1] = szamok[i];
			i--;
		}
		szamok[i + 1] = seged;
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

	rendez_beszuro(szamok);

	kiir(szamok);
	return 0;
}