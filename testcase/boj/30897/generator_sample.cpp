#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 30000;
    } else if (mode == 1) {
        n = 50000;
    } else {
        n = rnd.next(30000, 50000);
    }

    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1) == 0 ? 0 : rnd.next(1, 10);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10000);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = 1;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? 10000 : 1;
        }
    } else if (mode == 4) {
        int zeroPos = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            a[i] = (i == zeroPos) ? 0 : rnd.next(1, 10000);
        }
    } else if (mode == 5) {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (mode == 6) {
        vector<int> palette = {0, 1, 2, 9999, 10000};
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(palette);
        }
    } else {
        int block = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            int base = (i / block) % 2 == 0 ? rnd.next(0, 20) : rnd.next(9980, 10000);
            a[i] = base;
        }
    }

    println(n);
    println(a);

    return 0;
}
