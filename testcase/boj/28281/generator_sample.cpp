#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0) ? 2 : rnd.next(3, 20);

    int x;
    if (rnd.next(0, 4) == 0) {
        x = rnd.any(vector<int>{1, 2, 999999, 1000000});
    } else {
        x = rnd.next(1, 1000000);
    }

    vector<int> a(n);

    if (mode == 0) {
        a[0] = rnd.any(vector<int>{1, 2, 999, 1000});
        a[1] = rnd.any(vector<int>{1, 2, 999, 1000});
    } else if (mode == 1) {
        int value = rnd.next(1, 1000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 1000);
        }
        int pos = rnd.next(0, n - 2);
        a[pos] = rnd.next(1, 5);
        a[pos + 1] = rnd.next(1, 5);
    } else if (mode == 3) {
        int start = rnd.next(1, 1000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i;
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(1, 20) : rnd.next(900, 1000);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{1, 2, 999, 1000});
        }
    } else {
        int lo = rnd.next(1, 800);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 200)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    }

    println(n, x);
    println(a);

    return 0;
}
