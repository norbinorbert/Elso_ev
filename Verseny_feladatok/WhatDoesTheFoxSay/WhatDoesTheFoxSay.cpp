#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

int main() {
	int test_cases;
	cin >> test_cases; cin.ignore();
	for (int i = 0; i < test_cases; i++) {
		string szoveg, temp_s, fox_say;
		vector<string> recording, hangok;	
		getline(cin, szoveg);
		stringstream olvas(szoveg);
		while (olvas >> temp_s) {
			recording.push_back(temp_s);
		}
		getline(cin, fox_say);
		while (fox_say != "what does the fox say?") {
			stringstream olvas(fox_say);
			bool goes = false;
			while (olvas >> temp_s) {
				if (temp_s == "goes") {
					goes = true;
				}
				if (temp_s != "goes" && goes) {
					hangok.push_back(temp_s);
				}
			}
			getline(cin, fox_say);
		}
		for (int j = 0; j < hangok.size(); j++) {
			for (int k = 0; k < recording.size(); k++) {
				if (hangok[j] == recording[k]) {
					recording[k] = " ";
				}
			}
		}
		for (int j = 0; j < recording.size(); j++) {
			if (recording[j] != " ") {
				cout << recording[j] << " ";
			}
		}
		cout << endl;
	}
	return 0;
}