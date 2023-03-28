#include <vector>
#include <iostream>

using namespace std;

#ifndef matrix_h
#define matrix_h

typedef struct Matrix {
	vector<vector<int>> tabla;
	int n, m;
}Matrix;

Matrix* Letrehoz(int, int);

void Felszabadit(Matrix*);

void Kiir(Matrix*);

int GetSzelesseg(Matrix*);
int GetHosszusag(Matrix*);

void SetElem(Matrix*, int, int, int);

int GetElem(Matrix*, int, int);

#endif // !Labirintus_h
