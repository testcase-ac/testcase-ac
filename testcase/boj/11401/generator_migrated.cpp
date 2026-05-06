#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    long long n = rand() % 4000000 + 1;
    long long k = rand() % (n + 1);
    cout << n << " " << k << endl;
    return 0;
}
