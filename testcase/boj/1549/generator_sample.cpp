#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static long long bounded(long long value) {
    return max(0LL, min(1000000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = 2;
        long long x = rnd.next(0, 1000000000);
        a = {x, rnd.next(0, 1) ? x : rnd.next(0, 1000000000)};
    } else if (mode == 1) {
        n = rnd.next(3, 18);
        long long x = rnd.next(0, 1000000000);
        a.assign(n, x);
    } else if (mode == 2) {
        n = rnd.next(4, 32);
        if (n % 2 == 1 && rnd.next(0, 1)) --n;
        int block = rnd.next(1, max(1, n / 2));
        vector<long long> pattern(block);
        for (long long& x : pattern) x = rnd.next(0, 1000000000);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = pattern[i % block];
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        long long cur = rnd.next(0, 1000);
        long long step = rnd.next(0, 1000000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cur = bounded(cur + step + rnd.next(0, 25));
            a[i] = cur;
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) a[i] = rnd.next(999999990, 1000000000);
            else if (i % 3 == 1) a[i] = rnd.next(0, 10);
            else a[i] = rnd.next(0, 1000000000);
        }
    } else if (mode == 5) {
        n = rnd.next(8, 44);
        a.resize(n);
        long long base = rnd.next(0, 1000000000);
        for (int i = 0; i < n; ++i) {
            long long delta = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 1000);
            a[i] = bounded(base + delta);
        }
    } else if (mode == 6) {
        n = rnd.next(10, 50);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 2000);
        int len = rnd.next(1, n / 2);
        int left = rnd.next(0, n - 2 * len);
        int right = rnd.next(left + len, n - len);
        long long target = 0;
        for (int i = 0; i < len; ++i) target += a[left + i];
        long long cur = 0;
        for (int i = 0; i + 1 < len; ++i) cur += a[right + i];
        a[right + len - 1] = bounded(target - cur + rnd.next(-3, 3));
    } else {
        n = rnd.next(0, 4) == 0 ? 3000 : rnd.next(60, 120);
        a.resize(n);
        long long hi = rnd.next(1000, 1000000000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0LL, hi);
    }

    println(n);
    println(a);
    return 0;
}
