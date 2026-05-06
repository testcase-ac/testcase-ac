#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    cout << rand() % 1000000000 + 1 << endl;
    return 0;
}
