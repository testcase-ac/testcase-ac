#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(3, 10);
    vector<int> w(n);

    if (mode == 0) {
        int lo = rnd.next(1, 40);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 120)));
        for (int& x : w) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        for (int& x : w) x = rnd.next(1, 12);
        int highCount = rnd.next(1, max(1, n / 2));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < highCount; ++i) w[pos[i]] = rnd.next(700, 1000);
    } else if (mode == 2) {
        w[0] = rnd.next(600, 1000);
        w[n - 1] = rnd.next(600, 1000);
        for (int i = 1; i + 1 < n; ++i) w[i] = rnd.next(1, 30);
    } else if (mode == 3) {
        int base = rnd.next(1, 80);
        int step = rnd.next(1, max(1, (1000 - base) / max(1, n - 1)));
        for (int i = 0; i < n; ++i) w[i] = min(1000, base + i * step);
        if (rnd.next(0, 1)) reverse(w.begin(), w.end());
    } else if (mode == 4) {
        int low = rnd.next(1, 20);
        int high = rnd.next(100, 1000);
        for (int i = 0; i < n; ++i) w[i] = (i % 2 == 0) ? high : low;
        if (rnd.next(0, 1)) reverse(w.begin(), w.end());
    } else if (mode == 5) {
        int value = rnd.next(1, 1000);
        fill(w.begin(), w.end(), value);
        int tweaks = rnd.next(0, n / 2);
        for (int i = 0; i < tweaks; ++i) w[rnd.next(0, n - 1)] = rnd.next(1, 1000);
    } else {
        n = rnd.next(3, 5);
        w.assign(n, 1);
        for (int& x : w) x = rnd.next(1, 1000);
    }

    println(n);
    println(w);
    return 0;
}
