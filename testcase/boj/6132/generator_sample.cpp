#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampHeight(int value) {
    return max(1, min(100, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(2, 15);
    }
    int c = rnd.next(1, 100);

    vector<int> h(n);
    if (mode == 0) {
        h[0] = rnd.next(1, 100);
    } else if (mode == 1) {
        int base = rnd.next(1, 100);
        int spread = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            h[i] = clampHeight(base + rnd.next(-spread, spread));
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 30);
        int high = rnd.next(70, 100);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0 ? low : high) + rnd.next(-3, 3);
            h[i] = clampHeight(h[i]);
        }
    } else if (mode == 3) {
        int cur = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 8);
            h[i] = clampHeight(cur);
        }
        if (rnd.next(0, 1)) {
            reverse(h.begin(), h.end());
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 100);
        }
    } else {
        int first = rnd.next(1, 100);
        int second = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int base = (i < n / 2 ? first : second);
            h[i] = clampHeight(base + rnd.next(-10, 10));
        }
    }

    println(n, c);
    for (int value : h) {
        println(value);
    }

    return 0;
}
