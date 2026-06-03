#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int k = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        k = 1;
        a = {rnd.next(1, 100000)};
    } else {
        n = rnd.next(2, 30);
        if (mode == 1) {
            k = rnd.next(1, min(n, 3));
        } else if (mode == 2) {
            k = n;
        } else {
            k = rnd.next(1, n);
        }

        a.resize(n);
        if (mode == 1) {
            int base = rnd.next(1, 12);
            for (int i = 0; i < n; ++i) a[i] = base;
        } else if (mode == 2) {
            int low = rnd.next(1, 20);
            int step = rnd.next(0, 5);
            for (int i = 0; i < n; ++i) a[i] = min(100000, low + i * step);
        } else if (mode == 3) {
            int high = rnd.next(99950, 100000);
            int step = rnd.next(0, 5);
            for (int i = 0; i < n; ++i) a[i] = max(1, high - i * step);
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                a[i] = (i % 2 == 0) ? rnd.next(99990, 100000) : rnd.next(1, 10);
            }
        } else if (mode == 5) {
            int lo = rnd.next(1, 99980);
            int hi = min(100000, lo + rnd.next(0, 20));
            for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
        } else {
            for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 100000);
            if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
        }
    }

    println(n, k);
    println(a);

    return 0;
}
