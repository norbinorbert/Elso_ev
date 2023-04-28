//Boda Norbert, 511

#include <iostream>

using namespace std;

template <typename T>
class Verem {
	int max_meret;
	int meret;
	struct node {
		T adat;
		node* elozo;
		node* kovetkezo;
	};
	node* fej;
	node* vege;
public:
	Verem(int);
	~Verem();
	T& operator[](int);
	void operator()(T (*func)(T));
	void betesz(T);
	T kivesz();
	void kiir();
};

template<typename T>
Verem<T>::Verem(int n) {
	fej = new node;
	vege = new node;
	fej->adat = 0;
	vege->adat = 0;
	fej->elozo = NULL;
	fej->kovetkezo = vege;
	vege->elozo = fej;
	vege->kovetkezo = NULL;
	meret = 0;
	max_meret = n;
}

template<typename T>
Verem<T>::~Verem() {
	while (fej->kovetkezo != vege) {
		node* a = fej->kovetkezo;
		fej->kovetkezo = a->kovetkezo;
		delete a;
	}
	delete fej;
	delete vege;
}


template<typename T>
T& Verem<T>::operator[](int index) {
	int i = 0;
	node* a = fej->kovetkezo;
	while (i != index) {
		a = a->kovetkezo;
		i++;
	}
	return a->adat;
}

template<typename T>
T duplaz(T a) {
	return a * 2;
}

template<typename T>
void Verem<T>::operator()(T (*duplaz)(T)) {
	node* a = fej->kovetkezo;
	while (a != vege) {
		a->adat = duplaz(a->adat);
		a = a->kovetkezo;
	}
}

template<typename T>
void Verem<T>::betesz(T elem) {
	if (meret == max_meret) {
		throw "Hiba! Tulcsordulas";
	}
	meret++;
	node* tmp = new node;
	tmp->adat = elem;
	tmp->elozo = vege->elozo;
	tmp->kovetkezo = vege;
	vege->elozo->kovetkezo = tmp;
	vege->elozo = tmp;
}

template<typename T>
T Verem<T>::kivesz() {
	if (meret == 0) {
		throw "Hiba! Alulcsordulas";
	}
	node* a = vege->elozo;
	T tmp = a->adat;
	a->elozo->kovetkezo = vege;
	vege->elozo = a->elozo;
	delete a;
	meret--;
	return tmp;
}

template<typename T>
void Verem<T>::kiir() {
	node* a = fej->kovetkezo;
	while (a != vege) {
		cout << a->adat << " ";
		a = a->kovetkezo;
	}
	cout << endl;
}


int main() {
	Verem<int> a(5);
	try {
		a.kivesz();
		a.kivesz();
	}
	catch (const char* s) {
		cout << s << endl;
	}
	a.betesz(1);
	a.betesz(2);
	a.betesz(3);
	a.betesz(4);
	a.betesz(5);
	try {
		a.betesz(6);
		a.betesz(7);
	}
	catch (const char* s) {
		cout << s << endl;
	}
	cout << "Verem tartalma: ";
	a.kiir();

	cout << "Harmadik elem: " << a[3] << endl;
	a[3] = 10;
	cout << "Harmadik elem: " << a[3] << endl;
	cout << "Utolso elem: " << a.kivesz() << endl;
	a(duplaz);
	cout << "Duplazas utan: ";
	a.kiir();
	return 0;
}