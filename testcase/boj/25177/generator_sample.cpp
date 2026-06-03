#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int scoreNear(int base, int radius) {
    int lo = max(1, base - radius);
    int hi = min(1000, base + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 0) {
        m = n;
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.next(n + 1, 16);
    } else if (mode == 2) {
        m = rnd.next(1, 8);
        n = rnd.next(m + 1, 16);
    } else if (mode == 5) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
    }

    vector<int> a(n), b(m);

    if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(500, 1000);
        for (int i = 0; i < m; ++i) {
            if (i < n) {
                b[i] = rnd.next(1, a[i]);
            } else {
                b[i] = rnd.next(1, 20);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 40);
        for (int i = 0; i < m; ++i) b[i] = rnd.next(900, 1000);
    } else {
        int base = rnd.next(1, 1000);
        int radius = rnd.next(0, 250);
        for (int i = 0; i < n; ++i) a[i] = scoreNear(base, radius);
        for (int i = 0; i < m; ++i) b[i] = scoreNear(base, radius);

        if (rnd.next(0, 2) == 0 && n > 0 && m > 0) {
            int idx = rnd.next(0, min(n, m) - 1);
            a[idx] = rnd.next(1, 50);
            b[idx] = rnd.next(950, 1000);
        }
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
