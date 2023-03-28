#include "matrix_linearis.h"

#ifndef Labirintus_h
#define Labirintus_h

typedef struct Labirintus {
	Matrix* labirintus;
	int n, m;
	int x, y;
}Labirintus;

Labirintus* LetrehozVeletlen(int, int);
Labirintus* LetrehozFilebol(const char*);

void Felszabadit(Labirintus*);

void Kiir(Labirintus*);

void Lepes(Labirintus*);

void Pozicionalas(Labirintus*, int, int);

#endif // !Labirintus_h
