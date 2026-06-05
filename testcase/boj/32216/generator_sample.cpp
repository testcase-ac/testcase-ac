#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(1, 20);
    }

    int k;
    int t0;
    vector<int> d(n);

    if (mode == 0) {
        k = rnd.next(0, 100);
        t0 = k;
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(0, 12);
        }
    } else if (mode == 1) {
        k = rnd.next(0, 100);
        t0 = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 2 == 0 ? rnd.next(0, 5) : rnd.next(95, 100));
        }
    } else if (mode == 2) {
        k = rnd.any(vector<int>{0, 1, 99, 100});
        t0 = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(0, 100);
        }
    } else if (mode == 3) {
        k = rnd.next(20, 80);
        t0 = rnd.next(max(0, k - 3), min(100, k + 3));
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(0, 6);
        }
    } else if (mode == 4) {
        k = rnd.next(0, 100);
        t0 = rnd.next(0, 100);
        int lo = rnd.next(0, 40);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(lo, hi);
        }
    } else {
        k = rnd.next(0, 100);
        t0 = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(0, 100);
        }
    }

    println(n, k, t0);
    println(d);

    return 0;
}
