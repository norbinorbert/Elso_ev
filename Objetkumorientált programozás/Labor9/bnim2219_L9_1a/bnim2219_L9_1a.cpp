//Boda Norbert, 511
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class E {
protected:
	int e;
public:
	E(char*);
};

E::E(char* s) {
	e = 4;
	strcat(s, "E");
}

class F {
protected:
	int f;
public:
	F(char*);
};

F::F(char* s) {
	f = 5;
	strcat(s, "F");
}

class A : virtual public E, virtual public F {
protected:
	int a;
public:
	A(char*);
};

A::A(char* s):E(s), F(s) {
	a = 0;
	strcat(s, "A");
}

class B : virtual public E, virtual public F {
protected:
	int b;
public:
	B(char*);
};

B::B(char* s):E(s), F(s) {
	b = 1;
	strcat(s, "B");
}

class C : virtual public E, virtual public F {
protected:
	int c;
public:
	C(char*);
};

C::C(char* s) :E(s), F(s) {
	c = 2;
	strcat(s, "C");
}

class D : virtual public E, virtual public F {
protected:
	int d;
public:
	D(char*);
};

D::D(char* s) :E(s), F(s) {
	d = 3;
	strcat(s, "D");
}

class G : public E, public F {
protected:
	int g;
public:
	G(char*);
};

G::G(char* s):E(s), F(s) {
	g = 6;
	strcat(s, "G");
}

class H : public E, public F {
protected:
	int h;
public:
	H(char*);
};

H::H(char* s) :E(s), F(s) {
	h = 7;
	strcat(s, "H");
}

class I {
protected:
	int i;
public:
	I(char*);
};

I::I(char* s) {
	i = 8;
	strcat(s, "I");
}

class J : public A, public B, public C, public D, public G, public H, virtual public I {
protected:
	int j;
public:
	J(char*);
	void kiir();
};

J::J(char* s): A(s), B(s), C(s), D(s), A::E(s), B::F(s), G(s), H(s), I(s) {
	j = 9;
	strcat(s, "J");
}

void J::kiir() {
	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	cout << "c:" << c << endl;
	cout << "d:" << d << endl;
	cout << "e(A-bol):" << A::e << endl;
	cout << "f(B-bol):" << B::f << endl;
	cout << "g:" << g << endl;
	cout << "h:" << h << endl;
	cout << "i:" << i << endl;
}

int main() {
	char* sorrend = new char{};
	J asd(sorrend);
	
	asd.kiir();

	cout << sorrend << endl;
	return 0;
}