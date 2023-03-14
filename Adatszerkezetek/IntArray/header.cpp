#include "header.h"
#include <iostream>

IntArray* Create(int n) {
	IntArray* A = new IntArray;
	A->t = new int[n];
	A->meret = n;
	return A;
}

void Destroy(IntArray* A) {
	delete[]A->t;
	delete A;
}

int GetSize(IntArray* A) {
	return A->meret;
}

int GetElement(IntArray* A, int index) {
	return A->t[index];
}

void SetElement(IntArray* A, int index, int x) {
	A->t[index] = x;
}

void WriteElement(IntArray* A, int index) {
	std::cout << A->t[index] << std::endl;
}