/*Boda Norbert
511-es csoport
Lab3/05
Adott egy római szám, írjuk ki arab számjegyekkel!*/

#include<iostream>
#include<string>

using namespace std;

void beolvas(string& romai_szam) {
	cin >> romai_szam;
	return;
}

int atalakit(string romai_szam) {
	string masolat = romai_szam;
	int ujszam = 0;
	short i = 0;

	//M=1000 lekezelese
	while (romai_szam[i] == 'M' && i <= romai_szam.size() - 1) {
		ujszam += 1000;
		i++;
	}
	//CM=900 lekezelese
	if (romai_szam[i] == 'C' && romai_szam[i + 1] == 'M' && i < romai_szam.size() - 1) {
		ujszam += 900;
		i += 2;
	}
	//D=500 lekezelese
	if (romai_szam[i] == 'D' && i <= romai_szam.size() - 1) {
		ujszam += 500;
		i++;
	}
	//CD=400 lekezelese
	if (romai_szam[i] == 'C' && romai_szam[i + 1] == 'D' && i < romai_szam.size() - 1) {
		ujszam += 400;
		i += 2;
	}
	//C=100 lekezelese
	while (romai_szam[i] == 'C' && i <= romai_szam.size() - 1) {
		ujszam += 100;
		i++;
	}
	//XC=90 lekezelese
	if (romai_szam[i] == 'X' && romai_szam[i + 1] == 'C' && i < romai_szam.size() - 1) {
		ujszam += 90;
		i += 2;
	}
	//L=50 lekezelese
	if (romai_szam[i] == 'L' && i <= romai_szam.size() - 1) {
		ujszam += 50;
		i++;
	}
	//XL=40 lekezelese
	if (romai_szam[i] == 'X' && romai_szam[i + 1] == 'L' && i < romai_szam.size() - 1) {
		ujszam += 40;
		i += 2;
	}
	//X=10 lekezelese
	while (romai_szam[i] == 'X' && i <= romai_szam.size() - 1) {
		ujszam += 10;
		i++;
	}
	//IX=9 lekezelese
	if (romai_szam[i] == 'I' && romai_szam[i + 1] == 'X' && i < romai_szam.size() - 1) {
		ujszam += 9;
		i += 2;
	}
	//V=5 lekezelese
	if (romai_szam[i] == 'V' && i <= romai_szam.size() - 1) {
		ujszam += 5;
		i++;
	}
	//IV=4 lekezelese
	if (romai_szam[i] == 'I' && romai_szam[i + 1] == 'V' && i < romai_szam.size() - 1) {
		ujszam += 4;
		i += 2;
	}
	//I=1 lekezelese
	while (romai_szam[i] == 'I' && i <= romai_szam.size() - 1) {
		ujszam += 1;
		i++;
	}

	return ujszam;
}

void kiir(int arab_szam) {
	cout << "A megadott szam arab szamjegyekkel: " << arab_szam;
	return;
}

int main() {
	string romai_szam;
	beolvas(romai_szam);

	int arab_szam = atalakit(romai_szam);
	
	kiir(arab_szam);

	return 0;
}