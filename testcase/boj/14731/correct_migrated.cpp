#include <iostream>
using namespace std;

long long p(long long a, long long b) {
    long long r = 1;
    while (b > 0) {
        if (b % 2 == 0) {
            a = (a * a) % 1000000007;
            b /= 2;
        } else {
            r = (r * a) % 1000000007;
            b -= 1;
        }
    }
    return r;
}

int main() {
    long long n, a, b, c = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        long long power = p(2, b - 1);
        c = (c + (a * b % 1000000007) * power % 1000000007) % 1000000007;
    }
    cout << c;
}
