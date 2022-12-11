/*Boda Norbert
511-es csoport
Lab1/10
Irjunk ki, egy 60-as szamrendszerben megadott szamot a 10-es szamrendszerben!
A 60-as szamrendszer szamjegyei 0, 1, ..., 9, (10), (11), ..., (59).
Peldaul az 5(15)(55)0(20)4 szam lehet egy 60-as szamrendszerben megadott szam.
Ha az eredmeny nem fer 64-bites elojel nelkuli egeszbe, irjunk ki -1-et!
*/

#include <iostream>
#include <string>
#include <climits>

using namespace std;

int main() {
	string szam_60, szamjegy = "";
	unsigned long long prev_szam = 0, szam_10 = 0;
	short hatvany = 0;
	cin >> szam_60;
	for (int i = szam_60.length() - 1; i >= 0; i--) {
		//megnezi ha a szamjegy 2 vagy 1 szamjegyu, majd ezzel dolgozik
		if (szam_60[i] == ')') {
			i--;
			while (szam_60[i] != '(') {
				szamjegy = szam_60[i] + szamjegy;
				i--;
			}
		}
		else {
			szamjegy = szam_60[i];
		}
		short temp_szamjegy = stoi(szamjegy);
		szamjegy = "";
		//a 31 * (60^10) illetve barmi ami ennel nagyobb kiesik az unsigned long long-bol
		if (hatvany > 10 || (hatvany == 10 && temp_szamjegy >= 31)) {
			cout << -1;
			return 0;
		}
		unsigned long long hatvan_hatvany = 1;
		for (int j = 1; j <= hatvany; j++) {
			hatvan_hatvany *= 60;
		}
		hatvany++;
		prev_szam = szam_10;
		szam_10 += hatvan_hatvany * temp_szamjegy;
		//ha a szam_10 atlep az unsigned long long max erteken akkor 0-tol fog ujra kezdodni,
		//ezert a prev_szam nagyobb lesz nala
		if (prev_szam > szam_10) {
			cout << -1;
			return 0;
		}
	}
	cout << szam_10;
	return 0;
}