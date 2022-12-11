#include <iostream>

using namespace std;

int main() {
	int n, c, g;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;
		int eredmeny = 0;
		for (int j = 0; j < c; j++) {
			cin >> g;
			eredmeny = eredmeny xor g;
		}
		cout << "Case #" << i+1 << ": " << eredmeny << endl;
	}
	return 0;
}