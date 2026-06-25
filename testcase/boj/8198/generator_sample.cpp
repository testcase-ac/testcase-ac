#include "testlib.h"

#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll LIMIT = 1000000000000000000LL;

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(4, 24);
    }

    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 2) {
        k = n - 1;
    } else {
        k = rnd.next(1, n - 1);
    }

    ll m;
    int mMode = rnd.next(0, 5);
    if (mMode == 0) {
        m = 1;
    } else if (mMode == 1) {
        m = rnd.next(2, 12);
    } else if (mMode == 2) {
        m = rnd.next(13, 1000);
    } else if (mMode == 3) {
        m = LIMIT;
    } else {
        m = rnd.next(1LL, LIMIT);
    }

    vector<ll> p;
    p.reserve(n);

    if (mode == 3) {
        ll cur = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(1LL, 3LL);
        }
    } else if (mode == 4) {
        ll cur = rnd.next(1LL, 50LL);
        ll gap = rnd.next(1LL, 5LL);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += gap;
            gap *= rnd.next(2LL, 4LL);
        }
    } else if (mode == 5) {
        ll cur = LIMIT - rnd.next(5000LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(1LL, 100LL);
        }
    } else {
        ll cur = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            if (i + 1 < n) {
                ll gap = rnd.next(1LL, 40LL);
                if (rnd.next(0, 3) == 0) {
                    gap = rnd.next(1LL, 4LL);
                }
                cur += gap;
            }
        }
    }

    println(n, k, m);
    println(p);
    return 0;
}
