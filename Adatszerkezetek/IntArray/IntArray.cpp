#include "header.h"
#include "header.cpp"
#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "n = ";
	cin >> n;
	IntArray* v = Create(n);
	int size = GetSize(v);
	for (int i = 0; i < size; i++) {
		int x;
		cout << "tomb[" << i << "] = ";
		cin >> x;
		SetElement(v, i, x);
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			int elso = GetElement(v, i), masodik = GetElement(v, j);
			if (elso > masodik) {
				SetElement(v, j, elso);
				SetElement(v, i, masodik);
			}
		}
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << "tomb[" << i << "] = ";
		WriteElement(v, i);
	}

	Destroy(v);
	return 0;
}