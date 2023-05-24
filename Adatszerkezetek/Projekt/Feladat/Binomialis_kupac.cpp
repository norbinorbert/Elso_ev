#include "Binomialis_kupac.h"
#include <iostream>
#include <climits>
#include <stack>

using namespace std;

binomialis_kupac::binomialis_kupac() {
	fej = NULL;
}

binomialis_kupac::~binomialis_kupac() {
	if (fej != NULL) {
		destroy(fej);
	}
	else {
		delete fej;
	}
}

void binomialis_kupac::destroy(node* tmp) {
	if (tmp != NULL) {
		if (tmp->gyerek != NULL) {
			destroy(tmp->gyerek);
		}
		if (tmp->testver != NULL) {
			destroy(tmp->testver);
		}
	}
	delete tmp;
}

void binomialis_kupac::binomialis_kupac::beszur(int kulcs) {
	node* tmp = new node;
	tmp->adat = kulcs;
	tmp->fokszam = 0;
	tmp->gyerek = NULL;
	tmp->szulo = NULL;
	tmp->testver = NULL;
	if (fej == NULL) {
		fej = tmp;
	}
	else {
		binomialis_kupac* a = new binomialis_kupac;
		a->fej = tmp;
		egyesit(a);
		delete a;
	}
}

void binomialis_kupac::egyesit(binomialis_kupac* tmp) {
	node* a = fej;
	node* b = tmp->fej;
	fej = osszefesul(a, b);
	if (fej == NULL) {
		return;
	}
	node* elozo = NULL;
	a = fej;
	node* kovetkezo = a->testver;
	while (kovetkezo != NULL) {
		if ((a->fokszam != kovetkezo->fokszam) || (kovetkezo->testver != NULL && kovetkezo->testver->fokszam == a->fokszam)) {
			elozo = a;
			a = kovetkezo;
		}
		else {
			if (a->adat <= kovetkezo->adat) {
				a->testver = kovetkezo->testver;
				binomialis_osszekapcsolas(a, kovetkezo);
			}
			else {
				if (elozo == NULL) {
					fej = kovetkezo;
				}
				else {
					elozo->testver = kovetkezo;
				}
				binomialis_osszekapcsolas(kovetkezo, a);
				a = kovetkezo;
			}
		}
		kovetkezo = a->testver;
	}
	tmp->fej = NULL;
}

binomialis_kupac::node* binomialis_kupac::osszefesul(node* a, node* b) {
	node* uj;
	if (a != NULL && b != NULL) {
		if (a->fokszam <= b->fokszam) {
			uj = a;
			a = a->testver;
		}
		else {
			uj = b;
			b = b->testver;
		}
	}
	else {
		if (a != NULL) {
			uj = a;
			a = a->testver;
		}
		else if (b != NULL) {
			uj = b;
			b = b->testver;
		}
		else {
			uj = NULL;
		}
	}
	node* uj_fej = uj;

	while (a != NULL && b != NULL) {
		if (a->fokszam <= b->fokszam) {
			uj->testver = a;
			uj = uj->testver;
			a = a->testver;
		}
		else {
			uj->testver = b;
			uj = uj->testver;
			b = b->testver;
		}
	}
	while (a != NULL) {
		uj->testver = a;
		uj = uj->testver;
		a = a->testver;

	}
	while (b != NULL) {
		uj->testver = b;
		uj = uj->testver;
		b = b->testver;
	}
	return uj_fej;
}

void binomialis_kupac::binomialis_osszekapcsolas(node* a, node* b) {
	b->szulo = a;
	b->testver = a->gyerek;
	a->gyerek = b;
	a->fokszam++;
}

int binomialis_kupac::minimum() {
	node* a = minimum_node();
	if (a == NULL) {
		return 0;
	}
	return a->adat;
}

void binomialis_kupac::torol_minimum() {
	if (fej == NULL) {
		return;
	}
	node* minNode = minimum_node();
	if (minNode == fej) {
		fej = minNode->testver;
	}
	else {
		node* tmp = fej;
		while (tmp->testver != minNode) {
			tmp = tmp->testver;
		}
		tmp->testver = minNode->testver;
	}
	stack<node*> stack;
	node* tmp = minNode;
	if (tmp->gyerek != NULL) {
		tmp = tmp->gyerek;
		while (tmp != NULL) {
			stack.push(tmp);
			tmp = tmp->testver;
		}
	}
	delete minNode;
	binomialis_kupac* a = new binomialis_kupac;
	if (!stack.empty()) {
		a->fej = stack.top();
		stack.pop();
		a->fej->szulo = NULL;
		tmp = a->fej;
		while (!stack.empty()) {
			node* b = stack.top();
			stack.pop();
			b->szulo = NULL;
			b->testver = NULL;
			tmp->testver = b;
			tmp = tmp->testver;
		}
	}
	egyesit(a);
	delete a;
}

binomialis_kupac::node* binomialis_kupac::minimum_node() {
	if (fej == NULL) {
		return NULL;
	}
	node* tmp = fej;
	node* minNode = fej;
	int minimum = fej->adat;
	tmp = tmp->testver;
	while (tmp != NULL) {
		if (tmp->adat < minimum) {
			minimum = tmp->adat;
			minNode = tmp;
		}
		tmp = tmp->testver;
	}
	return minNode;
}
