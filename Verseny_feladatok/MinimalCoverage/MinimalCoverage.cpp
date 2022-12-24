#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int m;
	cin >> m;
	int first, second;
	vector<pair<int, int>> segments, megoldas;
	cin >> first >> second;
	while (first != 0 || second != 0) {
		segments.push_back({ first, second });
		cin >> first >> second;
	}
	sort(segments.begin(), segments.end());
	int i = 0, leghosszabb_index = 0, jelenlegi_kezdet = 0;
	while (i < segments.size() && segments[i].second <= jelenlegi_kezdet) {
		i++;
	}
	if (i < segments.size()) {
		leghosszabb_index = i;
	}
	while (i < segments.size()) {
		if (jelenlegi_kezdet >= m) {
			break;
		}
		while (i < segments.size() && segments[i].first <= jelenlegi_kezdet) {
			if ((segments[i].second - jelenlegi_kezdet) > (segments[leghosszabb_index].second - jelenlegi_kezdet)) {
				leghosszabb_index = i;
			}
			i++;
		}
		megoldas.push_back(segments[leghosszabb_index]);
		jelenlegi_kezdet = segments[leghosszabb_index].second;
		leghosszabb_index = i;
		if (jelenlegi_kezdet >= m) {
			break;
		}
	}

	bool lehetseges = true;
	jelenlegi_kezdet = 0;
	for (int i = 0; i < megoldas.size(); i++) {
		if (megoldas[i].first <= jelenlegi_kezdet && megoldas[i].second >= jelenlegi_kezdet) {
			jelenlegi_kezdet = megoldas[i].second;
		}
		else {
			lehetseges = false;
		}
	}
	if (jelenlegi_kezdet < m) {
		lehetseges = false;
	}

	if (!lehetseges) {
		cout << "No solution";
	}
	else {
		cout << megoldas.size() << endl;
		for (int i = 0; i < megoldas.size(); i++) {
			cout << megoldas[i].first << " " << megoldas[i].second << endl;
		}
	}
	return 0;
}