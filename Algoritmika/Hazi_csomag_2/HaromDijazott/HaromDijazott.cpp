/*Boda Norbert
511-es csoport
Lab2/01
Ismerjük egy osztály tanulóinak neveit (családnév + keresztnév) és év végi
átlagait. Állapítsuk meg, hogy egy adott nevu tanuló az elso három díjazott között van-e?*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void beolvas(short& diakok_szama, vector <string>& csaladnevek, vector <string>& keresztnevek,
	vector <double>& mediak, string& keresett_csaladnev, string& keresett_keresztnev) {

	string temp_s;
	double temp_x;
	cin >> diakok_szama;
	
	for (short i = 0; i < diakok_szama; i++) {
		cin >> temp_s;
		csaladnevek.push_back(temp_s);
		cin >> temp_s;
		keresztnevek.push_back(temp_s);
		cin >> temp_x;
		mediak.push_back(temp_x);
	}
	cin >> keresett_csaladnev >> keresett_keresztnev;
	
	return;
}

//maximumkivalasztas programozasi tetel
//kikeresi a 3 legnagyobb media indexet
void maximum_kereses(short& max1_index, short& max2_index, short& max3_index, vector<double>& mediak) {
	for (short i = 1; i < mediak.size(); i++) {
		if (mediak[i] > mediak[max1_index]) {
			max3_index = max2_index;
			max2_index = max1_index;
			max1_index = i;
		}
		else if (mediak[i] > mediak[max2_index]) {
			max3_index = max2_index;
			max2_index = i;
		}
		else if (mediak[i] > mediak[max3_index]) {
			max3_index = i;
		}
	}
	
	return;
}

//kivalasztas programozasi tetel
//visszateriti a keresett diak mediajat es -1-et ha nem szerepel az a diak a listaban
double media_kereses(vector <string>& csaladnevek, vector <string>& keresztnevek, vector <double>& mediak,
	string& keresett_csaladnev, string& keresett_keresztnev) {
	short hely = -1, i = 0;
	while (hely == -1 && i < csaladnevek.size()) {
		if (keresett_csaladnev == csaladnevek[i] && keresett_keresztnev == keresztnevek[i]) {
			hely = i;
		}
		else {
			i++;
		}
	}
	if (hely == -1) {
		return hely;
	}
	else {
		return mediak[hely];
	}
}

//igazat terit vissza ha egyezik a keresett diak mediaja a 3 legnagyobb media egyikevel
bool elso_harom(short index1, short index2, short index3, vector<double>& mediak, double media) {
	return (media == mediak[index1] || media == mediak[index2] || media == mediak[index3]);
}

int main() {
	short diakok_szama;
	vector <string> csaladnevek, keresztnevek;
	vector <double> mediak;
	string keresett_csaladnev, keresett_keresztnev;

	beolvas(diakok_szama, csaladnevek, keresztnevek, mediak, keresett_csaladnev, keresett_keresztnev);

	short max1_index = 0, max2_index = 0, max3_index = 0;
	maximum_kereses(max1_index, max2_index, max3_index, mediak);

	double keresett_diak_mediaja = media_kereses(csaladnevek, keresztnevek, mediak, keresett_csaladnev, keresett_keresztnev);

	if (elso_harom(max1_index, max2_index, max3_index, mediak, keresett_diak_mediaja)) {
		cout << "igen";
	}
	else {
		cout << "nem";
	}

	return 0;
}