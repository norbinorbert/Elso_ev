#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct runner {
	string name;
	double first, second;
};

bool second_leg_sort(runner a, runner b) {
	return (a.second < b.second);
}

int main() {
	short n;
	cin >> n;
	vector<runner> runners(n);
	for (short i = 0; i < n; i++) {
		cin >> runners[i].name >> runners[i].first >> runners[i].second;
	}
	sort(runners.begin(), runners.end(), second_leg_sort);

	vector<string> names(4);
	double sum = INT_MAX;
	for (short i = 0; i < runners.size(); i++) {
		double temp_sum = runners[i].first;
		vector<string> temp_names(4, "");
		temp_names[0] = runners[i].name;
		short j = 0, index = 1;
		while (j < runners.size() && temp_names[3] == "") {
			if (j != i) {
				temp_sum += runners[j].second;
				temp_names[index] = runners[j].name;
				index++;
			}
			j++;
		}
		if (temp_sum < sum) {
			names = temp_names;
			sum = temp_sum;
		}
	}
	cout << sum << endl;
	for (short i = 0; i < names.size(); i++) {
		cout << names[i] << endl;
	}

	return 0;
}