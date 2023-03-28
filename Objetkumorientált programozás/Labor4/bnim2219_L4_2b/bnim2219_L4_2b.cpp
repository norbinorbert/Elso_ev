//Boda Norbert, 511

#include <iostream>

using namespace std;

bool kulonbozo_elojel(double a, double b) {
	return (a > 0 && b > 0 && a != 0 && b != 0);
}

pair<double, double> metszespont(pair<double, double> p1, pair<double, double> p2) {
	if (kulonbozo_elojel(p1.second, p2.second)) {
		throw "Hiba";
	}
	if (p1.first == p2.first) {
		return { p1.first, 0 };
	}
	double m = (p2.second - p1.second) / (p2.first - p1.first);
	double x = (m * p1.first - p1.second) / m;
	return { x, 0 };
}

int main() {
	try {
		pair<double, double> pont = metszespont({ 1, -1 }, { 3, 1 });
		cout << pont.first << " " << pont.second << endl;
		pont = metszespont({ 1, 0 }, { 2, 3 });
		cout << pont.first << " " << pont.second << endl;
		pont = metszespont({ 1, 2 }, { 1, 3 });
		cout << pont.first << " " << pont.second << endl;
	}
	catch (const char*) {
		cout << "Nem metszik egymast";
	}
	return 0;
}