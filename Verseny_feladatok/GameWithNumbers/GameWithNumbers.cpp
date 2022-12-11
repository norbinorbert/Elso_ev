#include <iostream>

using namespace std;

int main() {
	int szam;
	cin >> szam;
	if (szam % 10 == 0) {
		cout << 2;
	}
	else {
		cout << 1 << endl << szam % 10;
	}
	return 0;
}