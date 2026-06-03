#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampHeight(int x) {
    return max(1, min(1000000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    vector<int> h(n);

    if (mode == 0) {
        int cur = rnd.next(1, 1000000 - n);
        int step = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            h[i] = clampHeight(cur + i * step);
        }
    } else if (mode == 1) {
        int cur = rnd.next(n, 1000000);
        int step = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            h[i] = clampHeight(cur - i * step);
        }
    } else if (mode == 2) {
        int value = rnd.next(1, 1000000);
        fill(h.begin(), h.end(), value);
    } else if (mode == 3) {
        int low = rnd.next(1, 100);
        int high = rnd.next(999900, 1000000);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0 ? low + rnd.next(0, 20) : high - rnd.next(0, 20));
        }
    } else if (mode == 4) {
        int groups = rnd.next(1, min(8, n));
        int pos = 0;
        for (int g = 0; g < groups; ++g) {
            int remaining = n - pos;
            int len = (g == groups - 1 ? remaining : rnd.next(1, remaining - (groups - g - 1)));
            int value = rnd.next(1, 1000000);
            for (int i = 0; i < len; ++i) {
                h[pos++] = value;
            }
        }
    } else if (mode == 5) {
        int base = rnd.next(1, 1000000);
        h[0] = base;
        for (int i = 1; i < n; ++i) {
            int delta = rnd.next(-5, 5);
            h[i] = clampHeight(h[i - 1] + delta);
        }
    } else {
        int lo = rnd.next(1, 999950);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 50)));
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(lo, hi);
        }
    }

    println(n);
    println(h);
    return 0;
}
