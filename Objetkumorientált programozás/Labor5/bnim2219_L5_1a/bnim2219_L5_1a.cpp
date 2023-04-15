//Boda Norbert, 511

#include <iostream>
#include <cmath>

using namespace std;

template<class T, int n>
class Matrix {
	T** matr;
public:
	Matrix();
	Matrix(T[n][n]);
	Matrix(const Matrix&);
	~Matrix();
	Matrix osszead(const Matrix&);
	double operator ~();
	void kiir();
};

template<class T, int n>
Matrix<T, n>::Matrix() {
	matr = new T * [n];
	for (int i = 0; i < n; i++) {
		matr[i] = new T[n]{ 0 };
	}
	for (int i = 0; i < n; i++) {
		matr[i][i] = 1;
	}
}

template<class T, int n>
Matrix<T, n>::Matrix(T A[n][n]) {
	matr = new T * [n];
	for (int i = 0; i < n; i++) {
		matr[i] = new T[n]{ 0 };
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matr[i][j] = A[i][j];
		}
	}
}

template<class T, int n>
Matrix<T, n>::Matrix(const Matrix& A) {
	matr = new T * [n];
	for (int i = 0; i < n; i++) {
		matr[i] = new T[n]{ 0 };
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matr[i][j] = A.matr[i][j];
		}
	}
}

template<class T, int n>
Matrix<T, n>::~Matrix() {
	for (int i = 0; i < n; i++) {
		delete[]matr[i];
	}
	delete[]matr;
}

template<class T, int n>
Matrix<T, n> Matrix<T, n>::osszead(const Matrix& A) {
	int temp[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = matr[i][j] + A.matr[i][j];
		}
	}
	Matrix B(temp);
	return B;
}

template<class T, int n>
double Matrix<T, n>::operator ~() {
	double osszeg = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			osszeg += matr[i][j] * matr[i][j];
		}
	}
	return sqrt(osszeg);
}

template<class T, int n>
void Matrix<T, n>::kiir() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	int temp[2][2] = { 1, 1,
					   1, 1 };
	Matrix<int, 2> A;
	cout << "A: " << endl;
	A.kiir();

	Matrix<int, 2> B(temp);
	cout << "B: " << endl;
	B.kiir();

	cout << "A + B: " << endl;
	A.osszead(B).kiir();

	cout << "~B = ";
	cout << ~B << endl << endl;

	cout << "C: " << endl;
	Matrix<int, 2>C(A);
	C.kiir();

	return 0;
}