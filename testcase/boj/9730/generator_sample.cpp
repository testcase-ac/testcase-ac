#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        int lo = rnd.next(1, 30);
        int hi = rnd.next(lo, min(100000, lo + 40));
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 12);
            a[i] = min(cur, 100000);
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 20) + 12 * n;
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 12);
            a[i] = max(1, cur);
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 12);
        int high = rnd.next(50, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(low, min(100000, low + 8))
                                : rnd.next(max(1, high - 20), high);
        }
    } else if (mode == 4) {
        int peak = rnd.next(20, 100000);
        int base = rnd.next(1, min(peak, 30));
        int pivot = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int dist = abs(i - pivot);
            a[i] = max(1, peak - dist * rnd.next(1, 15));
            if (rnd.next(4) == 0) a[i] = rnd.next(base, min(100000, base + 10));
        }
    } else {
        vector<int> pool;
        int count = rnd.next(2, 5);
        for (int i = 0; i < count; ++i) pool.push_back(rnd.next(1, 100000));
        for (int& x : a) x = rnd.any(pool);
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 5);
        int n;
        if (tc == 0) {
            n = 2;
        } else if (rnd.next(5) == 0) {
            n = rnd.next(20, 40);
        } else {
            n = rnd.next(3, 14);
        }

        vector<int> a = makeCase(n, mode);
        println(n);
        println(a);
    }

    return 0;
}
