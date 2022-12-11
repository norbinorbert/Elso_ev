#include <ctime>
#include <iostream>
#include <climits>

#define ISMETLESEK_SZAMA 10000000

using namespace std;

int Megold2(int a[], int n)
{
	int sum[10];
	sum[0] = a[0];
	for (int i = 1; i < n; ++i) {
		sum[i] = sum[i - 1] + a[i];
	}
	int max_osszeg = 0, temp_osszeg=0, min_sum = INT_MAX, max_sum = INT_MIN, min_index=0, max_index=0;
	for (int i = 0; i < n; ++i) {
		if (sum[i] < min_sum) {
			min_sum = sum[i];
			min_index = i;
		}
		if (sum[i] >= min_sum && i >= min_index) {
			if (sum[i] > max_sum) {
				max_sum = sum[i];
			}
			temp_osszeg = sum[i] - min_sum;
			if (temp_osszeg > max_osszeg) {
				max_osszeg = temp_osszeg;
			}
		}
	}
	if ((min_sum > 0 || min_sum==max_sum || min_index > max_index) && max_sum > max_osszeg) {
		max_osszeg = max_sum;
	}
	return max_osszeg;
}

int main()
{
	int tomb[10] = { 1, 2, -6, 3, 4, 5, -2, 10, -5, -6 };
	int meret = 10;

	clock_t start = clock();
	int megoldas;
	for (int ismetles = 0; ismetles < ISMETLESEK_SZAMA; ++ismetles)
	{
		megoldas = Megold2(tomb, meret);
	}
	cout << "Megoldas: " << megoldas << endl;
	cout << double(clock() - start) / CLOCKS_PER_SEC << endl;
	return 0;
}