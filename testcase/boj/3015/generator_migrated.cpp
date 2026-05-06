#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    int n = rand() % 20 + 1;
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
        cout << rand() % (1 << 20) << endl;
    }
    return 0;
}
