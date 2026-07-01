#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 1000000;
    int mode = rnd.next(0, 7);
    int n;
    int t;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        t = rnd.next(1, 1000000);
        a = {rnd.any(vector<int>{1, rnd.next(2, 30), MAXV})};
    } else {
        n = rnd.next(2, 20);
        if (mode == 1) {
            t = rnd.next(1, min(2 * n + 4, 1000000));
        } else if (mode == 2) {
            t = rnd.next(max(1, n - 2), min(4 * n + 10, 1000000));
        } else if (mode == 3) {
            t = rnd.next(500000, 1000000);
        } else {
            t = rnd.next(1, 1000000);
        }

        a.assign(n, 1);
        if (mode == 1) {
            int lo = rnd.next(1, 20);
            int hi = rnd.next(lo, min(MAXV, lo + 200));
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(lo, hi);
            }
        } else if (mode == 2) {
            int cur = rnd.next(1, 30);
            int step = rnd.next(1, 50);
            for (int i = 0; i < n; ++i) {
                a[i] = min(MAXV, cur + i * step + rnd.next(0, step));
            }
            if (rnd.next(0, 1)) {
                reverse(a.begin(), a.end());
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                a[i] = (i % 2 == 0 ? MAXV : rnd.next(1, 5));
            }
        } else if (mode == 4) {
            int base = rnd.next(1, 20);
            int peak = rnd.any(vector<int>{rnd.next(base, min(MAXV, base + 500)), MAXV});
            int pos = rnd.next(0, n - 1);
            for (int i = 0; i < n; ++i) {
                a[i] = base + rnd.next(0, 5);
            }
            a[pos] = peak;
        } else if (mode == 5) {
            int first = rnd.next(1, 100);
            int second = rnd.next(1, 100);
            for (int i = 0; i < n; ++i) {
                a[i] = (i % 2 == 0 ? first : second);
            }
        } else {
            int lo = rnd.any(vector<int>{1, rnd.next(1, 1000), rnd.next(900000, MAXV)});
            int hi = rnd.next(lo, MAXV);
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(lo, hi);
            }
        }
    }

    println(n, t);
    println(a);
    return 0;
}
