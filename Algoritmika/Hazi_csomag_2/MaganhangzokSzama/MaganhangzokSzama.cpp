/*Boda Norbert
511-es csoport
Lab2/03
Számoljuk meg egy adott szövegben a magánhangzók számát!*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool maganhangzo_e(char betu) {
	vector <char> maganhangzok = { 'a', 'e', 'i', 'o', 'u' };

	for (unsigned char i = 0; i < maganhangzok.size(); i++) {
		if (tolower(betu) == maganhangzok[i]) {
			return true;
		}
	}

	return false;
}

//szekvencialis kereses programozasi tetel
short maganhangzok_szama(string szoveg) {
	short szamlalo = 0;
	
	for (short i = 0; i < szoveg.size(); i++) {
		if (maganhangzo_e(szoveg[i])) {
			szamlalo++;
		}
	}
	
	return szamlalo;
}

int main() {
	string szoveg;
	getline(cin, szoveg);

	cout << maganhangzok_szama(szoveg);
	return 0;
}