#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n, q
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    // array A
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    for (int qi = 0; qi < q; ++qi) {
        int type = inf.readInt(1, 4, "t");
        if (type == 1) {
            // 1 l r c
            inf.readSpace();
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n - 1, "r");
            inf.readSpace();
            long long c = inf.readLong(-10000LL, 10000LL, "c");
            inf.readEoln();

            ensuref(l <= r, "Query %d: l (%d) > r (%d) in type 1", qi + 1, l, r);

            // simulate to ensure no overflow of A_i beyond 64-bit during validation
            for (int i = l; i <= r; ++i) {
                __int128 v = (__int128)a[i] + (__int128)c;
                ensuref(v >= LLONG_MIN && v <= LLONG_MAX,
                        "Query %d: addition overflows 64-bit at index %d", qi + 1, i);
                a[i] = (long long)v;
            }

        } else if (type == 2) {
            // 2 l r d
            inf.readSpace();
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n - 1, "r");
            inf.readSpace();
            long long d = inf.readLong(2LL, 1000000000LL, "d");
            inf.readEoln();

            ensuref(l <= r, "Query %d: l (%d) > r (%d) in type 2", qi + 1, l, r);

            // apply floor division
            for (int i = l; i <= r; ++i) {
                long long x = a[i];
                if (x >= 0) {
                    a[i] = x / d;
                } else {
                    // floor division for negative values
                    long long qv = x / d;
                    long long rv = x % d;
                    if (rv != 0) --qv;
                    a[i] = qv;
                }
            }

        } else if (type == 3) {
            // 3 l r
            inf.readSpace();
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n - 1, "r");
            inf.readEoln();

            ensuref(l <= r, "Query %d: l (%d) > r (%d) in type 3", qi + 1, l, r);

            // simulate min, no further constraints given but ensure it fits in 64-bit
            long long mn = a[l];
            for (int i = l + 1; i <= r; ++i)
                mn = min(mn, a[i]);
            (void)mn;

        } else { // type == 4
            // 4 l r
            inf.readSpace();
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n - 1, "r");
            inf.readEoln();

            ensuref(l <= r, "Query %d: l (%d) > r (%d) in type 4", qi + 1, l, r);

            // simulate sum using 128-bit to check it stays in 64-bit
            __int128 s = 0;
            for (int i = l; i <= r; ++i) s += (__int128)a[i];
            ensuref(s >= LLONG_MIN && s <= LLONG_MAX,
                    "Query %d: sum overflows 64-bit integer range", qi + 1);
        }
    }

    inf.readEof();
}
