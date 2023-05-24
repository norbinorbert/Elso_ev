#include <iostream>
#include <string>
#include "lista.h"

using namespace std;

Lista::Lista(int rendezett = 0) {
	fej = NULL;
	vege = NULL;
	if (rendezett == 1 || rendezett == 2) {
		this->rendezett = rendezett;
	}
	else {
		this->rendezett = 0;
	}
}

Lista::~Lista() {
	while (fej != NULL) {
		Elem* a = fej;
		fej = fej->kovetkezo;
		delete a;
	}
}

void Lista::kiir() {
	Elem* a = fej;
	while (a != NULL) {
		a->kiir();
		a = a->kovetkezo;
	}
}

void Lista::beszuras_elejere(string n, double a) {
	Elem* tmp = new Elem(n, a);
	if (fej == NULL) {
		fej = tmp;
		vege = tmp;
	}
	else {
		tmp->kovetkezo = fej;
		fej = tmp;
	}
}

void Lista::beszuras_elejere(Elem* a) {
	if (fej == NULL) {
		fej = a;
		vege = a;
	}
	else {
		a->kovetkezo = fej;
		fej = a;
	}
}

void Lista::beszuras_vegere(string n, double a) {
	Elem* tmp = new Elem(n, a);
	if (fej == NULL) {
		fej = tmp;
		vege = tmp;
	}
	else {
		vege->kovetkezo = tmp;
		vege = tmp;
	}
}

void Lista::beszuras_vegere(Elem* a) {
	if (fej == NULL) {
		fej = a;
		vege = a;
	}
	else {
		vege->kovetkezo = a;
		vege = a;
	}
}

void Lista::beszuras_rendezett(string n, double a) {
	Elem* tmp = new Elem(n, a);
	if (fej == NULL) {
		fej = tmp;
		vege = tmp;
	}
	if (rendezett == 0 || rendezett == 1) {
		Elem* a = fej;
		if (a->nev > tmp->nev) {
			beszuras_elejere(tmp);
			return;
		}
		while (a != vege && a->kovetkezo->nev < tmp->nev) {
			a = a->kovetkezo;
		}
		tmp->kovetkezo = a->kovetkezo;
		a->kovetkezo = tmp;
	}
	if (rendezett == 2) {
		Elem* a = fej;
		if (a->atlag > tmp->atlag) {
			beszuras_elejere(tmp);
			return;
		}
		while (a != vege && a->kovetkezo->atlag < tmp->atlag) {
			a = a->kovetkezo;
		}
		tmp->kovetkezo = a->kovetkezo;
		a->kovetkezo = tmp;
	}
}

void Lista::beszuras_rendezett(Elem* tmp) {
	if (fej == NULL) {
		fej = tmp;
		vege = tmp;
	}
	if (rendezett == 0 || rendezett == 1) {
		Elem* a = fej; 
		if (a->nev > tmp->nev) {
			beszuras_elejere(tmp);
			return;
		}
		while (a != vege && a->kovetkezo->nev < tmp->nev) {
			a = a->kovetkezo;
		}
		tmp->kovetkezo = a->kovetkezo;
		a->kovetkezo = tmp;
	}
	if (rendezett == 2) {
		Elem* a = fej; 
		if (a->atlag > tmp->atlag) {
			beszuras_elejere(tmp);
			return;
		}
		while (a != vege && a->kovetkezo->atlag < tmp->atlag) {
			a = a->kovetkezo;
		}
		tmp->kovetkezo = a->kovetkezo;
		a->kovetkezo = tmp;
	}
}

void Lista::rendezes(int r) {
	if (fej == NULL || r < 1 || r > 2) {
		return;
	}

	rendezett = r;

	Elem* temp_pozicio = NULL;
	bool rendezett = true;
	do {
		Elem* utolso_pozicio = fej;
		while (utolso_pozicio->kovetkezo != temp_pozicio) {
			utolso_pozicio = utolso_pozicio->kovetkezo;
		}
		rendezett = true;
		Elem* i = fej;
		if (i != utolso_pozicio) {
			while (i != utolso_pozicio) {
				if (r == 1) {
					if (i->nev > i->kovetkezo->nev) {
						swap(i->nev, i->kovetkezo->nev);
						swap(i->atlag, i->kovetkezo->atlag);
						rendezett = false;
						temp_pozicio = i->kovetkezo;
					}
				}
				if (r == 2) {
					if (i->atlag > i->kovetkezo->atlag) {
						swap(i->nev, i->kovetkezo->nev);
						swap(i->atlag, i->kovetkezo->atlag);
						rendezett = false;
						temp_pozicio = i->kovetkezo;
					}
				}
				i = i->kovetkezo;
			}
		}
	} while (!rendezett);
}