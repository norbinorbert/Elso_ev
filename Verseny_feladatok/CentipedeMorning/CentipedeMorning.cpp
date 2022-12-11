#include <iostream>

using namespace std;

int main() {
	int left, right, seconds = 0;
	cin >> left >> right;
	if (left > right) {
		cout << 2 * left + 39;
	}
	else {
		cout << 2 * right + 40;
	}
	return 0;
}