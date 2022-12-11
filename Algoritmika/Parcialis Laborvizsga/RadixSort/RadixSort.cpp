#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void beolvas(int& vector_hossza, vector<unsigned long long>& szamok) {
    cin >> vector_hossza;
    unsigned long long temp;
    for (int i = 0; i < vector_hossza; i++) {
        cin >> temp;
        szamok.push_back(temp);
    }
}

int max_szamjegy(vector<unsigned long long>& szamok) {
    int maximum = szamok[0];
    for (int i = 1; i < szamok.size(); i++) {
        if (maximum < szamok[i]) {
            maximum = szamok[i];
        }
    }
    string szj = to_string(maximum);
    return szj.size();
}

unsigned long long oszto_kiszamolas(int szamjegy_pozicio) {
    unsigned long long oszto = 1;
    for (int i = 0; i < szamjegy_pozicio; i++) {
        oszto *= 10;
    }
    return oszto;
}

void masol(vector<unsigned long long>& temp, vector<unsigned long long>& szamok) {
    for (int i = 0; i < szamok.size(); i++) {
        szamok[i] = temp[i];
    }
}

void count_sort(vector<unsigned long long>& szamok, int& szamjegy_pozicio) {
    unsigned long long oszto = oszto_kiszamolas(szamjegy_pozicio);
    vector<int> db(10);
    vector<unsigned long long> temp(szamok.size());
    for (int i = 0; i < szamok.size(); i++) {
        db[(szamok[i] / oszto) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        db[i] += db[i - 1];
    }
    for (int i = szamok.size()-1; i >=0; i--) {
        temp[db[(szamok[i] / oszto) % 10]-1] = szamok[i];
        db[(szamok[i] / oszto) % 10] --;
    }
    masol(temp, szamok);
}

void radix(vector<unsigned long long>& szamok, int szj) {
    for (int i = 0; i < szj; i++) {
        count_sort(szamok, i);
    }
}

void kiir(vector<unsigned long long>& rendezett) {
    for (int i = 0; i < rendezett.size(); i++) {
        cout << rendezett[i] << endl;
    }
}

int main() {
    int vector_hossza;
    vector<unsigned long long> szamok;
    beolvas(vector_hossza, szamok);

    int szj = max_szamjegy(szamok);
    
    radix(szamok, szj);

    kiir(szamok);
    return 0;
}