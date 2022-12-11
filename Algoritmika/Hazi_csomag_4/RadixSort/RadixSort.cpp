/*Boda Norbert
511-es csoport
Lab4/05
Rendezzünk egy 𝑛 elemű tömböt számjegyes rendezéssel! A bemenet első
sora tartalmazza az 𝑛 értéket, a többi 𝑛 sor a sorozat elemeit.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void beolvas(int& hossz, vector<unsigned long long>& szamok) {
	cin >> hossz;
	unsigned long long temp;
	for (int i = 0; i < hossz; i++) {
		cin >> temp;
		szamok.push_back(temp);
	}
}

//megnezi hany szamjegyu a legnagyobb szam, ennyiszer kell majd meghivni a count sortot
int max_szamjegy(vector<unsigned long long>& szamok) {
	unsigned long long maximum = szamok[0];
	for (int i = 1; i < szamok.size(); i++) {
		if (maximum < szamok[i]) {
			maximum = szamok[i];
		}
	}
	string szj = to_string(maximum);
	return szj.size();
}

//kiszamolja, hogy mennyivel kell osztani ahhoz, hogy a megfelelo szamjegyet lehessen elerni
unsigned long long oszto_kiszamolas(int szamjegy_pozicio) {
	unsigned long long oszto = 1;
	for (int i = 0; i < szamjegy_pozicio; i++) {
		oszto *= 10;
	}
	return oszto;
}

void count_sort(vector<unsigned long long>& szamok, int& szamjegy_pozicio) {
	unsigned long long oszto = oszto_kiszamolas(szamjegy_pozicio);
	vector<int> darab(10);
	for (int i = 0; i < szamok.size(); i++) {
		darab[(szamok[i] / oszto) % 10]++;
	}
	for (int i = 1; i < darab.size(); i++) {
		darab[i] += darab[i - 1];
	}

	//kotelezoen stabil rendezest kell vegezni
	vector<unsigned long long> temp(szamok.size());
	for (int i = szamok.size() - 1; i >= 0; i--) {
		temp[darab[(szamok[i] / oszto) % 10] - 1] = szamok[i];
		darab[(szamok[i] / oszto) % 10]--;
	}
	szamok = temp;
}

void radix(vector<unsigned long long>& szamok, int szj) {
	//minden szamjegyre meghivja a count sortot
	for (int i = 0; i < szj; i++) {
		count_sort(szamok, i);
	}
}

void kiir(vector<unsigned long long>& szamok) {
	for (int i = 0; i < szamok.size(); i++) {
		cout << szamok[i] << endl;
	}
}

int main() {
	int hossz;
	vector<unsigned long long> szamok;
	beolvas(hossz, szamok);

	int szj = max_szamjegy(szamok);
	radix(szamok, szj);

	kiir(szamok);
	return 0;
}