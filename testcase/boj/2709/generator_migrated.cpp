#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    int t = rand() % 20 + 1;
    cout << t << endl;

    for (int i = 0; i < t; i++) {
        int r = rand() % 20 + 1;
        cout << r << endl;
    }
    return 0;
}
