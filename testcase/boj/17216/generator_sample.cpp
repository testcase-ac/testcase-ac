#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, mode == 6 ? 40 : 18);
    vector<int> a(n);

    if (mode == 0) {
        int cur = rnd.next(n, 1000);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = max(1, cur - rnd.next(1, 20));
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, max(1, 1000 - n));
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = min(1000, cur + rnd.next(1, 20));
        }
    } else if (mode == 2) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(950, 1000);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) a[i] = rnd.next(hi - 40, hi);
            else a[i] = rnd.next(lo, lo + 40);
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-5, 5);
            a[i] = min(1000, max(1, base + delta));
        }
    } else if (mode == 4) {
        int lo = rnd.next(1, 900);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 99)));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 1000);
    } else {
        int blocks = rnd.next(2, 6);
        int pos = 0;
        for (int b = 0; b < blocks && pos < n; ++b) {
            int len = rnd.next(1, max(1, (n - pos) / (blocks - b)));
            int start = rnd.next(1, 1000);
            int dir = rnd.next(0, 1) ? 1 : -1;
            for (int j = 0; j < len && pos < n; ++j, ++pos) {
                a[pos] = min(1000, max(1, start + dir * j * rnd.next(1, 15)));
            }
        }
        while (pos < n) a[pos++] = rnd.next(1, 1000);
    }

    println(n);
    println(a);
    return 0;
}
