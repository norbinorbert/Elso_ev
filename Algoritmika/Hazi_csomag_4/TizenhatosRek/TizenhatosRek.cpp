/*Boda Norbert
511-es csoport
Lab4/08
Írjunk rekurzív algoritmust, amely átalakít egy, a 16-os számrendszerben
megadott egész számot a 10-es számrendszerbe! Ne használjunk ismétlő struktúrát a beolvasáson kívül!*/

#include <iostream>
#include <string>

using namespace std;

void beolvas(string& hexa) {
	cin >> hexa;
}

bool helytelen(string& hexa, int index) {
	hexa[index] = toupper(hexa[index]);
	if (hexa[index] < '0' || (hexa[index] > '9' && hexa[index] < 'A') || hexa[index] >'F') {
		return true;
	}
	if (index < hexa.size()-1) {
		return helytelen(hexa, index + 1);
	}
	return false;
}

unsigned long long atalakit(string& hexa, int index) {
	hexa[index] = toupper(hexa[index]);
	if (hexa[index] >= '0' && hexa[index] <= '9') {
		if (index == 0) {
			return (hexa[index] - 48);
		}
		return atalakit(hexa, index - 1) * 16 + (hexa[index] - 48);
	}
	else {
		if (index == 0) {
			return (hexa[index] - 55);
		}
		return atalakit(hexa, index - 1) * 16 + (hexa[index] - 55);
	}
}

int main() {
	string hexa, temp;
	beolvas(hexa);
	short max_hossz = 16;
	if (hexa.size() <= max_hossz) {
		if (helytelen(hexa, 0)) {
			cout << -1;
		}
		else {
			unsigned long long megoldas = atalakit(hexa, hexa.size() - 1);
			cout << megoldas;
		}
	}
	else {
		cout << -1;
	}

	return 0;
}