#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(25, 60) : rnd.next(3, 18));
    vector<int> r(n);

    if (mode == 0) {
        int value = rnd.next(1, 100);
        fill(r.begin(), r.end(), value);
    } else if (mode == 1) {
        int low = rnd.next(1, 35);
        int high = rnd.next(66, 100);
        for (int i = 0; i < n; ++i) r[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 2) {
        int base = rnd.next(1, 12);
        fill(r.begin(), r.end(), base);
        int spikes = rnd.next(1, min(4, n));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < spikes; ++i) r[pos[i]] = rnd.next(80, 100);
    } else if (mode == 3) {
        int start = rnd.next(1, 30);
        int step = rnd.next(1, max(1, (100 - start) / n));
        for (int i = 0; i < n; ++i) r[i] = min(100, start + i * step);
        if (rnd.next(0, 1)) reverse(r.begin(), r.end());
    } else if (mode == 4) {
        int groups = rnd.next(2, min(6, n));
        for (int i = 0; i < n; ++i) {
            int band = (i * groups) / n;
            int lo = 1 + band * (99 / groups);
            int hi = min(100, lo + rnd.next(4, 20));
            r[i] = rnd.next(lo, hi);
        }
        int shift = rnd.next(0, n - 1);
        rotate(r.begin(), r.begin() + shift, r.end());
    } else {
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) r[i] = rnd.next(lo, hi);
    }

    println(n);
    for (int value : r) println(value);

    return 0;
}
