#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void input(int& n, vector<int>& stocks) {
    cin >> n;
    stocks.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> stocks[i];
    }
}

void calculate(vector<int>& losses, vector<int>& stocks) {
    int peak = stocks[0];
    for (int i = 1; i < stocks.size(); i++) {
        if (stocks[i] >= peak) {
            peak = stocks[i];
        }
        else {
            losses[i] = losses[i - 1] + (stocks[i] - stocks[i - 1]);
        }
    }
}

int find_min(vector<int>& losses) {
    int min = losses[0];
    for (int i = 1; i < losses.size(); i++) {
        if (losses[i] < min)
        {
            min = losses[i];
        }
    }
    return min;
}

void output(vector<int>& losses) {
    int biggest_loss = find_min(losses);
    cout << biggest_loss << endl;
}

int main()
{
    int n;
    vector<int> stocks;
    input(n, stocks);

    vector<int> losses(n, 0);
    calculate(losses, stocks);

    output(losses);
    return 0;
}