#include "Labirintus.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

Labirintus* LetrehozVeletlen(int sor, int oszlop) {
	srand(time(NULL));
	Labirintus* A = new Labirintus;
	A->labirintus = Letrehoz(sor, oszlop);
	A->n = GetHosszusag(A->labirintus);
	A->m = GetSzelesseg(A->labirintus);
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			int ertek = rand() % 2;
			SetElem(A->labirintus, i, j, ertek);
		}
	}
	return A;
}

Labirintus* LetrehozFilebol(const char* file) {
	ifstream fin(file);
	Labirintus* A = new Labirintus;
	int sor, oszlop;
	fin >> sor >> oszlop;
	A->labirintus = Letrehoz(sor, oszlop);
	A->n = sor;
	A->m = oszlop;
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			int ertek;
			fin >> ertek;
			SetElem(A->labirintus, i, j, ertek);
		}
	}
	return A;
}

void Felszabadit(Labirintus* A) {
	Felszabadit(A->labirintus);
	delete A;
}

void Kiir(Labirintus* A) {
	SetElem(A->labirintus, A->x, A->y, 2);
	Kiir(A->labirintus);
	SetElem(A->labirintus, A->x, A->y, 0);
}

void Lepes(Labirintus* A) {
	char irany;
	cin >> irany;
	if (irany == 'w') {
		if (A->x == 0) {
			return;
		}
		else {
			if (GetElem(A->labirintus, A->x - 1, A->y) == 0) {
				A->x--;
			}
		}
	}

	if (irany == 'a') {
		if (A->y == 0) {
			return;
		}
		else {
			if (GetElem(A->labirintus, A->x, A->y - 1) == 0) {
				A->y--;
			}
		}
	}

	if (irany == 's') {
		if (A->x == A->m - 1) {
			return;
		}
		else {
			if (GetElem(A->labirintus, A->x + 1, A->y) == 0) {
				A->x++;
			}
		}
	}

	if (irany == 'd') {
		if (A->y == A->n - 1) {
			return;
		}
		else {
			if (GetElem(A->labirintus, A->x, A->y + 1) == 0) {
				A->y++;
			}
		}
	}
}

void Pozicionalas(Labirintus*A, int x, int y) {
	A->x = x;
	A->y = y;
}
