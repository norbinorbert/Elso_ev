#include "halasto.h"
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void Init() {
	srand(time(NULL));
}

Halasto* Create(int sor, int oszlop) {
	Halasto* A = new Halasto;
	A->n = sor;
	A->m = oszlop;
	A->to = new int*[sor];
	for (int i = 0; i < sor; i++) {
		A->to[i] = new int[oszlop] {0};
	}
	A->db = 0;
	A->fajtak_db = 0;
	A->fajtak = new int[101] {0};
	return A;
}

Halasto* CreateFromFile(const char* file) {
	ifstream in(file);
	int sor;
	in >> sor;
	int oszlop;
	in >> oszlop;
	Halasto* A = Create(sor, oszlop);
	for (int i = 0; i < sor; i++) {
		for (int j = 0; j < oszlop; j++) {
			int fajta;
			in >> fajta;
			PutHal(A, i, j, fajta);
		}
	}
	return A;
}

Halasto* CreateWild(int sor, int oszlop) {
	Halasto* A = Create(sor, oszlop);
	
	for (int i = 0; i < sor; i++) {
		for (int j = 0; j < oszlop; j++) {
			int fajta = rand() % 101;
			PutHal(A, i, j, fajta);
		}
	}

	return A;
}

void Destroy(Halasto* A) {
	delete[]A->fajtak;
	for (int i = 0; i < A->n; i++) {
		delete[]A->to[i];
	}
	delete[]A->to;
	delete A;
}

void PutHal(Halasto* A, int sor, int oszlop, int fajta) {
	if (A->to[sor][oszlop] == 0) {
		A->to[sor][oszlop] = fajta;
		A->db++;
		if (A->fajtak[fajta] == 0) {
			A->fajtak_db++;
		}
		A->fajtak[fajta]++;
	}
}

int GetHal(Halasto* A, int sor, int oszlop) {
	return A->to[sor][oszlop];
}

int GetSzelesseg(Halasto* A) {
	return A->m;
}

int GetHosszusag(Halasto* A) {
	return A->n;
}

int FajtakSzama(Halasto* A) {
	return A->fajtak_db;
}

void FajtaElofordulasa(Halasto* A) {
	for (int i = 1; i < 101; i++) {
		if (A->fajtak[i] != 0) {
			cout << i << ": " << A->fajtak[i] << endl;
		}
	}
	cout << endl;
}

Halasto* Atont(Halasto* A, Halasto* B) {
	int index = 1;
	while (index<101 && A->fajtak[index] == 0) {
		index++;
	}
	if (index == 101) {
		return B;
	}

	for (int i = 0; i < B->n; i++) {
		for (int j = 0; j < B->m; j++) {
			if (B->to[i][j] == 0) {
				B->to[i][j] = A->fajtak[index];
			}
		}
	}

	return B;
}

int SzabadAHely(Halasto* A, int sor, int oszlop) {
	if (A->to[sor][oszlop] == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int GetHalKezdo(Halasto* A) {
	return GetHalAdvanced(A, 0, A->n-1, 0, A->m-1);
}

int GetHalAdvanced(Halasto* A, int kezdosor, int vegsosor, int kezdooszlop, int vegsooszlop) {
	int mod = max(kezdosor, vegsosor) - min(kezdosor, vegsosor) + 1;
	int sor = rand() % mod;
	sor += min(kezdosor, vegsosor);

	mod = max(kezdooszlop, vegsooszlop) - min(kezdooszlop, vegsooszlop) + 1;
	int oszlop = rand() % mod;
	oszlop += min(kezdooszlop, vegsooszlop);

	int hal = A->to[sor][oszlop];
	A->to[sor][oszlop] = 0;
	if (hal != 0) {
		A->fajtak[hal]--;
		if (A->fajtak[hal] == 0) {
			A->fajtak_db--;
		}
		A->db--;
	}
	return hal;
}

void StatKezdo(Halasto* A) {
	FajtaElofordulasa(A);
}

void StatHalado(Halasto* A, int kezdosor, int vegsosor, int kezdooszlop, int vegsooszlop) {
	int fajtak[101]{ 0 };
	for (int i = kezdosor; i <= vegsosor; i++) {
		for (int j = kezdooszlop; j <= vegsooszlop; j++) {
			if (A->to[i][j] != 0) {
				fajtak[A->to[i][j]]++;
			}
		}
	}
	for (int i = 1; i < 101; i++) {
		if (fajtak[i] != 0) {
			cout << i << ": " << fajtak[i] << endl;
		}
	}
	cout << endl;
}

void PrintH(Halasto* A) {
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			cout << A->to[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}