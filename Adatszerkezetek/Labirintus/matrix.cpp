#include "matrix.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Matrix* Letrehoz(int sor, int oszlop) {
	Matrix* A = new Matrix;
	A->n = sor;
	A->m = oszlop;
	A->tabla.resize(sor, vector<int>(oszlop));
	return A;
}

void Felszabadit(Matrix* A) {
	delete A;
}

void Kiir(Matrix* A){
	for (int i = 0; i < A->n; i++) {
		for (int j = 0; j < A->m; j++) {
			cout << A->tabla[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int GetSzelesseg(Matrix* A){
	return A->m;
}

int GetHosszusag(Matrix* A) {
	return A->n;
}

void SetElem(Matrix* A, int sor, int oszlop, int ertek) {
	A->tabla[sor][oszlop] = ertek;
}

int GetElem(Matrix* A, int sor, int oszlop) {
	return A->tabla[sor][oszlop];
}
