#include <iostream>
#include <ctime>

using namespace std;

template <class T>
class Rendezes {
protected:
    virtual bool kisebb(T a, T b) = 0;
    virtual void csere(T &a, T &b) = 0;
public:
    virtual void rendez(T *tomb, int n) = 0;
};

class Stat {
private:
    unsigned int ido, nHasonlit, nCsere;
    clock_t c;

protected:
    void kezd();
    void vege();
    void init();
    void incHasonlit();
    void incCsere();

public:
    Stat();
    unsigned int getIdo();
    unsigned int getHasonlit();
    unsigned int getCsere();
};

void Stat::kezd() {
    c = clock();
}

void Stat::vege() {
    clock_t tmp = clock();
    ido = (c - tmp) / CLOCKS_PER_SEC * 1000;
    c = tmp;
}

void Stat::init() {
    ido = nHasonlit = nCsere = 0;
}

void Stat::incHasonlit() {
    nHasonlit++;
}

void Stat::incCsere() {
    nCsere++;
}

Stat::Stat() {
    init();
    kezd();
}

unsigned int Stat::getIdo() {
    ido = (clock() - c) / CLOCKS_PER_SEC * 1000;
    return ido;
}

unsigned int Stat::getHasonlit() {
    return nHasonlit;
}

unsigned int Stat::getCsere() {
    return nCsere;
}

template <class T>
class BuborekosRendezes : public Rendezes<T> {
protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

template<class T>
bool BuborekosRendezes<T>::kisebb(T a, T b) {
    return (a < b);
}

template<class T>
void BuborekosRendezes<T>::csere(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
void BuborekosRendezes<T>::rendez(T* tomb, int n) {
    int temp_pozicio = n;
    bool rendezett = true;
    do {
        int utolso_pozicio = temp_pozicio - 1;
        rendezett = true;
        for (int i = 0; i < utolso_pozicio; i++) {
            if (kisebb(tomb[i+1], tomb[i])) {
                csere(tomb[i], tomb[i + 1]);
                rendezett = false;
                temp_pozicio = i + 1;
            }
        }
    } while (!rendezett);
}

template <class T>
class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat {
protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);
};

template<class T>
bool BuborekosRendezesT<T>::kisebb(T a, T b) {
    incHasonlit();
    return BuborekosRendezes<T>::kisebb(a, b);
}

template<class T>
void BuborekosRendezesT<T>::csere(T& a, T& b) {
    incCsere();
    BuborekosRendezes<T>::csere(a, b);
}

template<class T>
void BuborekosRendezesT<T>::rendez(T* tomb, int n) {
    BuborekosRendezes<T>::rendez(tomb, n);
}

template <class T>
class QuickSort : public Rendezes<T> {
private:
    void qsort(T* a, int bal, int jobb);
    int particional(T *a, int bal, int jobb);

protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);

};

template<class T>
void QuickSort<T>::qsort(T* a, int bal, int jobb) {
    if (bal < jobb) {
        int m = particional(a, bal, jobb);
        qsort(a, m + 1, jobb);
        qsort(a, bal, m);
        
    }
}

template<class T>
int QuickSort<T>::particional(T* a, int bal, int jobb) {
    T strazsa = a[jobb];
    int i = bal - 1;
    for (int j = bal; j <= jobb - 1; j++) {
        if (kisebb(a[j], strazsa)) {
            i++;
            csere(a[i], a[j]);
        }
    }
    csere(a[i + 1], a[jobb]);
    return i;
}

template<class T>
bool QuickSort<T>::kisebb(T a, T b) {
    return (a < b);
}

template<class T>
void QuickSort<T>::csere(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
void QuickSort<T>::rendez(T* tomb, int n) {
    qsort(tomb, 0, n - 1);
}

template <class T>
class QuickSortT : public QuickSort<T>, public Stat {

protected:
    bool kisebb(T a, T b);
    void csere(T &a, T &b);

public:
    void rendez(T *tomb, int n);

};

template<class T>
bool QuickSortT<T>::kisebb(T a, T b) {
    incHasonlit();
    return Quicksort<T>::kisebb(a, b);
}

template<class T>
void QuickSortT<T>::csere(T& a, T& b) {
    incCsere();
    QuickSort<T>::csere(a, b);
}

template<class T>
void QuickSortT<T>::rendez(T* tomb, int n) {
    QuickSort<T>::qsort(tomb, 0, n - 1);
}

int main() {
    int t1[1000], t2[1000];
    for (int i = 0; i < 1000; i++) {
        t1[i] = 1000 - i;
        t2[i] = 1000 - i;
    }
    Rendezes<int>* r[] = { new BuborekosRendezesT<int>, new QuickSortT<int> };
    r[0]->rendez(t1, 1000);
    cout << "Buborekos rendezes:" << endl;
    cout << "===================" << endl;
    cout << "Osszehasonlitasok szama: " << (dynamic_cast<BuborekosRendezesT<int>*>(r[0]))->getHasonlit() << endl;
    cout << "Cserek szama: " << (dynamic_cast<BuborekosRendezesT<int>*>(r[0]))->getCsere() << endl;
    cout << "Ido (ms): " << (dynamic_cast<BuborekosRendezesT<int>*>(r[0]))->getIdo() << endl;
    cout << endl;
    cout << "QuickSort:" << endl;
    cout << "==========" << endl;
    r[1]->rendez(t2, 1000);
    cout << "Osszehasonlitasok szama: " << (dynamic_cast<QuickSortT<int>*>(r[1]))->getHasonlit() << endl;
    cout << "Cserek szama: " << (dynamic_cast<QuickSortT<int>*>(r[1]))->getCsere() << endl;
    cout << "Ido (ms): " << (dynamic_cast<QuickSortT<int>*>(r[1]))->getIdo() << endl;
}