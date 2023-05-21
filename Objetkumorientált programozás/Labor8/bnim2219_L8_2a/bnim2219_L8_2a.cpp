//Boda Norbert, 511

#include <iostream>

using namespace std;

class Tomeg_g;
class Tomeg_d;

class Tomeg_g {
	int kg, dkg, g;
	double maradek;
public:
	Tomeg_g(int, int, int);
	Tomeg_g(const Tomeg_d&);
	void kiir() const;
};

class Tomeg_d {
	int font, uncia, dram;
public:
	Tomeg_d(int, int, int);
	int get_font() const;
	int get_uncia() const;
	int get_dram() const;
	operator Tomeg_g();
};

Tomeg_g::Tomeg_g(int kg, int dkg, int g) {
	this->kg = kg;
	this->dkg = dkg;
	this->g = g;
	this->maradek = 0;
}

Tomeg_g::Tomeg_g(const Tomeg_d& a) {
	kg = dkg = g = maradek = 0;
	double osszeg = 0;
	osszeg += 453.592 * a.get_font() + 28.349 * a.get_uncia() + 1.77 * a.get_dram();
	int tmp_kg = osszeg;
	tmp_kg /= 1000;
	kg = tmp_kg;
	osszeg -= kg * 1000;

	int tmp_dkg = osszeg;
	tmp_dkg /= 10;
	dkg = tmp_dkg;
	osszeg -= dkg * 10;
	
	int tmp_g = osszeg;
	g = tmp_g;
	osszeg -= g;

	maradek = osszeg;

}

void Tomeg_g::kiir() const {
	cout << kg << " " << dkg << " " << g << " " << maradek << endl;
}

Tomeg_d::Tomeg_d(int font, int uncia, int dram) {
	this->font = font;
	this->uncia = uncia;
	this->dram = dram;
}

int Tomeg_d::get_font() const{
	return font;
}

int Tomeg_d::get_uncia() const{
	return uncia;
}

int Tomeg_d::get_dram() const{
	return dram;
}

Tomeg_d::operator Tomeg_g() {
	return Tomeg_g(*this);
}

int main() {
	Tomeg_d a(1, 0, 0);
	((Tomeg_g)a).kiir();
	
	Tomeg_d b(0, 1, 0);
	Tomeg_g c(b);
	c.kiir();
	
	Tomeg_d d(0, 0, 1);
	((Tomeg_g)d).kiir();
	return 0;
}