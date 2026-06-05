#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeHeights(int mode, int n) {
    vector<int> h(n);

    if (mode == 0) {
        int value = rnd.next(1, 100);
        fill(h.begin(), h.end(), value);
    } else if (mode == 1) {
        int value = rnd.next(1, 15);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            h[i] = min(100, value + i * step);
        }
    } else if (mode == 2) {
        int value = rnd.next(86, 100);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            h[i] = max(1, value - i * step);
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 8);
        int high = rnd.next(93, 100);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0) ? low : high;
        }
    } else if (mode == 4) {
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(0, 3) == 0) {
                cur = rnd.next(1, 100);
            }
            h[i] = cur;
        }
    } else {
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(lo, hi);
        }
    }

    if (rnd.next(0, 4) == 0) h[0] = rnd.next(1, 100);
    if (rnd.next(0, 4) == 0) h[n - 1] = rnd.next(1, 100);

    return h;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 3) {
        n = rnd.next(2, 18);
    } else if (rnd.next(0, 4) == 0) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(2, 16);
    }

    vector<int> h = makeHeights(mode, n);

    println(n);
    println(h);

    return 0;
}
