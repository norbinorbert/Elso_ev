/*Boda Norbert
511-es csoport*/

#include <iostream>

using namespace std;

int a(int b) {
	return b;
}

int a(int b, int c = 0) {
	return b + c;
}

int main() {
	cout << a(123) << " " << a(123, 3);
	return 0;
}

/*
Error (active)	E0308	more than one instance of overloaded function "a" matches the argument list
Error	C2668	'a': ambiguous call to overloaded function

1 parameteres meghivas eseten nem tudja eldonteni, hogy melyik fuggvenyt kell meghivja, 
mivel a masodik valtozat meghivhato 1 es 2 parameterre is
*/