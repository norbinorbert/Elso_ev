#include "HashList.h"
#include <iostream>

using namespace std;

int main() {
	HashList a(11);

	a.beszur("Szia", 12);
	a.beszur("sad", 11);
	a.beszur("asd");

	a.kiir();
	cout << a["Szia"] << endl;
	a["Szia"] = 13;
	cout << a["Szia"] << endl;

	cout << a["uj_string"] << endl;

	a["ujabb_string"] = 9;
	cout << a["ujabb_string"] << endl;
	return 0;
}
