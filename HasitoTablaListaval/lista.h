#ifndef LISTA_H
#define LISTA_H

#include "elem.h"
#include <string>

using namespace std;

class Lista {
	Elem* fej;
	Elem* vege;
	int rendezett;
public:
	Lista(int = 0);
	~Lista();
	void kiir();
	void beszuras_elejere(string, double);
	void beszuras_elejere(Elem*);
	void beszuras_vegere(string, double);
	void beszuras_vegere(Elem*);
	void beszuras_rendezett(string, double);
	void beszuras_rendezett(Elem*);
	void rendezes(int);
	Elem*& find(string);
};

#endif // LISTA_H
