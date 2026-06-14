#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    vector<int> w;

    if (mode == 0) {
        n = rnd.next(2, 12);
        int lo = rnd.next(1, 30);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 200)));
        w.resize(n);
        for (int& x : w) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        int value = rnd.next(1, 10000);
        w.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 35);
        int cur = rnd.next(1, 200);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            cur = min(10000, cur + rnd.next(0, 80));
            w[i] = cur;
        }
        if (rnd.next(2) == 0) reverse(w.begin(), w.end());
    } else if (mode == 3) {
        n = rnd.next(4, 40);
        int low = rnd.next(1, 20);
        int high = rnd.next(5000, 10000);
        w.resize(n);
        for (int i = 0; i < n; ++i) {
            w[i] = (i % 2 == 0 ? low + rnd.next(0, 20) : high - rnd.next(0, 200));
            w[i] = max(1, min(10000, w[i]));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 45);
        w.assign(n, rnd.next(1, 50));
        int spikes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < spikes; ++i) {
            w[rnd.next(n)] = rnd.next(1000, 10000);
        }
    } else if (mode == 5) {
        n = rnd.next(6, 60);
        w.resize(n);
        int base = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            int block = i / rnd.next(2, 6);
            w[i] = min(10000, base + block * rnd.next(1, 40) + rnd.next(0, 5));
        }
    } else if (mode == 6) {
        n = rnd.next(80, 180);
        w.resize(n);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, 10000);
        for (int& x : w) x = rnd.next(lo, hi);
    } else {
        n = rnd.next(1500, 2000);
        w.resize(n);
        int base = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-20, 20);
            w[i] = max(1, min(10000, base + delta));
        }
    }

    println(n);
    println(w);
    return 0;
}
