#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_A = 1000000000LL;

vector<long long> makeIncreasing(int n, long long lo, long long hi) {
    vector<long long> values(n);
    long long cur = rnd.next(lo, min(hi - n + 1, lo + 5));
    values[0] = cur;
    for (int i = 1; i < n; ++i) {
        long long remaining = hi - cur - (n - i - 1);
        long long step = rnd.next(1LL, min(20LL, remaining));
        cur += step;
        values[i] = cur;
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    long long k;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1LL, 20LL);
        a = makeIncreasing(n, 0, 200);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(2LL, 50LL);
        vector<long long> finalValues = makeIncreasing(n, k, 300);
        a = finalValues;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1)) {
                a[i] -= k;
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = rnd.next(1LL, 15LL);
        long long base = rnd.next(k + 1, k + 30);
        a.assign(n, base);
        for (int i = 0; i < n; ++i) {
            a[i] += rnd.next(0LL, min(3LL, k));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        k = rnd.next(1LL, 1000000000LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(MAX_A - 100, MAX_A);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 15);
        k = 1000000000LL;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? MAX_A : rnd.next(0LL, 30LL);
        }
    } else if (mode == 5) {
        n = rnd.next(10, 40);
        k = rnd.next(1LL, 100LL);
        a.resize(n);
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-5LL, 8LL);
            cur = max(0LL, min(MAX_A, cur));
            a[i] = cur;
        }
    } else {
        n = rnd.next(1, 100);
        k = rnd.next(1LL, 1000000000LL);
        a.resize(n);
        long long hi = rnd.next(0LL, MAX_A);
        long long lo = rnd.next(0LL, hi);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    }

    println(n, k);
    println(a);
    return 0;
}
