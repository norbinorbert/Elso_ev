#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void beolvas(int& n, vector<long long>& szamok) {
    cin >> n;
    szamok.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> szamok[i];
    }
}

pair<long long, int> tombszakasz(vector<long long>& szamok, int bal, int jobb, long long& megoldas, int elozo_kozep) {
    if (bal == jobb) {
        megoldas = max(megoldas, szamok[bal]);
        return make_pair(szamok[bal], elozo_kozep);
    }
    int kozep = (bal + jobb) / 2;
    pair<long long, int> maximum1 = tombszakasz(szamok, bal, kozep, megoldas, kozep);
    megoldas = max(megoldas, maximum1.first);
    pair<long long, int> maximum2 = tombszakasz(szamok, kozep + 1, jobb, megoldas, kozep + 1);
    megoldas = max(megoldas, maximum2.first);
    if (maximum1.second == elozo_kozep && maximum1.first >= 0 && maximum2.first < 0) {
        return make_pair(maximum1.first, elozo_kozep);
    }
    if (maximum2.second == elozo_kozep + 1 && maximum2.first >= 0 && maximum1.first < 0) {
        return make_pair(maximum2.first, elozo_kozep + 1);
    }
    if (maximum1.second == maximum2.second - 1) {
        long long osszeg = maximum1.first + maximum2.first;
        megoldas = max(megoldas, osszeg);
        if (osszeg >= 0) {
            if (jobb <= elozo_kozep) {
                return make_pair(osszeg, jobb);
            }
            if (bal >= elozo_kozep) {
                return make_pair(osszeg, maximum1.second);
            }
        }
    }
    if (maximum1.first > maximum2.first) {
        return maximum1;
    }
    if(maximum2.first > maximum1.first){
        return maximum2;
    }
    if (maximum1.first == maximum2.first) {
        if (jobb <= elozo_kozep) {
            return maximum2;
        }
        if (bal >= elozo_kozep) {
            return maximum1;
        }
    }

}

void kiir(long long& megoldas) {
    cout << megoldas;
}

int main() {
    int n;
    vector<long long> szamok;
    beolvas(n, szamok);

    long long megoldas = LLONG_MIN;
    tombszakasz(szamok, 0, n - 1, megoldas, n);

    kiir(megoldas);
    return 0;
}