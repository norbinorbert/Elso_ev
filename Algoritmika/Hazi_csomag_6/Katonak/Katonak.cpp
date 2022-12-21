/*Boda Norbert
511-es csoport
Lab6/02
A háború során 𝑚 különböző helyen kell őrt állni, mindegyik helyről tudjuk,
hogy melyik nap kezdetétől melyik nap végéig kell ott szolgálatot teljesítsen egy
katona. Állapítsuk meg, hogy elegendő-e 𝑛 darab katona ahhoz, hogy őrt álljunk
mind az 𝑚 helyen!*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(int& katonak_szama, short& helyek_szama, vector<pair<short, short>>& napok) {
	cin >> katonak_szama >> helyek_szama;
	napok.resize(helyek_szama);
	for (short i = 0; i < helyek_szama; i++) {
		cin >> napok[i].first >> napok[i].second;
	}
}

bool katonak(int& katonak_szama, short& helyek_szama, vector<pair<short, short>>& napok) {
	//ha nincs katona, de van hely ahol ort kell allni akkor hamisat terit vissza
	if (katonak_szama == 0 && helyek_szama != 0) {
		return false;
	}
	//ha nincs hely ahol ort kell allni, vagy tobb katona van, mint hely, akkor igazat terit vissza
	if (helyek_szama == 0 || katonak_szama > helyek_szama) {
		return true;
	}
	//rendezi a tombot a vegzodesi nap szerint
	sort(napok.begin(), napok.end());
	vector<pair<short, short>> katonak(katonak_szama);
	for (short i = 0; i < helyek_szama; i++) {
		int j = 0;
		//megnezi ha a j-edik katona orizheti az i-edik helyet 
		while (j < katonak_szama && katonak[j].second >= napok[i].first) {
			j++;
		}
		//ha vegigment az osszes katonan es egyik sem tudja orizni a helyet akkor hamisat terit vissza
		if (j == katonak_szama) {
			return false;
		}
		//a j-edik katona elkezdi orizni az i-edik helyet
		katonak[j] = napok[i];
	}
	return true;
}

void kiir(bool& lehetseges) {
	if (lehetseges) {
		cout << "igen";
	}
	else {
		cout << "nem";
	}
}

int main() {
	int katonak_szama;
	short helyek_szama;
	vector<pair<short, short>> napok;
	beolvas(katonak_szama, helyek_szama, napok);

	bool lehetseges = katonak(katonak_szama, helyek_szama, napok);

	kiir(lehetseges);
	return 0;
}