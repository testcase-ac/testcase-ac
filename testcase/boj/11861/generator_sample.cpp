#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomHeight(int low, int high) {
    return rnd.next(low, high);
}

void clampHeights(vector<int>& h) {
    for (int& x : h) {
        x = max(1, min(15000, x));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    vector<int> h(n);

    if (mode == 0) {
        int start = randomHeight(1, 80);
        int step = randomHeight(0, 12);
        for (int i = 0; i < n; ++i) h[i] = start + i * step;
    } else if (mode == 1) {
        int start = randomHeight(1, 80);
        int step = randomHeight(0, 12);
        for (int i = 0; i < n; ++i) h[i] = start + (n - 1 - i) * step;
    } else if (mode == 2) {
        int base = randomHeight(1, 120);
        int blockSize = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            if (i % blockSize == 0) base = randomHeight(1, 120);
            h[i] = base;
        }
    } else if (mode == 3) {
        int high = randomHeight(30, 180);
        int low = randomHeight(1, min(20, high));
        for (int i = 0; i < n; ++i) h[i] = high;
        for (int i = rnd.next(0, max(0, n - 1)); i < n; i += rnd.next(2, 5)) {
            h[i] = low;
        }
    } else if (mode == 4) {
        int base = randomHeight(1, 50);
        int peak = randomHeight(base, 200);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            h[i] = base + dist * rnd.next(0, 8);
        }
        if (n > 0) h[rnd.next(0, n - 1)] = peak;
    } else if (mode == 5) {
        int a = randomHeight(1, 30);
        int b = randomHeight(31, 160);
        for (int i = 0; i < n; ++i) h[i] = (i % 2 == 0 ? a : b);
    } else {
        int lo = randomHeight(1, 80);
        int hi = randomHeight(lo, 220);
        for (int i = 0; i < n; ++i) h[i] = randomHeight(lo, hi);
    }

    clampHeights(h);

    println(n);
    println(h);

    return 0;
}
