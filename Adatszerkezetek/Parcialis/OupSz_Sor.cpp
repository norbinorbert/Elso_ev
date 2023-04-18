#include <iostream>
#include "OupSz_Sor.h"
#include <ctime>

using namespace std;

OupSz_Sor::OupSz_Sor(int max_meret) {
	srand(time(NULL));
	meret = max_meret;
	utolso_elem = -1;
	tomb = new int[max_meret] {0};
}

OupSz_Sor::~OupSz_Sor() {
	delete[]tomb;
}

bool OupSz_Sor::InsertElement(int elem) {
	if (utolso_elem == meret - 1) {
		return false;
	}
	tomb[++utolso_elem] = elem;
	return true;
}

int OupSz_Sor::PopElement() {
	if (utolso_elem == -1) {
		return 0;
	}
	if (utolso_elem == 0) {
		int tmp = tomb[utolso_elem];
		tomb[utolso_elem] = 0;
		utolso_elem--;
		return tmp;
	}
	if (utolso_elem == 1) {
		int index = rand() % 2;
		int tmp = tomb[index];
		if (index == 0) {
			tomb[0] = tomb[1];
		}
		tomb[1] = 0;
		utolso_elem--;
		return tmp;
	}
	if (utolso_elem >= 2) {
		int index = rand() % 3;
		int tmp = tomb[index];
		for (int i = index; i < meret - 1; i++) {
			tomb[i] = tomb[i + 1];
		}
		utolso_elem--;
		return tmp;
	}
}

void OupSz_Sor::PrintList() {
	for (int i = 0; i <= utolso_elem; i++) {
		cout << tomb[i] << " ";
	}
	cout << endl;
}