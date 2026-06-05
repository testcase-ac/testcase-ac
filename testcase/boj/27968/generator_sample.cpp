#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(6, 18);
    int m = rnd.next(4, 16);

    vector<long long> a(m);
    if (mode == 0) {
        long long cur = rnd.next(1, 4);
        for (int i = 0; i < m; ++i) {
            cur += rnd.next(0, 5);
            a[i] = cur;
        }
    } else if (mode == 1) {
        long long base = rnd.next(900000000, 1000000000);
        for (int i = 0; i < m; ++i) {
            a[i] = base - rnd.next(0, 1000);
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            a[i] = (i % 3 == 0) ? rnd.next(500000000, 1000000000) : rnd.next(1, 20);
        }
    } else {
        long long lo = rnd.next(1, 30);
        long long hi = rnd.next(31, 2000);
        for (int i = 0; i < m; ++i) {
            a[i] = rnd.next(lo, hi);
        }
        shuffle(a.begin(), a.end());
    }

    vector<long long> pref(m);
    for (int i = 0; i < m; ++i) {
        pref[i] = a[i] + (i == 0 ? 0 : pref[i - 1]);
    }

    vector<long long> b;
    b.reserve(n);
    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(6);
        int idx = rnd.next(m);
        long long x;

        if (kind == 0) {
            x = pref[idx];
        } else if (kind == 1) {
            x = max(1LL, pref[idx] - rnd.next(1, 3));
        } else if (kind == 2) {
            x = pref[idx] + rnd.next(1, 3);
        } else if (kind == 3) {
            x = rnd.next(1LL, pref[m - 1]);
        } else if (kind == 4) {
            x = pref[m - 1] + rnd.next(1, 1000000);
        } else {
            x = rnd.next(1LL, 1000000000000LL);
        }

        b.push_back(min(1000000000000LL, x));
    }

    println(n, m);
    println(a);
    for (long long x : b) {
        println(x);
    }

    return 0;
}
