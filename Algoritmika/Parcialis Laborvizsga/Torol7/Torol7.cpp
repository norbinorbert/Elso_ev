#include <iostream>
#include <vector>

using namespace std;

void beolvas(int& vector_hossza, vector<long long>& szamok) {
	cin >> vector_hossza;
	long long temp;
	for (int i = 0; i < vector_hossza; i++) {
		cin >> temp;
		szamok.push_back(temp);
	}
}

void torol_het(vector<long long>& szamok) {
	int i = 0;
	while (i < szamok.size()) {
		if (szamok[i] % 7 == 0) {
			szamok[i] = szamok[szamok.size() - 1];
			szamok.pop_back();
		}
		else {
			i++;
		}
	}
}

void kiir(vector<long long>& szamok) {
	cout << szamok.size() << endl;
	for (int i = 0; i < szamok.size(); i++) {
		cout << szamok[i] << endl;

	}
}

int main() {
	int vector_hossza;
	vector<long long> szamok;
	beolvas(vector_hossza, szamok);

	torol_het(szamok);

	kiir(szamok);
	return 0;
}