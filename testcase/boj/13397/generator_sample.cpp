#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampedValue(int value) {
    return max(1, min(10000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, n);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int low = rnd.next(1, 5000);
        int high = rnd.next(low, min(10000, low + rnd.next(1, 300)));
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? low : high);
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 10000);
        int step = rnd.next(-80, 80);
        if (step == 0) step = 1;
        for (int i = 0; i < n; ++i) {
            a[i] = clampedValue(start + i * step);
        }
    } else if (mode == 3) {
        int blocks = rnd.next(1, min(n, 8));
        int pos = 0;
        for (int b = 0; b < blocks; ++b) {
            int remaining = n - pos;
            int len = (b == blocks - 1) ? remaining : rnd.next(1, remaining - (blocks - b - 1));
            int center = rnd.next(1, 10000);
            int radius = rnd.next(0, 120);
            for (int i = 0; i < len; ++i) {
                a[pos++] = clampedValue(center + rnd.next(-radius, radius));
            }
        }
        m = rnd.next(1, min(n, blocks + rnd.next(0, 3)));
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10000);
        }
    } else {
        int low = rnd.next(1, 20);
        int high = rnd.next(9980, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) < 4) {
                a[i] = rnd.next(1, 10000);
            } else {
                a[i] = rnd.next(0, 1) == 0 ? low : high;
            }
        }
    }

    println(n, m);
    println(a);

    return 0;
}
