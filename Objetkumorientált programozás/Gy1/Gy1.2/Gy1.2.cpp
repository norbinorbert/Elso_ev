/*Boda Norbert
511-es csoport*/

#include <iostream>
#include <cmath>

using namespace std;

double negyzet(double x) {
	return x * x;
}

double gyok(double x) {
	return sqrt(x);
}

double reciprok(double x) {
	return 1 / x;
}

void vegrehajt(double x, double(*fuggveny)(double)) {
	cout << fuggveny(x) << endl;
}

int main() {
	vegrehajt(12, negyzet);
	vegrehajt(12, gyok);
	vegrehajt(12, reciprok);
	return 0;
}

