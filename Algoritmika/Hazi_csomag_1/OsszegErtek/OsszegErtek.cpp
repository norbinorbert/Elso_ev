/*Boda Norbert
511-es csoport
Lab1/05
Szamitsuk ki, adott n es x ertekekre, a kovetkezo osszeget
S = 1 - ... + (-1)^n * ((x)^2n/(2n)!)
Megkotesek:
1 <= n <= 100
x 64-bites valos szam (double) */

#include <iostream>
#include <cmath>

using namespace std;

int main() {
	short n;
	double x, tort, S=1;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		tort = 1;
		for (int j = 1; j <= 2*i; j++) {
			tort = tort * (x / j);
		}
		if (i % 2 == 0) {
			S += tort;
		}
		else {
			S -= tort;
		}
	}
	//mivel a round fuggvent egeszre kerekit, ezert a szam eloszor be van szorozva 100-al, majd kerekites utan elosztva,
	//hogy maradjon meg a 2 tizedes pontossag
	S *= 100;
	S = round(S);
	S /= 100;
	cout << S;
	return 0;
}