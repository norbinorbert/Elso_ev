/*Boda Norbert
511-es csoport
Lab3/04
Írjunk algoritmust, amely egy adott 𝑥 páros számot felír két különböző
prímszám összegeként (Goldbach-sejtés).*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void beolvas(unsigned int& szam) {
	cin >> szam;
	return;
}

//legeneralja a primszamokat 9781-ig, mivel "3,3... * 10^18-ig" minden paros szam felirhato olyan ket primszam osszegekent,
//amelyek kozul az egyik biztosan  <= 9781-nel (Goldbach's conjecture wikipedia)
void Eratoszthenesz(vector<bool>& prim_e) {
	prim_e.resize(9782);
	for (int i = 2; i <= 9781; i++) {
		prim_e[i] = true;
	}
	double gyok = sqrt(9781);
	for (int i = 2; i <= gyok; i++) {
		if (prim_e[i]) {
			int j = i * i;
			while (j <= 9781) {
				prim_e[j] = false;
				j = j + i;
			}
		}
	}
	return;
}

//a primszamokat atirja egy bool vectorbol egy unsigned int vectorba
void kivalaszt(vector<bool>& prim_e, vector<unsigned int>& primek) {
	for (int i = 3; i < prim_e.size(); i++) {
		if (prim_e[i])
		{
			primek.push_back(i);
		}
	}
	return;
}

//megnezi ha egy szam prim
bool prim(unsigned int szam) {
	for (int i = 2; i < sqrt(szam); i++) {
		if (szam % i == 0) {
			return false;
		}
	}
	return true;
}

//keresi a ket primszamot amelyek osszege egyenlo a szammal
void keres(unsigned int& szam, unsigned int& elso, unsigned int& masodik, vector<unsigned int>& primek) {
	for (int i = 0; i < primek.size(); i++) {
		if (prim(szam - primek[i])) {
			elso = primek[i];
			masodik = szam - primek[i];
			return;
		}
	}
	return;
}

void kiir(unsigned int& szam, unsigned int& elso, unsigned int& masodik) {
	cout << szam << " = " << elso << " + " << masodik;
	return;
}

int main() {
	unsigned int szam;
	beolvas(szam);

	vector<bool> prim_e;
	Eratoszthenesz(prim_e);

	vector<unsigned int> primek;
	kivalaszt(prim_e, primek);

	unsigned int elso_prim = 0, masodik_prim = 0;
	keres(szam, elso_prim, masodik_prim, primek);

	kiir(szam, elso_prim, masodik_prim);

	return 0;
}