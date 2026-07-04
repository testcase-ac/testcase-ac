#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool isPrime(long long x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

long long nextPrimeAtLeast(long long x) {
    if (x <= 2) return 2;
    if (x % 2 == 0) ++x;
    while (!isPrime(x)) x += 2;
    return x;
}

long long previousPrimeAtMost(long long x) {
    if (x < 2) return -1;
    if (x == 2) return 2;
    if (x % 2 == 0) --x;
    while (x >= 3 && !isPrime(x)) x -= 2;
    return x >= 2 ? x : -1;
}

string toString128(__int128 value) {
    if (value == 0) return "0";
    string s;
    while (value > 0) {
        s.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long p = 2;
    long long q = 3;
    long long k = 1;

    for (int attempt = 0; attempt < 10000; ++attempt) {
        if (mode == 0) {
            k = 1;
            p = nextPrimeAtLeast(rnd.next(2, 5000));
            q = nextPrimeAtLeast(p + rnd.next(0, 200));
        } else if (mode == 1) {
            k = rnd.next(2, 30);
            p = nextPrimeAtLeast(rnd.next(2, 2000));
            q = nextPrimeAtLeast(k * p);
        } else if (mode == 2) {
            k = rnd.next(2, 1000);
            p = nextPrimeAtLeast(rnd.next(100, 10000));
            long long target = k * p - rnd.next(0, 100000);
            q = nextPrimeAtLeast(max(target, p));
        } else if (mode == 3) {
            k = rnd.next(1000000, 99999999);
            p = rnd.any(vector<long long>{2, 3, 5, 7, 11, 13});
            q = nextPrimeAtLeast(k * p + rnd.next(-100, 100));
        } else if (mode == 4) {
            k = rnd.next(2, 100000);
            p = nextPrimeAtLeast(rnd.next(10000, 1000000));
            q = previousPrimeAtMost(k * p + rnd.next(0, 100000));
            if (q < p) continue;
        } else {
            k = rnd.next(1, 100);
            p = nextPrimeAtLeast(rnd.next(2, 100000));
            long long delta = rnd.next(-100000, 100000);
            q = nextPrimeAtLeast(max(p, k * p + delta));
        }

        if (q < p) swap(p, q);
        if (!isPrime(p) || !isPrime(q)) continue;
        if (llabs(q - k * p) > 100000) continue;

        println(toString128((__int128)p * q), k);
        return 0;
    }

    println("35", 1);
    return 0;
}
