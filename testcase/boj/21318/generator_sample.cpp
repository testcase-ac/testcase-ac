#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 6) {
        n = rnd.next(50000, 100000);
    } else {
        n = rnd.next(2, 30);
    }

    vector<long long> a(n);
    if (mode == 0) {
        a[0] = rnd.next(1LL, 1000000000LL);
    } else if (mode == 1) {
        long long cur = rnd.next(1LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 5LL);
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long cur = rnd.next(1000000000LL - 1000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = max(1LL, cur - rnd.next(1LL, 5LL));
        }
    } else if (mode == 3) {
        long long low = rnd.next(1LL, 20LL);
        long long high = rnd.next(999999980LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            if (i % 4 == 0) {
                a[i] = high;
            } else if (i % 4 == 1) {
                a[i] = low;
            } else {
                a[i] = rnd.next(low, high);
            }
        }
    } else if (mode == 4) {
        vector<long long> palette;
        int colors = rnd.next(1, 5);
        for (int i = 0; i < colors; ++i) {
            palette.push_back(rnd.next(1LL, 1000000000LL));
        }
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(palette);
        }
    } else {
        long long lo = rnd.next(1LL, 1000000000LL);
        long long hi = rnd.next(lo, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    }

    int q;
    if (mode == 6) {
        q = rnd.next(50000, 100000);
    } else if (mode == 0) {
        q = rnd.next(1, 8);
    } else {
        q = rnd.next(1, 40);
    }

    println(n);
    println(a);
    println(q);

    for (int i = 0; i < q; ++i) {
        int x, y;
        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            x = y = rnd.next(1, n);
        } else if (queryMode == 1) {
            x = 1;
            y = rnd.next(1, n);
        } else if (queryMode == 2) {
            x = rnd.next(1, n);
            y = n;
        } else if (queryMode == 3) {
            x = 1;
            y = n;
        } else {
            x = rnd.next(1, n);
            y = rnd.next(x, n);
        }
        println(x, y);
    }

    return 0;
}
