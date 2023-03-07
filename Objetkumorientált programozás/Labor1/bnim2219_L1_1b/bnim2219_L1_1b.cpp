/*Boda Norbert, 511-es csoport*/

#include <iostream>

using namespace std;

void spiralSorrend(const int* matrix, int n, int* spiral);

int main() {
	int n;
	cin >> n;
	int* matrix = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> matrix[i];
	}
	int* spiral = new int[n];
	spiralSorrend(matrix, n, spiral);

	for (int i = 0; i < n; i++) {
		cout << spiral[i] << " ";
	}
	return 0;
}

void spiralSorrend(const int* matrix, int n, int* spiral) {
	int spiral_index = 0, matrix_index = 0, gyok = sqrt(n), iteraciok = 0, lepesek = gyok;
	string irany = "jobb";
	while (lepesek > 0) {
		if (irany == "jobb") {
			for (int i = 0; i < lepesek - 1; i++) {
				spiral[spiral_index] = matrix[matrix_index];
				spiral_index++;
				matrix_index++;
			}
			spiral[spiral_index] = matrix[matrix_index];
			spiral_index++;
			matrix_index += gyok;
			irany = "le";
		}
		else if (irany == "le") {
			for (int i = 0; i < lepesek - 1; i++) {
				spiral[spiral_index] = matrix[matrix_index];
				spiral_index++;
				matrix_index += gyok;
			}
			spiral[spiral_index] = matrix[matrix_index];
			spiral_index++;
			matrix_index--;
			irany = "bal";
		}
		else if (irany == "bal") {
			for (int i = 0; i < lepesek - 1; i++) {
				spiral[spiral_index] = matrix[matrix_index];
				spiral_index++;
				matrix_index--;
			}
			spiral[spiral_index] = matrix[matrix_index];
			spiral_index++;
			matrix_index -= gyok;
			irany = "fel";
		}
		else if (irany == "fel") {
			for (int i = 0; i < lepesek - 1; i++) {
				spiral[spiral_index] = matrix[matrix_index];
				spiral_index++;
				matrix_index -= gyok;
			}
			spiral[spiral_index] = matrix[matrix_index];
			spiral_index++;
			matrix_index++;
			irany = "jobb";
		}
		iteraciok++;
		if (iteraciok == 2) {
			lepesek--;
			iteraciok = 0;
		}
		if (iteraciok == 1 && lepesek == gyok) {
			lepesek--;
			iteraciok = 0;
		}
	}
}