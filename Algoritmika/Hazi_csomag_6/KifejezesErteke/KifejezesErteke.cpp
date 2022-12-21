/*Boda Norbert
511-es csoport
Lab6/07
Legyen két halmaz: 𝐴 = {𝑎1, 𝑎2, . . . , 𝑎𝑚} és 𝐵 = {𝑏1, 𝑏2, . . . , 𝑏𝑛}. Határozzuk
meg a 𝐵 halmaz azon 𝑋 = {𝑥1, 𝑥2, . . . 𝑥𝑚} részhalmazát, amelynek megfelelően
az 𝐸 = 𝑎1𝑥1 + 𝑎2𝑥2 + . . . + 𝑎𝑚𝑥𝑚 kifejezés értéke a lehető legnagyobb.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void beolvas(short& A_halmaz_hossza, vector<int>& A, short& B_halmaz_hossza, vector<int>& B) {
	cin >> A_halmaz_hossza;
	A.resize(A_halmaz_hossza);
	for (short i = 0; i < A_halmaz_hossza; i++) {
		cin >> A[i];
	}
	cin >> B_halmaz_hossza;
	B.resize(B_halmaz_hossza);
	for (short i = 0; i < B_halmaz_hossza; i++) {
		cin >> B[i];
	}
}

//a fuggveny osszeadja a legnagyobb es a legkisebb szamokat, igy a vegen csak negativ vagy csak pozitiv szamok lesznek benne
void egyszerusit(vector<long long>& szorzatok) {
	sort(szorzatok.begin(), szorzatok.end());
	int i = 0;
	while (szorzatok[i] <= 0) {
		i++;
	}
	i--;
	while (i >= 0) {
		if (szorzatok[i] <= 0) {
			if (szorzatok[szorzatok.size() - 1] > 0) {
				szorzatok[i] += szorzatok[szorzatok.size() - 1];
				szorzatok.pop_back();
			}
			else {
				break;
			}
		}
		else {
			i--;
		}
	}
}

//kiszamolja a megfelelo szorzat parokat es tarolja ezeket egy vectorban
void felepit(vector<int>& A, vector<int>& B, vector<long long>& szorzatok) {
	short i = A.size() - 1;
	short j = B.size() - 1;
	short k = 0;
	while (i >= 0 && A[i] >= 0) {
		long long a = A[i], b = B[j];
		szorzatok[k] = a * b;
		i--;
		j--;
		k++;
	}
	if (i >= 0) {
		short index = 0;
		j = 0;
		while (index <= i) {
			long long a = A[index], b = B[j];
			szorzatok[k] = a * b;
			index++;
			j++;
			k++;
		}
	}
	egyszerusit(szorzatok);
	sort(szorzatok.begin(), szorzatok.end());
}

void osszead(string& szam1, long long& szam2) {
	unsigned long long masolat = (unsigned long long)(abs(szam2));
	string szam2_str = to_string(masolat);
	short i = 0, carry = 0;
	while (i < szam1.size() && i < szam2_str.size()) {
		short szamjegy = (szam1[szam1.size() - i - 1] - '0') + (szam2_str[szam2_str.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1[szam1.size() - i - 1] = szamjegy + '0';
		i++;
	}
	while (i < szam1.size()) {
		short szamjegy = (szam1[szam1.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1[szam1.size() - i - 1] = szamjegy + '0';
		i++;
	}
	while (i < szam2_str.size()) {
		short szamjegy = (szam2_str[szam2_str.size() - i - 1] - '0') + carry;
		carry = szamjegy / 10;
		szamjegy = szamjegy % 10;
		szam1 = to_string(szamjegy) + szam1;
		i++;
	}
	if (carry) {
		szam1 = "1" + szam1;
	}
}

string KifejezesErteke(vector<int>& A, vector<int>& B) {
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	vector<long long> szorzatok(A.size());
	felepit(A, B, szorzatok);
	string megoldas = "0";
	for (int i = 0; i < szorzatok.size(); i++) {
		osszead(megoldas, szorzatok[i]);
	}
	//mivel az osszes elemnek ugyanaz lesz az elojele, ezert ha az elso < 0, akkor az osszeg is < 0 lesz
	if (szorzatok[0] < 0) {
		megoldas = "-" + megoldas;
	}
	return megoldas;
}

void kiir(string& megoldas) {
	cout << megoldas;
}

int main() {
	short A_halmaz_hossza, B_halmaz_hossza;
	vector<int> A, B;
	beolvas(A_halmaz_hossza, A, B_halmaz_hossza, B);
	 
	string megoldas = KifejezesErteke(A, B);
	
	kiir(megoldas);
	return 0;
}