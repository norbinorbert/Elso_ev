#include "OupSz_Utemezo.h"
#include <iostream>

using namespace std;

OupSz_Utemezo::OupSz_Utemezo(int szam, int hossz) {
	sorok_szama = szam;
	max_hossz = hossz;
	a = new OupSz_Sor*[sorok_szama];
	for (int i = 0; i < sorok_szama; i++) {
		a[i] = new OupSz_Sor(max_hossz);
	}
}

OupSz_Utemezo::~OupSz_Utemezo() {
	for (int i = 0; i < sorok_szama; i++) {
		delete[]a[i];
	}
	delete[]a;
}

void OupSz_Utemezo::InsertProcess(int sor, int elem) {
	if (!a[sor]->InsertElement(elem)) {
		for (int i = 0; i < sorok_szama; i++) {
			if (i != sor && a[i]->InsertElement(elem)) {
				return;
			}
		}
	}
}

int OupSz_Utemezo::PickProcess() {
	int sor = rand() % sorok_szama;
	return a[sor]->PopElement();
}

void OupSz_Utemezo::PrintProcesses() {
	for (int i = 0; i < sorok_szama; i++) {
		a[i]->PrintList();
	}
}