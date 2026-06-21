#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampValue(long long x) {
    return (int)min(1000000LL, max(0LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> edgeValues = {0, 1, 999999, 1000000};
    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    int u = rnd.next(1, 25);
    int d = rnd.next(1, 25);
    vector<int> a, b;

    if (mode == 0) {
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 3);
        d = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 20);
            a[i] = base;
            b[i] = base;
        }
    } else if (mode == 1) {
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 8);
        d = rnd.next(1, 8);
        int step = u + d;
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 60);
            int k = rnd.next(0, min(6, n));
            int delta = k * step + rnd.next(-2, 2);
            if (rnd.next(0, 1) == 0) {
                a[i] = base;
                b[i] = clampValue((long long)base + delta);
            } else {
                b[i] = base;
                a[i] = clampValue((long long)base + delta);
            }
        }
    } else if (mode == 2) {
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 1000000);
        d = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(edgeValues);
            b[i] = rnd.any(edgeValues);
        }
    } else if (mode == 3) {
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 40);
        d = rnd.next(1, 40);
        int curA = rnd.next(0, 80);
        int curB = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            curA += rnd.next(0, 9);
            curB += rnd.next(0, 9);
            a[i] = curA;
            b[i] = curB;
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
        if (rnd.next(0, 1)) {
            reverse(b.begin(), b.end());
        }
    } else if (mode == 4) {
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 10);
        d = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int low = rnd.next(0, 40);
            int high = rnd.next(60, 140);
            if (i % 2 == 0) {
                a[i] = low;
                b[i] = high;
            } else {
                a[i] = high;
                b[i] = low;
            }
        }
    } else if (mode == 5) {
        n = rnd.next(25, 80);
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 100);
        d = rnd.next(1, 100);
        int lo = rnd.next(0, 500);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 2000)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
    } else {
        n = rnd.next(2, 40);
        a.resize(n);
        b.resize(n);
        u = rnd.next(1, 1000000);
        d = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1000000);
            b[i] = rnd.next(0, 1000000);
        }
    }

    println(n, u, d);
    println(a);
    println(b);
    return 0;
}
