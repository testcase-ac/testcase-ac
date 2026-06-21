#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long nearValue(long long base, long long spread) {
    long long lo = max(1LL, base - spread);
    long long hi = min(1000000000LL, base + spread);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(2, 12);
        k = 2;
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        k = n;
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        k = rnd.next(3, min(n, 6));
    } else if (mode == 3) {
        n = rnd.next(8, 28);
        k = rnd.next(max(2, n / 2), n);
    } else if (mode == 4) {
        n = rnd.next(15, 35);
        k = rnd.next(2, min(n, 10));
    } else if (mode == 5) {
        n = rnd.next(20, 45);
        k = rnd.next(max(2, n / 3), min(n, 2 * n / 3 + 1));
    } else if (mode == 6) {
        n = rnd.next(280, 360);
        k = rnd.next(2, 20);
    } else {
        n = rnd.next(240, 320);
        k = rnd.next(max(2, n - 40), n);
    }

    a.assign(n, 1);
    int pattern = rnd.next(0, 6);

    if (pattern == 0) {
        long long cur = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 20LL);
            a[i] = min(cur, 1000000000LL);
        }
    } else if (pattern == 1) {
        long long cur = rnd.next(1LL, 500LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 200LL);
            a[n - 1 - i] = min(cur, 1000000000LL);
        }
    } else if (pattern == 2) {
        long long high = rnd.next(800000000LL, 1000000000LL);
        long long low = rnd.next(1LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            if ((i % max(2, k - 1)) == 0 || rnd.next(0, 9) == 0) {
                a[i] = nearValue(high, 5000000LL);
            } else {
                a[i] = nearValue(low, 200LL);
            }
        }
    } else if (pattern == 3) {
        long long high = rnd.next(1000000LL, 1000000000LL);
        long long low = rnd.next(1LL, 10000LL);
        for (int i = 0; i < n; ++i) {
            int pos = i % k;
            if (pos == 0 || pos == k - 1) {
                a[i] = nearValue(high, high / 20 + 1);
            } else {
                a[i] = nearValue(low, 1000LL);
            }
        }
    } else if (pattern == 4) {
        for (int i = 0; i < n; ++i) {
            long long band = (i / max(1, k / 2)) % 2 ? 1000000000LL : 1000LL;
            a[i] = nearValue(band, band / 30 + 1);
        }
    } else if (pattern == 5) {
        vector<long long> choices = {1, 2, 3, 999999937LL, 999999999LL, 1000000000LL};
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(choices);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1LL, 1000000000LL);
        }
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(a.begin(), a.end());
    }

    println(n, k);
    println(a);
    return 0;
}
