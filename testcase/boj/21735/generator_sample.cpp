#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 10);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 25);
    } else if (mode == 1) {
        m = rnd.next(1, 10);
        n = rnd.next(max(1, m), min(100, 2 * m + 4));
        a.resize(n);
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 12);
            a[i] = cur;
        }
    } else if (mode == 2) {
        m = rnd.next(2, 10);
        n = rnd.next(m + 1, min(100, 2 * m + 8));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(1, 30);
            } else {
                a[i] = rnd.next(500, 3000);
            }
        }
    } else if (mode == 3) {
        m = rnd.next(3, 10);
        n = rnd.next(m, min(100, 3 * m + 8));
        a.assign(n, rnd.next(1, 20));
        int peaks = rnd.next(1, min(n, 4));
        for (int i = 0; i < peaks; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] = rnd.next(10000, 1000000);
        }
    } else if (mode == 4) {
        n = rnd.next(20, 100);
        m = rnd.next(1, 10);
        a.resize(n);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(1000, 1000000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 10);
        int value = rnd.next(1, 1000000);
        a.assign(n, value);
    }

    println(n, m);
    println(a);
    return 0;
}
