#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int coins;
		cin >> coins;
		if (coins <= 2) {
			int temp;
			for (int j = 0; j < coins; j++) {
				cin >> temp;
			}
			cout << "Case #" << i + 1 << ": " << coins << endl;
		}
		else{
			vector<unsigned int> coin(coins);
			unsigned long long osszeg = 1, szamlalo = 2;
			for (int j = 0; j < coins; j++) {
				cin >> coin[j];
			}
			sort(coin.begin(), coin.end());
			for (int j = 1; j < coins - 1; j++) {
				if (osszeg + coin[j] < coin[j + 1]) {
					osszeg += coin[j];
					szamlalo++;
				}
			}
			cout << "Case #" << i + 1 << ": " << szamlalo << endl;
		}
	}
	return 0;
}