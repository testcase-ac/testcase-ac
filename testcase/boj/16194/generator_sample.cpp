#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampPrice(int x) {
    return max(1, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 85) {
        n = rnd.next(2, 30);
    } else {
        n = rnd.next(31, 120);
    }

    vector<int> p(n);
    int mode = rnd.next(6);

    if (mode == 0) {
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            p[i] = clampPrice(base * (i + 1) + rnd.next(0, 8));
        }
    } else if (mode == 1) {
        int start = rnd.next(20, 200);
        int step = rnd.next(0, 6);
        for (int i = 0; i < n; ++i) {
            p[i] = clampPrice(start - step * i + rnd.next(0, 10));
        }
    } else if (mode == 2) {
        int cheapSize = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int blocks = (i + cheapSize) / cheapSize;
            p[i] = clampPrice(blocks * rnd.next(1, 12) + rnd.next(0, 5));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(1, 80);
        }
        for (int i = 0; i < n; i += rnd.next(2, 5)) {
            p[i] = rnd.next(5000, 10000);
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 10);
        int high = rnd.next(50, 500);
        for (int i = 0; i < n; ++i) {
            p[i] = (rnd.next(100) < 70) ? rnd.next(low, low + 20) : rnd.next(high, min(10000, high + 200));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(1, 10000);
        }
    }

    println(n);
    println(p);
    return 0;
}
