//Boda Norbert, 511

#include <iostream>

using namespace std;

class Ido {
	int ora, perc, masodperc;
public:
	Ido(int, int, int);
	Ido(int);
	Ido& operator +=(const Ido&);
	Ido& operator -=(const Ido&);
	void kiir();
};

Ido::Ido(int h, int m, int s) {
	ora = h;
	perc = m;
	masodperc = s;
}

Ido::Ido(int szam) {
	ora = perc = masodperc = 0;
	if (szam / 3600 > 0) {
		ora = szam / 3600;
	}
	szam %= 3600;
	if (szam / 60 > 0) {
		perc = szam / 60;
	}
	szam %= 60;
	masodperc = szam;
}

Ido& Ido::operator +=(const Ido& i) {
	masodperc += i.masodperc;
	int tmp = 0;
	if (masodperc >= 60) {
		masodperc -= 60;
		tmp = 1;
	}
	perc += i.perc + tmp;
	tmp = 0;
	if (perc >= 60) {
		perc -= 60;
		tmp = 1;
	}
	ora += i.ora + tmp;
	return (*this);
}

Ido& Ido::operator -=(const Ido& i) {
	if (masodperc < i.masodperc) {
		masodperc += 60;
		if (perc > 0) {
			perc -= 1;
		}
		else {
			perc = 59;
			ora -= 1;
		}
	}
	masodperc -= i.masodperc;
	if (perc < i.perc) {
		perc += 60;
		ora -= 1;
	}
	perc -= i.perc;
	ora -= i.ora;
	return (*this);
}

void Ido::kiir() {
	cout << ora << ":";
	if (perc < 10) {
		cout << "0";
	}
	cout << perc << ":";
	if (masodperc < 10) {
		cout << "0";
	}
	cout << masodperc << endl;
}

int main() {
	Ido a(0, 1, 59);

	a += 1;      // előbb 1-ről Ido-re konvertál 

	a.kiir();

	a -= 1;      // előbb 1-ről Ido-re konvertál

	a.kiir();

	Ido b(9605);

	b.kiir();    // 2 óra 40 perc 5 másodperc

	return 0;
}