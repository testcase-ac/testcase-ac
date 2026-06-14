#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

using ll = long long;

void ensureNonEmpty(vector<ll>& c) {
    ll total = accumulate(c.begin(), c.end(), 0LL);
    if (total == 0) {
        c[rnd.next(0, (int)c.size() - 1)] = 1;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 35);
    if (mode == 6) {
        n = rnd.next(36, 120);
    }

    vector<ll> c(n, 0);

    if (mode == 0) {
        c[rnd.next(0, n - 1)] = 1;
    } else if (mode == 1) {
        int nonzero = rnd.next(1, min(n, 8));
        vector<int> positions(n);
        iota(positions.begin(), positions.end(), 0);
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < nonzero; ++i) {
            c[positions[i]] = rnd.next(1, 4);
        }
    } else if (mode == 2) {
        int prefix = rnd.next(1, n);
        for (int i = 0; i < prefix; ++i) {
            c[i] = rnd.next(1, 3);
        }
        for (int i = prefix; i < n; ++i) {
            c[i] = rnd.next(0, 5) == 0 ? rnd.next(1, 2) : 0;
        }
    } else if (mode == 3) {
        int gap = rnd.next(2, 5);
        int shift = rnd.next(0, gap - 1);
        for (int i = 0; i < n; ++i) {
            if ((i + shift) % gap != 0) {
                c[i] = rnd.next(1, 6);
            }
        }
    } else if (mode == 4) {
        int highCount = rnd.next(1, min(n, 6));
        for (int i = 0; i < highCount; ++i) {
            c[rnd.next(0, n - 1)] = rnd.next(999999900, 1000000000);
        }
        int smallCount = rnd.next(0, min(n, 10));
        for (int i = 0; i < smallCount; ++i) {
            int pos = rnd.next(0, n - 1);
            if (c[pos] == 0) {
                c[pos] = rnd.next(1, 20);
            }
        }
    } else if (mode == 5) {
        int tailStart = rnd.next(0, n - 1);
        for (int i = tailStart; i < n; ++i) {
            c[i] = rnd.next(1, 7);
        }
        for (int i = 0; i < tailStart; ++i) {
            c[i] = rnd.next(0, 3) == 0 ? rnd.next(1, 3) : 0;
        }
    } else {
        int lo = rnd.next(0, 5);
        int hi = rnd.next(lo + 1, 1000);
        for (int i = 0; i < n; ++i) {
            c[i] = rnd.next(0, 3) == 0 ? 0 : rnd.next(lo, hi);
        }
    }

    ensureNonEmpty(c);

    println(n);
    println(c);

    return 0;
}
