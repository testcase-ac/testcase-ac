#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
using namespace std;
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}
int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    long long n = rand() % 1000000000000000000 + 1;
    long long k = rand() % (n + 1);
    int m;
    do {
        m = rand() % 1999 + 2;
    } while (!is_prime(m));
    cout << n << " " << k << " " << m << endl;
    return 0;
}
