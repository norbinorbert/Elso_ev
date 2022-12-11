#include <iostream>
#include <vector>

using namespace std;

void general_fibonacci(int k, vector<int>& darab, unsigned long long f0, unsigned long long f1, int n) {
	if (f0 > k && f1 > k) {
		f0 = f0 % k;
		f1 = f1 % k;
	}
	unsigned long long f2 = f0 + f1;
	if (darab[f2 % k] == 0) {
		darab[f2 % k] = n;
	}
	else {
		cout << darab[f2 % k] << endl;
		return;
	}
	general_fibonacci(k, darab, f1, f2, n + 1);
}

int main() {
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		vector<int> darab(k);
		general_fibonacci(k, darab, 1, 1, 2);
	}
	return 0;
}