#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n = 1;
    if (mode == 8) {
        n = rnd.next(40, 120);
    } else if (mode == 0) {
        n = 1;
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = rnd.next(0, 1);
    } else if (mode == 1) {
        int value = rnd.next(0, n);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        int cur = rnd.next(0, min(n, 3));
        for (int i = 0; i < n; ++i) {
            cur = rnd.next(cur, n);
            a[i] = cur;
        }
    } else if (mode == 3) {
        int cur = rnd.next(n - min(n, 3), n);
        for (int i = 0; i < n; ++i) {
            cur = rnd.next(0, cur);
            a[i] = cur;
        }
    } else if (mode == 4) {
        int lo = rnd.next(0, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) {
            a[i] = (rnd.next(0, 3) == 0 ? rnd.next(0, n) : rnd.next(lo, hi));
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = (rnd.next(0, 1) == 0 ? 0 : n);
        }
    } else if (mode == 6) {
        int block = rnd.next(1, min(n, 6));
        for (int i = 0; i < n; ++i) {
            int base = (i / block) % (n + 1);
            a[i] = rnd.next(max(0, base - 1), min(n, base + 1));
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else {
        int alphabet = rnd.next(2, min(n + 1, 10));
        vector<int> values;
        for (int i = 0; i < alphabet; ++i) {
            values.push_back(rnd.next(0, n));
        }
        values.push_back(0);
        values.push_back(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(values);
        }
    }

    println(n);
    println(a);

    return 0;
}
