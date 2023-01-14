#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> black = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
vector<pair<int, int>> moves = { {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };

void backtracking(int& answer, int temp_answer, vector<string>& v, vector<vector<bool>>& possible, int x, int y) {
	if (temp_answer > answer) {
		answer = temp_answer;
	}
	for (int i = 0; i < 4; i++) {
		if (x + moves[i].first >= 0 && x + moves[i].first < 10 && y + moves[i].second >= 0 && y + moves[i].second < 10 &&
			v[x + black[i].first][y + black[i].second] == 'B' && possible[x + moves[i].first][y + moves[i].second]) {
			possible[x + black[i].first][y + black[i].second] = true;
			v[x + black[i].first][y + black[i].second] = 'A';
			backtracking(answer, temp_answer + 1, v, possible, x + moves[i].first, y + moves[i].second);
			possible[x + black[i].first][y + black[i].second] = false;
			v[x + black[i].first][y + black[i].second] = 'B';
		}
	}
}

int main() {
	int t, answer;
	cin >> t;
	vector<string> v(10, "");
	for (int i = 0; i < t; i++) {
		answer = 0;
		vector<vector<bool>> possible(10, vector<bool>(10, true));
		for (int j = 0; j < 10; j++) {
			cin >> v[j];
		}
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				if (v[j][k] == 'W' || v[j][k] == 'B') {
					possible[j][k] = false;
				}
			}
		}
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				if (v[j][k] == 'W') {
					possible[j][k] = true;
					backtracking(answer, 0, v, possible, j, k);
					possible[j][k] = false;
				}
			}
		}
		cout << answer << endl;
	}
}
