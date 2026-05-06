#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    int n = rand() % 100 + 1;
    int l = rand() % n + 1;
    int r = rand() % n + 1;
    cout << n << " " << l << " " << r << endl;
    return 0;
}
