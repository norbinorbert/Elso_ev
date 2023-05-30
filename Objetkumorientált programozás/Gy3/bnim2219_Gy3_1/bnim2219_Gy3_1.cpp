//Boda Norbert, 511

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void torol_elejerol(string&);
void torol_vegerol(string&);
void kisbetusit(string&);
bool csokkeno(const pair<string, int>, const pair<string, int>);

int main() {
	map<string, int> statisztika;
	ifstream fin("Dickens.txt");
	string szo;
	while (fin >> szo) {
		if (szo.size() > 0) {
			torol_elejerol(szo);
		}
		if (szo.size() > 0) {
			torol_vegerol(szo);
		}
		if (szo.size() > 0) {
			kisbetusit(szo);
			statisztika[szo]++;
		}
	}
	
	vector<pair<string, int>> elemek;
	for (pair<string, int> i : statisztika) {
		elemek.push_back(i);
	}
	sort(elemek.begin(), elemek.end(), csokkeno);
	
	for (pair<string, int> i : elemek) {
		cout << i.first << " " << i.second << endl;
	}
	return 0;
}

void torol_elejerol(string& szo) {
	char elso = szo[0];
	while ((elso < 'A') || (elso > 'Z' && elso < 'a') || elso > 'z') {
		szo.erase(0, 1);
		if (szo.size() == 0) {
			break;
		}
		elso = szo[0];
	}
}

void torol_vegerol(string& szo) {
	char utolso = szo[szo.size() - 1];
	while ((utolso < 'A') || (utolso > 'Z' && utolso < 'a') || utolso > 'z') {
		szo.pop_back();
		if (szo.size() == 0) {
			break;
		}
		utolso = szo[szo.size() - 1];
	}
}

void kisbetusit(string& szo) {
	for (int i = 0; i < szo.size(); i++) {
		szo[i] = tolower(szo[i]);
	}
}

bool csokkeno(const pair<string, int> a, const pair<string, int> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second > b.second;
}