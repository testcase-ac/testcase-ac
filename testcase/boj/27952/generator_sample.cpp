#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_VALUE = 1000000000LL;

    int mode = rnd.next(0, 5);
    int n;
    ll x;
    vector<ll> a, b;

    if (mode == 0) {
        n = rnd.next(1, 8);
        x = rnd.next(1LL, 20LL);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1LL, 30LL);
            b[i] = rnd.next(1LL, 30LL);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        x = rnd.next(1LL, 100LL);
        a.resize(n);
        b.resize(n);
        ll prefix = 0;
        int failAt = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.next(1LL, 20LL);
            prefix += b[i];
            if (i == failAt) {
                a[i] = min(MAX_VALUE, prefix + rnd.next(1LL, 20LL));
            } else {
                a[i] = rnd.next(1LL, min(MAX_VALUE, prefix + 20));
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        x = rnd.next(1LL, 50LL);
        a.resize(n);
        b.resize(n);
        ll prefix = 0;
        for (int i = 0; i < n; ++i) {
            b[i] = rnd.next(1LL, 25LL);
            prefix += b[i];
            ll slack = rnd.next(0LL, min(10LL, prefix - 1));
            a[i] = prefix - slack;
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        x = rnd.next(1LL, 1000000000LL);
        a.assign(n, 1);
        b.assign(n, 1);
        int bigPos = rnd.next(0, n - 1);
        b[bigPos] = rnd.next(900000000LL, MAX_VALUE);
        int tightPos = rnd.next(bigPos, n - 1);
        ll prefix = 0;
        for (int i = 0; i < n; ++i) {
            prefix += b[i];
            if (i == tightPos) {
                a[i] = rnd.next(max(1LL, prefix - 5), min(MAX_VALUE, prefix));
            } else {
                a[i] = rnd.next(1LL, min(MAX_VALUE, prefix));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 40);
        x = rnd.next(1LL, 100LL);
        a.resize(n);
        b.resize(n);
        ll prefix = 0;
        for (int i = 0; i < n; ++i) {
            b[i] = (i % 2 == 0) ? rnd.next(1LL, 3LL) : rnd.next(20LL, 60LL);
            prefix += b[i];
            if (rnd.next(0, 3) == 0) {
                a[i] = min(MAX_VALUE, prefix + rnd.next(1LL, 5LL));
            } else {
                a[i] = rnd.next(1LL, min(MAX_VALUE, prefix));
            }
        }
    } else {
        n = rnd.next(2, 10);
        x = rnd.next(900000000LL, MAX_VALUE);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(900000000LL, MAX_VALUE);
            b[i] = rnd.next(900000000LL, MAX_VALUE);
        }
    }

    println(n, x);
    println(a);
    println(b);

    return 0;
}
