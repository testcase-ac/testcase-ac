#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 7) {
        n = rnd.next(20, 50);
    } else {
        n = rnd.next(3, 15);
    }

    vector<int> a(n);

    if (mode == 0) {
        int lo = rnd.next(0, 20);
        int hi = rnd.next(lo, 1000000000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 1) {
        int leftSlope = rnd.next(0, 8);
        int rightSlope = rnd.next(0, 8);
        int valley = rnd.next(0, 30);
        int pivot = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i <= pivot) {
                a[i] = valley + (pivot - i) * leftSlope;
            } else {
                a[i] = valley + (i - pivot) * rightSlope;
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 40);
        int peak = rnd.next(base + 1, base + 80);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(0, 8);
        int center = rnd.next(1, n - 2);
        a[center] = peak;
        if (rnd.next(0, 1)) a[rnd.next(0, n - 1)] = rnd.next(0, base);
    } else if (mode == 3) {
        int low = rnd.next(0, 15);
        int high = rnd.next(low + 1, low + 60);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? high : low) + rnd.next(0, 5);
        }
    } else if (mode == 4) {
        int cur = rnd.next(0, 50);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-12, 12);
            cur = max(0, cur);
            a[i] = cur;
        }
    } else if (mode == 5) {
        int base = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) a[i] = base;
        int changes = rnd.next(1, min(n, 5));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] = max(0, base + rnd.next(-30, 80));
        }
    } else if (mode == 6) {
        int highBase = rnd.next(999999900, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = highBase - rnd.next(0, 100);
        }
        int pos = rnd.next(0, n - 1);
        a[pos] = rnd.next(0, 100);
    } else {
        int split1 = rnd.next(0, n - 1);
        int split2 = rnd.next(split1, n - 1);
        int x = rnd.next(0, 1000);
        int y = rnd.next(0, 1000);
        int z = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            if (i < split1) a[i] = x + rnd.next(0, 20);
            else if (i < split2) a[i] = y + rnd.next(0, 20);
            else a[i] = z + rnd.next(0, 20);
        }
    }

    println(n);
    println(a);

    return 0;
}
