#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampPrice(int value) {
    return max(1, min(1000000, value));
}

vector<int> makeTimes(int n, int mode) {
    vector<int> t(n);

    int current = rnd.next(1, mode == 2 ? 1000 : 20);
    for (int i = 0; i < n; ++i) {
        t[i] = current;

        if (i + 1 == n) break;

        int remaining = n - i - 1;
        int maxGap = (1000000 - current - remaining) / remaining;
        int gap;
        if (mode == 0) {
            gap = rnd.next(1, min(maxGap, 5));
        } else if (mode == 1) {
            gap = rnd.next(1, min(maxGap, 50));
        } else {
            gap = rnd.next(max(1, min(maxGap, 1000)), max(1, maxGap));
        }
        current += gap;
    }

    return t;
}

vector<int> makePrices(int n, int mode) {
    vector<int> p(n);

    if (mode == 0) {
        int start = rnd.next(1, 1000000);
        int step = rnd.next(-2000, 2000);
        for (int i = 0; i < n; ++i) {
            p[i] = clampPrice(start + step * i + rnd.next(-3, 3));
        }
    } else if (mode == 1) {
        int low = rnd.next(1, 500000);
        int high = rnd.next(500001, 1000000);
        for (int i = 0; i < n; ++i) {
            p[i] = (i % 2 == 0 ? low : high) + rnd.next(-20, 20);
            p[i] = clampPrice(p[i]);
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            p[i] = clampPrice(base + rnd.next(-5, 5));
        }
    } else if (mode == 3) {
        int base = rnd.next(1000, 999000);
        for (int i = 0; i < n; ++i) p[i] = base;
        int spikes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < spikes; ++i) {
            int at = rnd.next(0, n - 1);
            p[at] = clampPrice(base + rnd.next(-50000, 50000));
        }
    } else {
        p[0] = rnd.next(1, 1000000);
        for (int i = 1; i < n; ++i) {
            p[i] = clampPrice(p[i - 1] + rnd.next(-10000, 10000));
        }
    }

    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode < 7) {
        n = rnd.next(2, 12);
    } else if (sizeMode < 9) {
        n = rnd.next(13, 60);
    } else {
        n = rnd.next(100, 250);
    }

    int timeMode = rnd.next(0, 2);
    int priceMode = rnd.next(0, 4);
    vector<int> t = makeTimes(n, timeMode);
    vector<int> p = makePrices(n, priceMode);

    int deltaMode = rnd.next(0, 5);
    int delta;
    if (deltaMode == 0) {
        delta = 0;
    } else if (deltaMode <= 2) {
        delta = rnd.next(1, 20);
    } else if (deltaMode <= 4) {
        delta = rnd.next(21, 10000);
    } else {
        delta = rnd.next(10001, 1000000);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(t[i], p[i]);
    }
    println(delta);

    return 0;
}
