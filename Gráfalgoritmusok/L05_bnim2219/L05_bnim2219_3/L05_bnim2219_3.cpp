//Boda Norbert, 511

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>

using namespace std;

struct csomopont {
    int ido;
    int nev;
    int t0min;
    int t1min;
    int t0max;
    int t1max;
    bool kritikus;
};

struct el {
    int u, v;
};

void beolvas(int&, vector<csomopont>&, vector<el>&);
vector<pair<int, int>> DFS(vector<csomopont>&, vector<el>&);
void DFS_visit(vector<el>&, int, vector<pair<int, int>>&, int&, vector<csomopont>&);
void topologiai_rendezes(vector<pair<int, int>>&);
bool csokkeno(pair<int, int>, pair<int, int>);
void kritikus_ut(int, vector<csomopont>&, vector<el>&, vector<pair<int, int>>&);
void kiir(vector<csomopont>&);

int main() {
    int csomopontok_szama;
    vector<csomopont> csp;
    vector<el> elek;
    beolvas(csomopontok_szama, csp, elek);

    vector<pair<int, int>> topo = DFS(csp, elek);

    kritikus_ut(csomopontok_szama, csp, elek, topo);

    kiir(csp);

    return 0;
}

void beolvas(int& csomopontok_szama, vector<csomopont>& csp, vector<el>& elek) {
    ifstream fin("3_be.txt");
    fin >> csomopontok_szama;
    csp.resize(csomopontok_szama + 1, {0, 0, 0, 0, INT_MAX - 1, INT_MAX - 1, false });
    for (int i = 1; i <= csomopontok_szama; i++) {
        fin >> csp[i].ido;
        csp[i].nev = i;
    }
    int u, v;
    while (fin >> u >> v) {
        elek.push_back({ u,v });
    }
    fin.close();
}

vector<pair<int, int>> DFS(vector<csomopont>& csp, vector<el>& elek) {
    vector<pair<int, int>> allapot(csp.size(), { 0, 0 });
    int ido = 0;
    for (int i = 1; i < csp.size(); i++) {
        if (allapot[i].first == 0) {
            DFS_visit(elek, i, allapot, ido, csp);
        }
    }
    topologiai_rendezes(allapot);
    return allapot;
}

void DFS_visit(vector<el>& elek, int cs, vector<pair<int, int>>& topo, int& ido, vector<csomopont>& csp) {
    topo[cs].first = 1;
    ido++;
    for (int i = 0; i < elek.size(); i++) {
        if (elek[i].u == cs && topo[elek[i].v].first == 0) {
            DFS_visit(elek, elek[i].v, topo, ido, csp);
        }
    }
    ido++;
    topo[cs].first = ido;
}

void topologiai_rendezes(vector<pair<int, int>>& topo) {
    for (int i = 1; i < topo.size(); i++) {
        topo[i].second = i;
    }
    sort(topo.begin() + 1, topo.end(), csokkeno);
}

bool csokkeno(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

void kritikus_ut(int csomopontok_szama, vector<csomopont>& csp, vector<el>& elek, vector<pair<int, int>>& topo) {
    csp[1].t0min = 0;
    csp[1].t1min = csp[1].ido;
    for (int j = 2; j <= csomopontok_szama; j++) {
        int u = topo[j].second;
        for (int i = 0; i < elek.size(); i++) {
            if (elek[i].v == u) {
                csp[u].t0min = max(csp[u].t0min, csp[elek[i].u].t1min);
            }
        }
        csp[u].t1min = csp[u].t0min + csp[u].ido;
    }
    csp[csomopontok_szama].t1max = csp[csomopontok_szama].t1min;
    csp[csomopontok_szama].t0max = csp[csomopontok_szama].t1max - csp[csomopontok_szama].ido;
    for (int j = csomopontok_szama - 1; j >= 1; j--) {
        int u = topo[j].second;
        for (int i = 0; i < elek.size(); i++) {
            if (elek[i].u == u) {
                csp[u].t1max = min(csp[u].t1max, csp[elek[i].v].t0max);
            }
        }
        csp[u].t0max = csp[u].t1max - csp[u].ido;
    }
    for (int i = 1; i <= csomopontok_szama; i++) {
        if (csp[i].t0min == csp[i].t0max && csp[i].t1min == csp[i].t1max) {
            csp[i].kritikus = true;
        }
    }
}

void kiir(vector<csomopont>& csp) {
    ofstream fout("3_ki.txt");
    for (int i = 1; i < csp.size(); i++) {
        if (csp[i].kritikus) {
            fout << csp[i].nev << " ";
        }
    }
    fout << endl;
    for (int i = 1; i < csp.size(); i++) {
        fout << csp[i].nev << " ";
        fout << csp[i].ido << " ";
        fout << csp[i].t0min << " ";
        fout << csp[i].t1min << " ";
        fout << csp[i].t0max << " ";
        fout << csp[i].t1max << endl;
    }
    fout.close();
}