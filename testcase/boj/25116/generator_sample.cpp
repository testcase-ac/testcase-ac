#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 7) {
        n = rnd.next(60, 120);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> a(n);
    long long m;

    if (mode == 0) {
        a[0] = rnd.next(0, 1000000000);
        m = rnd.next(1LL, 1000000000000000000LL);
    } else if (mode == 1) {
        fill(a.begin(), a.end(), 0);
        m = rnd.next(1LL, 1000000000000000000LL);
    } else if (mode == 2) {
        int value = rnd.next(999999900, 1000000000);
        fill(a.begin(), a.end(), value);
        long long maxUseful = min(1000000000000000000LL, 1LL * value * n + rnd.next(0, 1000000));
        m = rnd.next(1LL, maxUseful);
    } else if (mode == 3) {
        int base = rnd.next(0, 50);
        int step = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            long long value = base + 1LL * i * step;
            a[i] = (int)min(1000000000LL, value);
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
        m = rnd.next(1LL, 1LL * n * max(1, a[n / 2]) + rnd.next(1, 1000000));
    } else if (mode == 4) {
        fill(a.begin(), a.end(), rnd.next(0, 20));
        int spikes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < spikes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(100000000, 1000000000);
        }
        m = rnd.next(1LL, 1000000000000000000LL);
    } else if (mode == 5) {
        int hi = rnd.next(1, 2000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, hi);
        long long total = 0;
        for (int x : a) total += x;
        m = rnd.next(1LL, max(1LL, total + rnd.next(0, 2000)));
    } else if (mode == 6) {
        int hi = rnd.next(0, 1000000000);
        int lo = rnd.next(0, hi);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
        m = rnd.next(1LL, 1000000000000000000LL);
    } else {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 1000000000);
        long long total = 0;
        for (int x : a) total += x;
        long long upper = min(1000000000000000000LL, max(1LL, total) + rnd.next(0, 1000000000));
        m = rnd.next(1LL, upper);
    }

    long long maxK = 1LL * n * (n + 1) / 2;
    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = maxK;
    } else if (kMode == 2) {
        k = rnd.next(1LL, min(maxK, (long long)n));
    } else {
        k = rnd.next(1LL, maxK);
    }

    println(n, m, k);
    println(a);

    return 0;
}
