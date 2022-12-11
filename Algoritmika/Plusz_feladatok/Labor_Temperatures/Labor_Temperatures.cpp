#include <iostream>
#include <vector>

using namespace std;

void read(short& n, vector<short>& temperatures) {
    cin >> n;

    for (short i = 0; i < n; i++) {
        short temperature;
        cin >> temperature;
        temperatures.push_back(temperature);
    }

    return;
}

short closest(vector<short>& temperatures) {
    if (temperatures.size() == 0) {
        return 0;
    }

    short min_sub, closest;
    if (temperatures[0] < 0) {
        min_sub = -temperatures[0];
        closest = temperatures[0];
    }
    else {
        min_sub = temperatures[0];
        closest = temperatures[0];
    }

    for (short i = 0; i < temperatures.size(); i++) {
        short temp_sub = 0;
        if (temperatures[i] < 0) {
            temp_sub = -temperatures[i];
        }
        else {
            temp_sub = temperatures[i];
        }
        if (temp_sub < min_sub) {
            min_sub = temp_sub;
            closest = temperatures[i];
        }
        if (temp_sub == min_sub && temperatures[i] >= 0) {
            closest = temperatures[i];
        }
    }
    return closest;
}

void write(short& closest) {
    cout << closest << endl;
    return;
}

int main()
{
    short n;
    vector<short> temperatures;

    read(n, temperatures);

    short answer = closest(temperatures);

    write(answer);

    return 0;
}