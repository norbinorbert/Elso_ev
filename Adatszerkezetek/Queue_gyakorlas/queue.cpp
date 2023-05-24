#include <iostream>
#include "queue.h"

using namespace std;

queue::queue() {
	fej = new node;
	vege = new node;
	fej->elozo = NULL;
	fej->kovetkezo = vege;
	vege->elozo = fej;
	vege->kovetkezo = NULL;
}

queue::~queue() {
	while (fej->kovetkezo != vege) {
		node* a = fej->kovetkezo;
		fej->kovetkezo = a->kovetkezo;
		delete a;
	}
	delete fej;
	delete vege;
}

void queue::push(int adat) {
	node* uj = new node;
	uj->adat = adat;
	uj->elozo = vege->elozo;
	uj->kovetkezo = vege;
	vege->elozo->kovetkezo = uj;
	vege->elozo = uj;
}

void queue::pop() {
	if (!IsEmpty()) {
		node* a = fej->kovetkezo;
		fej->kovetkezo = a->kovetkezo;
		a->kovetkezo->elozo = fej;
		delete a;
	}
}
int queue::front() {
	return fej->kovetkezo->adat;
}

bool queue::IsEmpty() {
	if (fej->kovetkezo == vege) {
		return true;
	}
	return false;
}

void queue::ListQueue() {
	if (IsEmpty()) {
		cout << "A sor ures";
		cout << endl;
		return;
	}
	node* a = fej->kovetkezo;
	while (a != vege) {
		cout << a->adat << " ";
		a = a->kovetkezo;
	}
	cout << endl;
}