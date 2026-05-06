#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    int t = rand() % 15 + 1;
    cout << t << endl;
    for (int i = 0; i < t/3; ++i) {
        long long k = rand() % 1000 + 1;
        long long c = rand() % 1000 + 1;
        cout << k << " " << c << endl;
    } for (int i = t/3; i < 2*t/3; ++i) {
        long long k = rand() % 1000000 + 1;
        long long c = rand() % 1000000 + 1;
        cout << k << " " << c << endl;
    } for (int i = 2*t/3; i < t; ++i) {
        long long k = rand() % 1000000000 + 1;
        long long c = rand() % 1000000000 + 1;
        cout << k << " " << c << endl;
    }
    return 0;
}
