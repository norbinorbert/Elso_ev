#include <iostream>

using namespace std;

int main() {
	short number=0;
	while (number != 42) {
		cin >> number;
		if (number != 42) {
			cout << number << endl;
		}
	}
	return 0;
}