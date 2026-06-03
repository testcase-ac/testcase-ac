#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 500000;

    int mode = rnd.next(0, 6);
    int n;
    int p;
    vector<int> b;

    if (mode == 0) {
        n = rnd.next(1, 18);
        p = 1;
        b.resize(n);
        for (int i = 0; i < n; ++i) b[i] = i + 1;
    } else if (mode == 1) {
        n = rnd.next(3, 30);
        p = rnd.next(2, min(maxN, n + 5));
        b.assign(n, 1);
        int cur = 1;
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 2) == 0 && cur < n) ++cur;
            b[i] = cur;
        }
    } else if (mode == 2) {
        n = rnd.next(4, 35);
        p = rnd.next(1, min(maxN, n));
        b.assign(n, 1);
        int cur = rnd.next(1, min(n, 3));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0 && cur < n) ++cur;
            b[i] = cur;
        }
        int pos = rnd.next(1, n - 1);
        b[pos] = rnd.next(1, b[pos - 1]);
    } else if (mode == 3) {
        n = rnd.next(5, 40);
        p = rnd.next(1, min(maxN, n + 10));
        b.assign(n, 1);
        int cur = 1;
        for (int i = 0; i < n; ++i) {
            b[i] = cur;
            if (rnd.next(0, 2) == 0 && cur + 1 < n) ++cur;
        }
        int pos = rnd.next(1, n - 1);
        b[pos] = rnd.next(min(n, b[pos - 1] + 2), n);
    } else if (mode == 4) {
        n = rnd.next(1, 25);
        p = rnd.next(n, maxN);
        b.resize(n);
        int value = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) value = rnd.next(1, n);
            b[i] = value;
        }
    } else if (mode == 5) {
        n = rnd.next(20, 120);
        p = rnd.any(vector<int>{1, 2, 3, maxN});
        b.resize(n);
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) b[i] = rnd.next(lo, hi);
    } else {
        n = rnd.next(1, 80);
        p = rnd.next(1, maxN);
        b.resize(n);
        for (int i = 0; i < n; ++i) b[i] = rnd.next(1, n);
    }

    println(n, p);
    println(b);
    return 0;
}
