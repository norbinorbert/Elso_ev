//Boda Norbert, 511

#include <iostream>

using namespace std;

template<class T>
void rendez(T* tomb, int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (tomb[i] > tomb[j]) {
				swap(tomb[i], tomb[j]);
			}
		}
	}
}

template<class T>
void kiir(T* tomb, int n) {
	for (int i = 0; i < n; i++) {
		cout << tomb[i] << " ";
	}
	cout << endl;
}

int main() {
	int a[5] = { 1, 5, 3, 7, 2 };
	double b[6] = { 0.2, 2.1, -1.2, -10, 4.5, 100 };

	rendez(a, 5);
	rendez(b, 6);

	cout << "a: ";
	kiir(a, 5);
	cout << "b: ";
	kiir(b, 6);
}