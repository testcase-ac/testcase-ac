#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0 ? rnd.next(1, 5) : rnd.next(6, 30));
    vector<int> a(n);

    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 50)));
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int start = rnd.next(1, 100);
        int step = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) a[i] = min(1000000, start + i * step);
    } else if (mode == 2) {
        int start = rnd.next(900000, 1000000);
        int step = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) a[i] = max(1, start - i * step);
    } else if (mode == 3) {
        int low = rnd.next(1, 10);
        int high = rnd.next(999990, 1000000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? low + rnd.next(0, 3) : high - rnd.next(0, 3));
        }
    } else if (mode == 4) {
        int value = rnd.next(1, 1000000);
        for (int i = 0; i < n;) {
            value = max(1, min(1000000, value + rnd.next(-20, 20)));
            int len = min(n - i, rnd.next(1, 5));
            for (int j = 0; j < len; ++j) a[i + j] = value;
            i += len;
        }
    } else if (mode == 5) {
        int base = rnd.next(1, 1000000);
        for (int& x : a) x = base;
        int changes = rnd.next(1, max(1, n / 3));
        for (int k = 0; k < changes; ++k) {
            int idx = rnd.next(0, n - 1);
            a[idx] = rnd.next(1, 1000000);
        }
    } else {
        int lo = rnd.next(1, 999900);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(20, 200)));
        for (int& x : a) x = rnd.next(lo, hi);
        if (rnd.next(0, 1)) sort(a.begin(), a.end());
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
