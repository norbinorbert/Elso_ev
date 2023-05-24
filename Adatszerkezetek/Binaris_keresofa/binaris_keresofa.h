#ifndef BINARIS_KERESOFA_H
#define BINARIS_KERESOFA_H
#include <string>
using namespace std;

class binaris_keresofa {
	struct Elem {
		double adat;
		Elem* bal;
		Elem* jobb;
	};

	Elem* gyoker;

	void destroy(Elem*);
	void beszuras(Elem*, Elem*&);
	double torles(Elem*&);
	Elem*& kereses(double, Elem*&);
	void kiir(Elem*, string);

public:
	binaris_keresofa();
	~binaris_keresofa();
	void beszuras(double);
	void torles(double);
	bool kereses(double);
	void kiir();
};

#endif // !BINARIS_KERESOFA_H
