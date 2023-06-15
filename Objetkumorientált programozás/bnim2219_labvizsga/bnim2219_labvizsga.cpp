//Boda Norbert, 511
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class TermekAr {
protected:
	char* nev;
	int eur;
	int cent;
public:
	TermekAr();
	TermekAr(const char*, int, int);
	TermekAr(const TermekAr&);
	~TermekAr();
	TermekAr& operator=(const TermekAr&);
	TermekAr& operator++();
	TermekAr operator++(int);
	bool operator<=(const TermekAr&);
	void kiirNev();
	virtual void kiirAr();
	void kiir();
	operator int();
};

TermekAr::TermekAr() {
	nev = new char[1];
	nev[0] = 0;
	eur = 0;
	cent = 0;
}

TermekAr::TermekAr(const char* nev, int eur, int cent) {
	this->nev = new char[strlen(nev) + 1];
	strcpy(this->nev, nev);
	this->nev[strlen(nev)] = 0;
	this->eur = eur;
	while (cent >= 100) {
		cent -= 100;
		this->eur++;
	}
	this->cent = cent;
}

TermekAr::TermekAr(const TermekAr& t) {
	nev = new char[strlen(t.nev) + 1];
	strcpy(nev, t.nev);
	nev[strlen(nev)] = 0;
	eur = t.eur;
	cent = t.cent;
}

TermekAr::~TermekAr() {
	delete[]nev;
}

TermekAr& TermekAr::operator=(const TermekAr& t) {
	if (this != &t) {
		delete[]nev;
		nev = new char[strlen(t.nev) + 1];
		strcpy(nev, t.nev);
		eur = t.eur;
		cent = t.cent;
	}
	return *this;
}

TermekAr& TermekAr::operator++() {
	cent++;
	if (cent >= 100) {
		cent -= 100;
		eur++;
	}
	return *this;
}

TermekAr TermekAr::operator++(int) {
	TermekAr t = TermekAr(nev, eur, cent);
	cent++;
	if (cent >= 100) {
		cent -= 100;
		eur++;
	}
	return t;
}

bool TermekAr::operator<=(const TermekAr& t) {
	if (eur < t.eur) {
		return true;
	}
	if (eur == t.eur) {
		if (cent <= t.cent) {
			return true;
		}
	}
	return false;
}

void TermekAr::kiirNev() {
	cout << nev << endl;
}

void TermekAr::kiirAr() {
	cout << eur << " euro " << cent << " cent" << endl;
}

void TermekAr::kiir() {
	kiirNev();
	kiirAr();
}

TermekAr::operator int() {
	return eur * 100 + cent;
}

class TermekArAFA : public TermekAr {
	int AFA;
public:
	class ErvenytelenAFA {};
	TermekArAFA();
	TermekArAFA(const char*, int, int, int);
	TermekArAFA(const TermekArAFA&);
	~TermekArAFA() {};
	void kiirAr();
};

TermekArAFA::TermekArAFA():TermekAr() {
	AFA = 0;
}

TermekArAFA::TermekArAFA(const char* nev, int eur, int cent, int AFA): TermekAr(nev, eur, cent) {
	if (AFA < 0 || AFA > 30) {
		throw ErvenytelenAFA();
	}
	this->AFA = AFA;
}

TermekArAFA::TermekArAFA(const TermekArAFA& t): TermekAr(t.nev, t.eur, t.cent) {
	this->AFA = t.AFA;
}

void TermekArAFA::kiirAr() {
	int tmp = (int)TermekAr(nev, eur, cent);
	tmp += tmp * AFA / 100;
	TermekAr(nev, 0, tmp).kiirAr();
}

class Leltar {
	TermekArAFA* termekek;
	int max_termekek;
	int meret;
public:
	Leltar(int);
	void hozzaadTermek(const TermekArAFA&);
	TermekArAFA& legolcsobbTermek();
};

Leltar::Leltar(int max) {
	termekek = new TermekArAFA[max];
	max_termekek = max;
	meret = 0;
}

void Leltar::hozzaadTermek(const TermekArAFA& t) {
	if (meret == max_termekek) {
		throw "Tele van a leltar";
	}
	termekek[meret++] = t;
}

TermekArAFA& Leltar::legolcsobbTermek() {
	if (meret == 0) {
		throw "A leltar ures";
	}
	int index = 0;
	auto ar = (int)termekek[0];
	for (int i = 1; i < meret; i++) {
		if ((int)termekek[i] < ar) {
			index = i;
			ar = (int)termekek[i];
		}
	}
	return termekek[index];
}

int main() {
	cout << "*************TermekAr kiprobalasa*************" << endl;
	TermekAr a("alma", 0, 401);
	a.kiirNev();
	a.kiirAr();

	TermekAr b(a);
	b++;
	b.kiir();

	TermekAr c = b;
	++c;
	c.kiir();

	cout << "a <= b: " << boolalpha << (a <= b) << endl;

	cout << "c centben = " << (int)c << endl;
	cout << "*************Leltar es TermekArAFA kiprobalasa *************" << endl;
	//leltar letrehozasa
	Leltar leltar(5);

	//legolcsobb termek lekerdezese es kiirasa, ha ures a leltar
	try {
		auto& termek = leltar.legolcsobbTermek();
		termek.kiir();
	}
	catch (const char* s) {
		cout << s << endl;
	}

	//termek letrehozasa es hozzaadasa a leltarhoz
	TermekArAFA alma("alma", 1, 100, 3);
	leltar.hozzaadTermek(alma);

	//ervenytelen termek letrehozasa es hozzaadasa a leltarhoz
	try {
		TermekArAFA dohany("dohany", 5, 23, 50);
		leltar.hozzaadTermek(dohany);
	}
	catch (TermekArAFA::ErvenytelenAFA) {
		cout << "Ervenytelen a megadott AFA" << endl;
	}

	TermekArAFA korte("korte", 1, 10, 5);
	leltar.hozzaadTermek(korte);

	//masolo konstruktor hasznalata
	TermekArAFA korte2(korte);
	leltar.hozzaadTermek(korte2);

	TermekArAFA barack("barack", 2, 0, 10);
	leltar.hozzaadTermek(barack);

	TermekArAFA szilva("szilva", 0, 120, 2);
	leltar.hozzaadTermek(szilva);

	//termek hozzaadasa, ha betelt a leltar
	try {
		TermekArAFA narancs("narancs", 3, 20, 10);
		leltar.hozzaadTermek(narancs);
	}
	catch (const char* s) {
		cout << s << endl;
	}

	//legolcsobb termek lekerdezese es kiirasa
	
	cout << "Legolcsobb termek: " << endl;
	(leltar.legolcsobbTermek()).kiir();
	return 0;
}