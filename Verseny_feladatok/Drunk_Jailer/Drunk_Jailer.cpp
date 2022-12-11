#include <iostream>

using namespace std;

int main() {
	int first_number;
	cin >> first_number;
	for (int i = 0; i < first_number; i++) {
		int n, eredmeny = 0, szamlalo = 1;
		cin >> n;
		int v[101] = { 0 };
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (k % j == 0) {
					if (v[k] == 0) {
						v[k] = 1;
					}
					else {
						v[k] = 0;
					}
				}
			}
		}
		for (int j = 1; j <= n; j++) {
			if (v[j] == 1) {
				eredmeny++;
			}
		}
		cout << eredmeny << endl;
	}
	return 0;
}