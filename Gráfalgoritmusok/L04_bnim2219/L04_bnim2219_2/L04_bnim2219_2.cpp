//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

struct Elek {
	int u, v, suly;
};

void beolvas(int&, int&, int&, vector<Elek>&);
void Bellman_Ford(int, int, int, vector<Elek>&);
void kiir(vector<int>&, vector<long long>&, int, bool);
void kiir_rekurziv(int, vector<int>&, vector<long long>&, ofstream&);

int main() {
	int csomopontok_szama, elek_szama, kiindulasi_pont;
	vector<Elek> elek;
	beolvas(csomopontok_szama, elek_szama, kiindulasi_pont, elek);

	Bellman_Ford(csomopontok_szama, elek_szama, kiindulasi_pont, elek);
	return 0;
}

//filebol beolvassa az adatokat es egy struktura segitsegevel vectorban tarolja az eleket
void beolvas(int& csucsok_szama, int& elek_szama, int& kiindulasi_pont, vector<Elek>& elek) {
	ifstream fin("graf.in");
	fin >> csucsok_szama >> elek_szama >> kiindulasi_pont;
	elek.resize(elek_szama);
	for (int i = 0; i < elek_szama; i++) {
		fin >> elek[i].u >> elek[i].v >> elek[i].suly;
	}
	fin.close();
}

void Bellman_Ford(int csomopontok_szama, int elek_szama, int kiindulasi_pont, vector<Elek>& elek) {
	bool kor = false;

	//eltarolja minden csomopont szulejet
	vector<int> szulok(csomopontok_szama + 1, -1);

	//a tavolsagok a kivalasztott elek sulyai lesznek
	vector<long long> tavolsag(csomopontok_szama + 1, INT_MAX);

	tavolsag[kiindulasi_pont] = 0;

	//csomopontok szama - 1 alkalommal frissiti a megfelelo informaciokat
	for (int k = 1; k < csomopontok_szama; k++) {
		for (int i = 0; i < elek.size(); i++) {
			int csomopont = elek[i].u;
			int szomszedos_csomopont = elek[i].v;
			int suly = elek[i].suly;
			if (suly + tavolsag[csomopont] < tavolsag[szomszedos_csomopont]) {
				tavolsag[szomszedos_csomopont] = suly + tavolsag[csomopont];
				szulok[szomszedos_csomopont] = csomopont;
			}
		}
	}

	//bejarja meg egyszer az osszes elt es megnezi ha van-e negativ kor
	for (int i = 1; i < elek.size(); i++) {
		int csomopont = elek[i].u;
		int szomszedos_csomopont = elek[i].v;
		int suly = elek[i].suly;
		if (suly + tavolsag[csomopont] < tavolsag[szomszedos_csomopont]) {
			kor = true;
			break;
		}
	}

	kiir(szulok, tavolsag, kiindulasi_pont, kor);
}

void kiir(vector<int>& szulok, vector<long long>& tavolsag, int kiindulasi_pont, bool kor) {
	ofstream fout("graf.out");
	if (kor) {
		fout << "Van negativ kor";
		return;
	}
	for (int i = 1; i < szulok.size(); i++) {
		if (szulok[i] != -1) {
			fout << "A legrovidebb ut hossza " << i << "-ba: " << tavolsag[i] << endl;
			fout << "A legrovidebb ut " << i << "-ba: " << kiindulasi_pont << " ";
			kiir_rekurziv(i, szulok, tavolsag, fout);
			fout << endl;
		}
		else {
			if (i != kiindulasi_pont) {
				fout << "A legrovidebb ut hossza " << i << "-ba: " << "nem elerheto" << endl;
				fout << "A legrovidebb ut " << i << "-ba: " << "nem elerheto" << endl;
			}
		}
	}
	fout.close();
}

//kiirja az utat
void kiir_rekurziv(int csomopont, vector<int>& szulok, vector<long long>& tavolsag, ofstream& fout) {
	if (szulok[csomopont] != -1) {
		kiir_rekurziv(szulok[csomopont], szulok, tavolsag, fout);
		fout << csomopont << " ";
	}
}