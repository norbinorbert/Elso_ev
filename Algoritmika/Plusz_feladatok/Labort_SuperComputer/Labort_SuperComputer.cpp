#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(int& n, vector<pair<int, int>>& napok) {
    cin >> n;
    napok.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> napok[i].first;
        cin >> napok[i].second;
        napok[i].second += (napok[i].first - 1);
    }
}

bool novekvo(pair<int, int>& a, pair<int, int>& b) {
    return (a.second < b.second);
}

int SuperComputer(int& n, vector<pair<int, int>>& napok) {
    sort(napok.begin(), napok.end(), novekvo);
    int megoldas = 0;
    pair<int, int> jelenlegi_hasznalat = { -1, -1 };

    for (int i = 0; i < n; i++) {
        if (napok[i].first > jelenlegi_hasznalat.second) {
            jelenlegi_hasznalat = napok[i];
            megoldas++;
        }
    }

    return megoldas;
}

int main()
{
    int n;
    vector<pair<int, int>> napok;
    beolvas(n, napok);

    int megoldas = SuperComputer(n, napok);

    cout << megoldas << endl;
}