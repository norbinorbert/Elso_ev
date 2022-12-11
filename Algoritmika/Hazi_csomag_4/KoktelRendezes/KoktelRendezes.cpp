/*Boda Norbert
511-es csoport
Lab4/01
Rendezzünk egy 𝑛 elemű tömböt koktélrendezéssel!
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

void rendez_koktel(vector<long long>& szamok) {
	short temp_pozicio = szamok.size();
	bool rendezett = true;
	do{
		short utolso_pozicio = temp_pozicio - 1;
		rendezett = true;
		for (short i = 0; i < utolso_pozicio; i++) {
			if (szamok[i] > szamok[i + 1]) {
				swap(szamok[i], szamok[i + 1]);
				rendezett = false;
				temp_pozicio = i+1;
			}
		}
	}while (!rendezett);
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

	rendez_koktel(szamok);

	kiir(szamok);
	return 0;
}