#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(20, 100) : rnd.next(1, 12));
    int p = rnd.next(1, 100);
    int q = rnd.next(1, 100);

    if (mode == 1) {
        p = q;
    } else if (mode == 2 || mode == 3) {
        p = rnd.next(2, 100);
        q = rnd.next(1, p - 1);
    }

    vector<int> a(n), b(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 100);
            b[i] = a[i];
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 100);
            b[i] = (rnd.next(0, 3) == 0 ? a[i] : rnd.next(1, 100));
        }
    } else if (mode == 2) {
        int gap = p - q;
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(0, 99 / gap);
            int base = rnd.next(1, 100 - k * gap);
            a[i] = base;
            b[i] = base + k * gap;
        }
    } else if (mode == 3) {
        int gap = p - q;
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(0, 99 / gap);
            int base = rnd.next(1, 100 - k * gap);
            a[i] = base;
            b[i] = base + k * gap;
        }
        int bad = rnd.next(0, n - 1);
        if (gap == 1 || rnd.next(0, 1) == 0) {
            a[bad] = rnd.next(2, 100);
            b[bad] = rnd.next(1, a[bad] - 1);
        } else {
            b[bad] = clampValue(b[bad] + rnd.next(1, gap - 1));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{1, 2, 99, 100, rnd.next(1, 100)});
            b[i] = rnd.any(vector<int>{1, 2, 99, 100, rnd.next(1, 100)});
        }
    } else {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(51, 100);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
    }

    println(n, p, q);
    println(a);
    println(b);

    return 0;
}
