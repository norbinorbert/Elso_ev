#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007

int main() {
	int n;
	cin >> n;
	vector<unsigned long long> fakt(2 * n + 1);
	fakt[0] = 1;
	for (unsigned long long i = 1; i <= 2 * n; i++) {
		fakt[i] = (fakt[i - 1] * i) % MOD;
	}
	unsigned long long szamlalo = fakt[2 * n];
	unsigned long long nevezo = (fakt[n] * fakt[n + 1]) % MOD;
	for (unsigned long long i = 1; i < MOD; i++) {
		if ((nevezo * i) % MOD == 1) {
			nevezo = i;
			break;
		}
	}
	cout << (szamlalo * nevezo) % MOD;
	return 0;
}