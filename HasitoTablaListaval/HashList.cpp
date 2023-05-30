#include "HashList.h"

HashList::HashList(int meret) {
	t.resize(meret);
}

int HashList::HasitoFuggveny(string a) {
	int index = 0;
	for (int i = 0; i < a.size(); i++) {
		index += a[i] - 'A';
	}
	return index % t.size();
}

void HashList::beszur(string a, double ertek) {
	int index = HasitoFuggveny(a);
	t[index].beszuras_vegere(a, ertek);
}

void HashList::kiir() {
	for (int i = 0; i < t.size(); i++) {
		t[i].kiir();
	}
}

double& HashList::operator[](string a) {
	int index = HasitoFuggveny(a);
	Elem* tmp = t[index].find(a);
	
	if (tmp != NULL) {
		return tmp->atlag;
	}
	else {
		t[index].beszuras_vegere(a, 0);
		tmp = t[index].find(a);
		return tmp->atlag;
	}
}