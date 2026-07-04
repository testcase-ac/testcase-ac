#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long clampToLimit(long long value) {
    return min(value, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a = 1;
    long long b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        vector<long long> anchors = {1, 2, 12, 999983, 1000000000LL};
        a = rnd.any(anchors);
        if (rnd.next(0, 1)) {
            a = rnd.next(1LL, 1000000000LL);
        }
        b = a;
    } else if (mode == 1) {
        a = rnd.next(1LL, 100000LL);
        b = rnd.next(1LL, 100000LL);
        while (gcd(a, b) != 1) {
            b = rnd.next(1LL, 100000LL);
        }
    } else if (mode == 2) {
        long long g = rnd.next(1LL, 1000000LL);
        long long x = rnd.next(1LL, 1000LL);
        long long y = rnd.next(1LL, 1000LL);
        while (gcd(x, y) != 1) {
            y = rnd.next(1LL, 1000LL);
        }
        a = g * x;
        b = g * y;
    } else if (mode == 3) {
        vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        long long p = rnd.any(primes);
        long long q = rnd.any(primes);
        a = 1;
        b = 1;
        for (int i = 0; i < rnd.next(0, 12); ++i) {
            if (a <= 1000000000LL / p) a *= p;
        }
        for (int i = 0; i < rnd.next(0, 12); ++i) {
            if (b <= 1000000000LL / q) b *= q;
        }
    } else if (mode == 4) {
        long long base = rnd.next(900000000LL, 1000000000LL);
        long long delta = rnd.next(0LL, 100000LL);
        a = max(1LL, base - delta);
        b = base;
    } else {
        long long g = rnd.next(1LL, 50000LL);
        vector<long long> factors = {1, 2, 3, 4, 6, 8, 9, 12, 18, 24, 36, 48, 72, 96};
        long long x = rnd.any(factors);
        long long y = rnd.any(factors);
        a = g * x;
        b = g * y;
    }

    a = clampToLimit(a);
    b = clampToLimit(b);
    if (a > b) {
        swap(a, b);
    }

    println(a, b);
    return 0;
}
