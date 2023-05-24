#include "Binomialis_kupac.h"
#include <iostream>

using namespace std;

int main() {
	binomialis_kupac a, b;
	a.beszur(6);
	a.beszur(8);
	a.beszur(14);
	a.beszur(29);
	a.beszur(11);
	a.beszur(17);
	a.beszur(38);
	a.beszur(27);

	cout << a.minimum() << endl;
	cout << a.minimum() << " " << b.minimum() << endl;
	a.egyesit(b);
	for(int i=0;i<2;i++) {
		cout << a.minimum() << " ";
		a.torol_minimum();
	}
	return 0;
}