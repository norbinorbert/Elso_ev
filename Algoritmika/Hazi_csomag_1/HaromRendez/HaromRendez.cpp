/*Boda Norbert
511-es csoport
Lab1/03
Olvassunk be a billentyuzetrol harom 64 - bites elojeles egesz szamot.Irjuk
ki oket novekvo sorrendben!*/

#include <iostream>

using namespace std;

int main() {
	long long szam1, szam2, szam3;
	cin >> szam1 >> szam2 >> szam3;
	if (szam1 < szam2) {
		if (szam1 < szam3) {
			cout << szam1 << " ";
			if (szam2 < szam3) {
				cout << szam2 << " " << szam3;
			}
			else {
				cout << szam3 << " " << szam2;
			}
		}
		else {
			    cout << szam3 << " " << szam1 << " " << szam2;
		}
	}
	else {
		if (szam2 < szam3) {
			cout << szam2 << " ";
			if (szam1 < szam3) {
				cout << szam1 << " " << szam3;
			}
			else {
				cout << szam3 << " " << szam1;
			}
		}
		else {
			cout << szam3 << " " << szam2 << " " << szam1;
		}
	}
}