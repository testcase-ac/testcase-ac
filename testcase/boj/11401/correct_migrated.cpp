#include <iostream>
using namespace std;

const int m = 1000000007;
long long f[4000001];

long long p(long long a, long long b) {
    long long c = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            c = (c * a) % m;
        }
        a = (a * a) % m;
        b /= 2;
    }
    return c;
}

void precompute_factorials() {
    f[0] = 1;
    for (int i = 1; i <= 4000000; i++) {
        f[i] = f[i - 1] * i % m;
    }
}

long long com(long long n, long long k) {
    if (n < k) return 0;
    long long a = f[n];
    long long b = f[k];
    long long c = f[n - k];
    
    b = p(b, m - 2);
    c = p(c, m - 2);
    
    return (((a * b) % m) * c) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute_factorials();
    long long b, c;
    cin >> b >> c;
    cout << com(b,c);
}
