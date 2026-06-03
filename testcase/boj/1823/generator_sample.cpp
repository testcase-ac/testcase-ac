#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 20);
    vector<int> values(n);

    if (mode == 0) {
        n = rnd.next(1, 3);
        values.assign(n, 0);
        for (int& x : values) {
            x = rnd.next(1, 1000);
        }
    } else if (mode == 1) {
        n = rnd.next(4, 25);
        values.assign(n, 0);
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 200)));
        for (int& x : values) {
            x = rnd.next(lo, hi);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        int start = rnd.next(1, 120);
        int step = rnd.next(0, max(1, (1000 - start) / max(1, n - 1)));
        values.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            values[i] = min(1000, start + i * step);
        }
        if (rnd.next(0, 1)) {
            reverse(values.begin(), values.end());
        }
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        int low = rnd.next(1, 30);
        int high = rnd.next(600, 1000);
        values.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            values[i] = (i % 2 == 0) ? high : low;
        }
        if (rnd.next(0, 1)) {
            reverse(values.begin(), values.end());
        }
    } else if (mode == 4) {
        n = rnd.next(5, 30);
        int base = rnd.next(1, 1000);
        values.assign(n, base);
        int tweaks = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < tweaks; ++i) {
            values[rnd.next(0, n - 1)] = rnd.next(1, 1000);
        }
    } else if (mode == 5) {
        n = rnd.next(6, 40);
        values.assign(n, 0);
        values[0] = rnd.next(700, 1000);
        values[n - 1] = rnd.next(700, 1000);
        for (int i = 1; i + 1 < n; ++i) {
            values[i] = rnd.next(1, 80);
        }
        if (rnd.next(0, 1)) {
            reverse(values.begin(), values.end());
        }
    } else {
        n = rnd.next(40, 80);
        values.assign(n, 0);
        int bandLo = rnd.next(1, 500);
        int bandHi = rnd.next(bandLo, min(1000, bandLo + rnd.next(50, 500)));
        for (int& x : values) {
            x = rnd.next(bandLo, bandHi);
        }
    }

    println(n);
    for (int x : values) {
        println(x);
    }

    return 0;
}
