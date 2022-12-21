#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void beolvas(int& w, int& h, int& n, int& x0, int& y0) {
    cin >> w >> h; cin.ignore();
    cin >> n; cin.ignore();
    cin >> x0 >> y0;
}

void jatek(int& w, int& h, int& n, int& x0, int& y0) {
    int regijobb = w, regibal = 0, regilent = h, regifent = 0;
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();

        if (bomb_dir == "U") {
            regilent = y0;
            y0 = (regifent + regilent) / 2;
        }
        if (bomb_dir == "UR") {
            regibal = x0;
            regilent = y0;
            x0 = (regijobb + regibal) / 2;
            y0 = (regifent + regilent) / 2;
        }
        if (bomb_dir == "R") {
            regibal = x0;
            x0 = (regijobb + regibal) / 2;
        }
        if (bomb_dir == "DR") {
            regifent = y0;
            regibal = x0;
            x0 = (regibal + regijobb) / 2;
            y0 = (regifent + regilent) / 2;
        }
        if (bomb_dir == "D") {
            regifent = y0;
            y0 = (regifent + regilent) / 2;
        }
        if (bomb_dir == "DL") {
            regifent = y0;
            regijobb = x0;
            x0 = (regijobb + regibal) / 2;
            y0 = (regifent + regilent) / 2;
        }
        if (bomb_dir == "L") {
            regijobb = x0;
            x0 = (regibal + regijobb) / 2;
        }
        if (bomb_dir == "UL") {
            regilent = y0;
            regijobb = x0;
            x0 = (regijobb + regibal) / 2;
            y0 = (regifent + regilent) / 2;
        }
        // the location of the next window Batman should jump to.
        cout << x0 << " " << y0 << endl;
    }
}

int main()
{
    int w, h, n, x0, y0;
    beolvas(w, h, n, x0, y0);

    jatek(w, h, n, x0, y0);

    return 0;
}