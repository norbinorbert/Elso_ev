/*Boda Norbert
511-es csoport*/

#include <iostream>

using namespace std;

inline int maximum(int a, int b) {
	return (a > b) ? a : b;
}

inline int minimum(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	cout << maximum(1, 3) << " " << minimum(2, 3);
	return 0;
}