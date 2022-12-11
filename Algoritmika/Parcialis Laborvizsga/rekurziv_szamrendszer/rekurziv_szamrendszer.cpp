#include <iostream>

using namespace std;

void beolvas(unsigned long long& szam, short& szamrendszer) {
    cin >> szam >> szamrendszer;
}

unsigned long long szamrendszer_atalakitas(unsigned long long szam, short szamrendszer, unsigned long long hatvany) {
    if (szam == 0) {
        return 0;
    }
    if (szamrendszer == 10) {
        return szam;
    }
    return szamrendszer_atalakitas(szam / 10, szamrendszer, hatvany * szamrendszer) + hatvany * (szam % 10);
}

void kiir(unsigned long long atalakitott_szam) {
    cout << atalakitott_szam;
}

int main() {
    unsigned long long szam, hatvany = 1;
    short szamrendszer;
    beolvas(szam, szamrendszer);

    unsigned long long atalakitott_szam = szamrendszer_atalakitas(szam, szamrendszer, hatvany);

    kiir(atalakitott_szam);
    return 0;
}