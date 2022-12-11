#include <iostream>
#include <vector>

using namespace std;


int main() {
	long long n, m;
	vector<long long> height;
	cin >> n >> m;
	long long temp_szam, max_height=0;
	for (long long i = 0; i < n; i++) {
		cin >> temp_szam;
		if (max_height < temp_szam) {
			max_height = temp_szam;
		}
		height.push_back(temp_szam);
	}
	int eredmeny = 0, fenti_osszeg = 0, lenti_osszeg = 0;
	long long lenti = 0, fenti = max_height-1;
	while(lenti<fenti) {
		long long temp_osszeg = 0, kozep = (lenti + fenti) / 2, seged_temp_osszeg = 0;;
		for (long long j = 0; j < n; j++) {
			if (height[j] > kozep) {
				temp_osszeg += height[j] - kozep;
				seged_temp_osszeg += height[j] - kozep - 1;
			}
			if (fenti - lenti == 1) {
				fenti_osszeg += height[fenti] - fenti;
				lenti_osszeg += height[lenti] - lenti;
			}
		}
		if (temp_osszeg > m) {
			lenti = kozep;
		}
		if (temp_osszeg < m) {
			fenti = kozep;
		}
		if (temp_osszeg == m) {
			eredmeny = kozep;
			lenti = fenti;
		}
		if (fenti - lenti == 1) {
			if (fenti_osszeg < m) {
				eredmeny = lenti;
				fenti = lenti;
			}
			if (lenti_osszeg > m) {
				eredmeny = lenti;
				fenti = lenti;
			}
		}
	}
	cout << eredmeny;
	return 0;
}