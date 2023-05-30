#ifndef HASHLISH_H
#define HASHLIST_H

#include "lista.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashList {
	vector<Lista> t;
	
	int HasitoFuggveny(string);

public:
	HashList(int);
	void beszur(string, double = 0);
	void kiir();
	double& operator[](string);
};


#endif // !HASHLISH_H
