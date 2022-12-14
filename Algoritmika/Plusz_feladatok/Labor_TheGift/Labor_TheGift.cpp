#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(int& n, int& c, vector<int>& budget) {
    cin >> n >> c;
    budget.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> budget[i];
    }
}

vector<int> gift(int& n, int& c, vector<int>& budget) {
    vector<int> eredmeny;
    int osszeg = 0;
    for (int i = 0; i < n; i++) {
        osszeg += budget[i];
    }
    if (osszeg < c) {
        return eredmeny;
    }
    sort(budget.begin(), budget.end());
    int ar = c, atlag = ar / n, i = 0;
    while (ar > 0) {
        if (budget[i] <= atlag) {
            while (i < n && budget[i] <= atlag) {
                eredmeny.push_back(budget[i]);
                ar -= budget[i];
                i++;
            }
        }
        else {
            int darabszam = 0;
            while (ar - atlag * (n - i) != 0) {
                darabszam++;
                ar -= (atlag + 1);
                i++;
            }
            if (ar - atlag * (n - i) == 0) {
                while (i < n) {
                    eredmeny.push_back(atlag);
                    ar -= atlag;
                    i++;
                }
            }
            for (int i = 0; i < darabszam; i++) {
                eredmeny.push_back(atlag + 1);
            }
        }
        if (n > i) {
            atlag = ar / (n - i);
        }
    }
    return eredmeny;
}

void kiir(vector<int>& eredmeny) {
    if (eredmeny.size() == 0) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        for (int i = 0; i < eredmeny.size(); i++) {
            cout << eredmeny[i] << endl;
        }
    }
}

int main()
{
    int n, c;
    vector<int> budget;
    beolvas(n, c, budget);

    vector<int> eredmeny = gift(n, c, budget);

    kiir(eredmeny);
}