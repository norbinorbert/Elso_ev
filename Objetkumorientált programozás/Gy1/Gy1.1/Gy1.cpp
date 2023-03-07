/*Boda Norbert
511-es csoport*/

#include <iostream>
#include <ctime>

using namespace std;

#define N 10000

int& kihuz(int& fekete, int& feher) {
	if (rand() % 2 == 0) {
		return fekete;
	}
	else {
		return feher;
	}
}

int main() {
	int feher = 0, fekete = 0;
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		kihuz(fekete, feher)++;
	}
	cout << fekete << " " << feher;
	return 0;
}