#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> billiards(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> billiards[i];
	}
	stack<int> stack;
	int j = 1;
	for (int i = 1; i <= n; i++) {
		stack.push(i);
		while (j < billiards.size() && !stack.empty() && billiards[j] == stack.top()) {
			stack.pop();
			j++;
		}
	}
	if (!stack.empty()) {
		cout << "Cheater";
	}
	else {
		cout << "Not a proof";
	}
	return 0;
}