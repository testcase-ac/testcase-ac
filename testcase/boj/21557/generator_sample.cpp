#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(3, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(3, 30);
    }

    vector<long long> a(n);
    long long highBase = rnd.next(1000000000LL - 1000, 1000000000LL);

    if (mode == 0) {
        long long base = rnd.next((long long)n, (long long)n + 10);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(0, 3);
    } else if (mode == 1) {
        long long cur = rnd.next((long long)n, (long long)n + 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 4);
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long cur = rnd.next((long long)n, (long long)n + 20) + 4LL * n;
        for (int i = 0; i < n; ++i) {
            a[i] = max((long long)n, cur);
            cur -= rnd.next(0, 4);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next((long long)n, (long long)n + 30);
        a[0] = highBase - rnd.next(0, 20);
        a[n - 1] = rnd.next((long long)n, (long long)n + 20);
        if (rnd.next(0, 1)) swap(a[0], a[n - 1]);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next((long long)n, (long long)n + 15)
                                : highBase - rnd.next(0, 50);
        }
    } else {
        long long lo = rnd.next((long long)n, (long long)n + 100);
        long long hi = min(1000000000LL, lo + rnd.next(0, 1000));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    println(n);
    println(a);
    return 0;
}
