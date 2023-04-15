//Boda Norbert, 511

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Elek {
	int u, v, suly;
};

void beolvas(int&, int&, vector<Elek>&);
void Kruskal(int, int, vector<Elek>&);
void rendez_novekvo(vector<Elek>&);
int max_szamjegy(vector<Elek>&);
void radix(vector<Elek>&, int);
void count_sort(vector<Elek>&, int&);
unsigned long long oszto_kiszamolas(int);
int keres(vector<pair<int, int>>&, int);
void egyesit(vector<pair<int, int>>&, int, int);
void kiir(int, vector<Elek>&);

int main(){
	int csucsok_szama, elek_szama;
	vector<Elek> elek;
	beolvas(csucsok_szama, elek_szama, elek);

	Kruskal(csucsok_szama, elek_szama, elek);
	return 0;
}

//filebol beolvassa az adatokat es egy struktura segitsegevel vectorban tarolja az eleket
void beolvas(int& csucsok_szama, int& elek_szama, vector<Elek>& elek) {
	ifstream fin("graf.in");
	fin >> csucsok_szama >> elek_szama;
	elek.resize(elek_szama);
	for (int i = 0; i < elek_szama; i++) {
		fin >> elek[i].u >> elek[i].v >> elek[i].suly;
	}
	fin.close();
}

//Kruskal algoritmusa minimalis feszitofa meghatarozasara
void Kruskal(int csucsok_szama, int elek_szama, vector<Elek>& elek) {
	rendez_novekvo(elek);

	//minden csomopont kulon komponenshez tartozik az elejen, ezek egy diszjunk halmaz segitsegevel lesznek abrazolva
	vector<pair<int, int>> komponensek(csucsok_szama + 1);
	//a par elso eleme a csomopont szuloje a diszjunkt halmazban, 
	//a masodik pedig a reszfak magassaga (ugyanugy a diszjunkt halmazban)
	for (int i = 1; i < komponensek.size(); i++) {
		komponensek[i].first = i;
		komponensek[i].second = 1;
	}
	vector<Elek> feszitofa;
	int i = 0, j = 0, osszeg = 0;
	while (j < elek_szama && i < csucsok_szama - 1) {
		int u = elek[j].u;
		int v = elek[j].v;
		int u_gyoker = keres(komponensek, u);
		int v_gyoker = keres(komponensek, v);
		//amikor az egyik el vegpontjai kulon komponenshez(diszjunkt halmazhoz) tartoznak akkor hozzaadja a feszitofahoz
		if (u_gyoker != v_gyoker) {
			i++;
			feszitofa.push_back(elek[j]);
			osszeg += elek[j].suly;
			//frissiti a komponensek tombot
			egyesit(komponensek, u, v);
		}
		j++;
	}
	kiir(osszeg, feszitofa);
}

//rendezi az eleket a suly szerint novekvo sorrendben
void rendez_novekvo(vector<Elek>&elek){
	//radix sort pozitiv szamokra mukodik, ezert a negativakat kulon kell kezelni
	vector<Elek> pozitiv, negativ;
	for (int i = 0; i < elek.size(); i++) {
		if (elek[i].suly < 0) {
			negativ.push_back(elek[i]);
		}
		else {
			pozitiv.push_back(elek[i]);
		}
	}

	for (int i = 0; i < negativ.size(); i++) {
		negativ[i].suly *= -1;
	}
	radix(negativ, max_szamjegy(negativ));
	for (int i = 0; i < negativ.size(); i++) {
		negativ[i].suly *= -1;
	}

	radix(pozitiv, max_szamjegy(pozitiv));

	int index = 0;
	for (int i = negativ.size() - 1; i >= 0; i--) {
		elek[index] = negativ[i];
		index++;
	}
	for (int i = 0; i < pozitiv.size(); i++) {
		elek[index] = pozitiv[i];
		index++;
	}
}

//megnezi hany szamjegyu a legnagyobb szam, ennyiszer kell majd meghivni a count sortot
int max_szamjegy(vector<Elek>& elek) {
	if (elek.size() > 0) {
		int maximum = elek[0].suly;
		for (int i = 1; i < elek.size(); i++) {
			if (maximum < elek[i].suly) {
				maximum = elek[i].suly;
			}
		}
		string szj = to_string(maximum);
		return szj.size();
	}
}

void radix(vector<Elek>& szamok, int szj) {
	//minden szamjegyre meghivja a count sortot
	for (int i = 0; i < szj; i++) {
		count_sort(szamok, i);
	}
}

void count_sort(vector<Elek>& elek, int& szamjegy_pozicio) {
	unsigned long long oszto = oszto_kiszamolas(szamjegy_pozicio);
	vector<int> darab(10);
	for (int i = 0; i < elek.size(); i++) {
		darab[(elek[i].suly / oszto) % 10]++;
	}
	for (int i = 1; i < darab.size(); i++) {
		darab[i] += darab[i - 1];
	}

	//kotelezoen stabil rendezest kell vegezni
	vector<Elek> temp(elek.size());
	for (int i = elek.size() - 1; i >= 0; i--) {
		temp[darab[(elek[i].suly / oszto) % 10] - 1] = elek[i];
		darab[(elek[i].suly / oszto) % 10]--;
	}
	elek = temp;
}

//kiszamolja, hogy mennyivel kell osztani ahhoz, hogy a megfelelo szamjegyet lehessen elerni
unsigned long long oszto_kiszamolas(int szamjegy_pozicio) {
	unsigned long long oszto = 1;
	for (int i = 0; i < szamjegy_pozicio; i++) {
		oszto *= 10;
	}
	return oszto;
}

//megkeresi a halmaz reprezentansat(a fa gyokeret, ami a halmazt abrazolja)
int keres(vector<pair<int, int>>& komponensek, int csomopont){
	if (csomopont != komponensek[csomopont].first) {
		komponensek[csomopont].first = keres(komponensek, komponensek[csomopont].first);
	}
	return komponensek[csomopont].first;
}

//egyesit ket diszjunkt halmazt
void egyesit(vector<pair<int, int>>& komponensek, int u, int v) {
	int u_gyoker = keres(komponensek, u);
	int v_gyoker = keres(komponensek, v);
	if (u_gyoker == v_gyoker) {
		return;
	}

	if (komponensek[u_gyoker].second < komponensek[v_gyoker].second) {
		komponensek[u_gyoker].first = v_gyoker;
	}
	else {
		komponensek[v_gyoker].first = u_gyoker;
		if (komponensek[u_gyoker].second == komponensek[v_gyoker].second) {
			komponensek[u_gyoker].second++;
		}
	}
}

//fileba kiirja a minimalis feszitofa koltseget es az eleket
void kiir(int osszeg, vector<Elek>& feszitofa) {
	ofstream fout("graf.out");
	fout << osszeg << endl;
	for (int i = 0; i < feszitofa.size(); i++) {
		fout << feszitofa[i].u << " " << feszitofa[i].v << endl;
	}
	fout.close();
}