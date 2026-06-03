#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0 ? 1 : rnd.next(2, 18));
    vector<long long> a(n);

    if (mode == 0) {
        a[0] = rnd.next(1LL, 1000000000LL);
    } else if (mode == 1) {
        long long cur = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 5LL);
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long cur = rnd.next(1LL, 80LL);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = max(1LL, cur - rnd.next(0LL, 8LL));
        }
    } else if (mode == 3) {
        long long lo = rnd.next(1LL, 8LL);
        long long hi = rnd.next(20LL, 60LL);
        for (int i = 0; i < n; ++i) a[i] = rnd.next() < 0.65 ? lo : hi;
    } else if (mode == 4) {
        long long base = rnd.next(15LL, 80LL);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(0LL, 15LL);
        int valley = rnd.next(0, n - 1);
        a[valley] = rnd.next(1LL, max(1LL, base - 1));
    } else if (mode == 5) {
        long long base = rnd.next(999999900LL, 1000000000LL);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(max(1LL, base - 40), base);
    } else {
        long long lo = rnd.next(1LL, 100LL);
        long long hi = rnd.next(lo, lo + 100LL);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = rnd.next(1LL, 30LL);
    } else if (kMode == 1) {
        k = rnd.next(31LL, 1000LL);
    } else if (kMode == 2) {
        k = rnd.next(1000000000LL, 1000000000000LL);
    } else if (kMode == 3) {
        k = rnd.next(999999999999999000LL, 1000000000000000000LL);
    } else {
        k = rnd.next(1LL, 1000000000000000000LL);
    }

    println(n);
    println(a);
    println(k);
}
