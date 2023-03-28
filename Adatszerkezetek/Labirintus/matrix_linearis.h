#include <iostream>

using namespace std;

#ifndef matrix_linearis_h
#define matrix_linearis_h

typedef struct Matrix {
	int* tabla;
	int n, m;
}Matrix;

Matrix* Letrehoz(int, int);

void Felszabadit(Matrix*);

void Kiir(Matrix*);

int GetSzelesseg(Matrix*);
int GetHosszusag(Matrix*);

void SetElem(Matrix*, int, int, int);

int GetElem(Matrix*, int, int);

#endif
