#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(4, 28);
    }

    vector<int> a(n);
    int low = rnd.next(1, 50);
    int high = rnd.next(999950, 1000000);

    if (mode == 0) {
        int start = rnd.next(1, 100);
        int step = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = min(1000000, start + i * step + rnd.next(0, 3));
        }
    } else if (mode == 1) {
        int start = rnd.next(999000, 1000000);
        int step = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = max(1, start - i * step - rnd.next(0, 3));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(low, low + 80);
            } else {
                a[i] = rnd.next(high - 80, high);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 1000000);
        int radius = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            a[i] = min(1000000, max(1, base + rnd.next(-radius, radius)));
        }
    } else if (mode == 4) {
        int p = rnd.next(1, n - 3);
        int q = rnd.next(p + 1, n - 2);
        int r = rnd.next(q + 1, n - 1);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(200000, 800000);
        }
        a[p - 1] = rnd.next(1, 100);
        a[p] = rnd.next(900000, 1000000);
        a[q] = rnd.next(1, 100);
        a[r] = rnd.next(900000, 1000000);
    } else if (mode == 5) {
        vector<int> pool = {
            1,
            2,
            rnd.next(3, 20),
            rnd.next(999981, 999998),
            999999,
            1000000
        };
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(pool);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int block = i * 4 / n;
            if (block == 0 || block == 2) {
                a[i] = rnd.next(1, 250000);
            } else {
                a[i] = rnd.next(750000, 1000000);
            }
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    }

    println(n);
    println(a);
    return 0;
}
