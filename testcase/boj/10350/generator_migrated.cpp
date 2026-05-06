#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    int n = rand() % 10 + 1;
    cout << n << endl;

    vector<int> capitals(n);
    int sum = 0;

    do {
        sum = 0;
        for (int i = 0; i < n; i++) {
            capitals[i] = rand() % 2001 - 1000;
            sum += capitals[i];
        }
    } while (sum <= 0);

    for (int i = 0; i < n; i++) {
        cout << capitals[i];
        if (i < n - 1) cout << ' ';
    }
    cout << endl;

    return 0;
}
