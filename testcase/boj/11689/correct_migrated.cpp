#include <iostream>
#include <cmath>
using namespace std;

long long e(long long n) {
    long long r = n;
    if (n % 2 == 0) {
        r -= r / 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    for (long long p = 3; p * p <= n; p += 2) {
        if (n % p == 0) {
            r -= r / p;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        r -= r / n;
    }
    return r;
}

int main() {
    long long n;
    cin >> n;
    cout << e(n) << endl;
}
