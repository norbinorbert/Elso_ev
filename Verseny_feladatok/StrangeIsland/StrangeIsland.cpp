#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int t, n;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> n;
		vector<int> szamok(n);
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			szamok[j] = temp;
		}
		sort(szamok.begin(), szamok.end());
		bool found = false;
		int szamlalo = 1, j = 1, szam = szamok[0];
		while (!found && j < szamok.size()) {
			if (szamok[j] == szam) {
				szamlalo++;
				j++;
			}
			else if (szamok[j] <= szamlalo) {
				szam = szamok[j];
				szamlalo++;
				j++;
			}
			else if (j + 1 <= szam) {
				szamlalo++;
				szam = szamok[j];
				j++;
			}
			else if ((szamok[j] > szam && szamok[j] > szamlalo) || j+1 > szam) {
				found = true;
			}
		}
		cout << "Case " << i + 1 << ": " << szamlalo << endl;
	}
	return 0;
}