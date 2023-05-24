#include "binaris_keresofa.h"
#include <iostream>

using namespace std;

binaris_keresofa::binaris_keresofa() {
	gyoker = NULL;
}

binaris_keresofa::~binaris_keresofa() {
	destroy(gyoker);
}

void binaris_keresofa::destroy(Elem* gyoker) {
	if (gyoker->bal != NULL) {
		destroy(gyoker->bal);
	}
	if (gyoker->jobb != NULL) {
		destroy(gyoker->jobb);
	}
	delete gyoker;
}

void binaris_keresofa::beszuras(double tmp){
	Elem* a = new Elem;
	a->adat = tmp;
	a->bal = NULL;
	a->jobb = NULL;
	beszuras(a, gyoker);
}

void binaris_keresofa::beszuras(Elem* a, Elem*& gyoker) {
	if (gyoker == NULL) {
		gyoker = a;
		return;
	}
	if (a->adat <= gyoker->adat) {
		beszuras(a, gyoker->bal);
	}
	else {
		beszuras(a, gyoker->jobb);
	}
}

void binaris_keresofa::torles(double tmp) {
	Elem* a = kereses(tmp, gyoker);
	if (a == NULL) {
		return;
	}
	if (a->bal == NULL && a->jobb == NULL) {
		delete a;
		return;
	}
	else {
		if (a->bal == NULL) {
			a = a->jobb;
			return;
		}
		if (a->jobb == NULL) {
			a = a->bal;
			return;
		}
		if (a->bal != NULL && a->jobb != NULL) {
			double adat = torles(a);
			a->adat = adat;
		}
	}
}

double binaris_keresofa::torles(Elem*& a) {
	if (a->bal != NULL) {
		torles(a->bal);
	}
	double tmp = a->adat;
	a = a->jobb;
	return tmp;
}

bool binaris_keresofa::kereses(double tmp) {
	Elem* a = kereses(tmp, gyoker);
	if (a == NULL) {
		return false;
	}
	return true;
}

binaris_keresofa::Elem*& binaris_keresofa::kereses(double tmp, Elem*& gyoker) {
	if (gyoker == NULL) {
		return gyoker;
	}
	if (gyoker->adat == tmp) {
		return gyoker;
	}
	if (tmp <= gyoker->adat) {
		return kereses(tmp, gyoker->bal);
	}
	else {
		return kereses(tmp, gyoker->jobb);
	}
}

void binaris_keresofa::kiir() {
	kiir(gyoker, " ");
}

void binaris_keresofa::kiir(Elem* gyoker, string space) {
	if (gyoker != NULL) {
		kiir(gyoker->jobb, space + "   ");
		cout << space << gyoker->adat << endl;
		kiir(gyoker->bal, space + "   ");
	}
}