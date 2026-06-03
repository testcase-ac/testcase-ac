#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        long long hi = rnd.next(1, 20);
        a.resize(n);
        for (long long& x : a) x = rnd.next(1LL, hi);
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        a.assign(n, rnd.next(1LL, 8LL));
        int center = rnd.next(1, n - 2);
        a[center] = rnd.next(20LL, 100LL);
        a[center - 1] = rnd.next(1LL, 1000000000LL);
        a[center + 1] = rnd.next(1LL, 1000000000LL);
    } else if (mode == 2) {
        n = rnd.next(3, 25);
        a.resize(n);
        long long low = rnd.next(1LL, 5LL);
        long long high = rnd.next(999999900LL, 1000000000LL);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? high : low);
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        long long base = rnd.next(1LL, 1000LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            long long delta = rnd.next(0LL, 10LL);
            a[i] = min(1000000000LL, base + i * rnd.next(0LL, 3LL) + delta);
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        n = rnd.next(3, 40);
        a.resize(n);
        long long left = rnd.next(1LL, 1000000000LL);
        long long right = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                a[i] = left;
            } else if (i == n - 1) {
                a[i] = right;
            } else {
                a[i] = rnd.next(1LL, min(left, right));
            }
        }
    } else {
        n = rnd.next(50, 120);
        a.resize(n);
        long long lo = rnd.next(1LL, 1000000LL);
        long long hi = rnd.next(lo, 1000000000LL);
        for (long long& x : a) x = rnd.next(lo, hi);
    }

    println(n);
    println(a);
    return 0;
}
