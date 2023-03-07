/*Boda Norbert
511-es csoport*/

#include <iostream>
#include <cmath>

using namespace std;

double hatvany(int alap, int kitevo) {
	return pow(alap, kitevo);
}

double hatvany(int alap) {
	return pow(alap, alap);
}

int main() {
	cout << hatvany(2, 3) << " " << hatvany(2);
	return 0;
}