#include "testlib.h"
using namespace std;

long long genK(const vector<int>& a) {
    long long tot = 0;
    int mn = 1000000000;
    int mx = 0;
    for (int x : a) {
        tot += x;
        if (x < mn) mn = x;
        if (x > mx) mx = x;
    }

    vector<long long> ks;
    ks.push_back(1LL);
    ks.push_back((long long)mn);
    ks.push_back((long long)mx);
    ks.push_back(tot);
    if (tot > 1) ks.push_back(tot - 1);
    ks.push_back(max(1LL, tot / 2));
    ks.push_back(1000000000LL);

    int attempts = min(3, (int)a.size());
    for (int it = 0; it < attempts; ++it) {
        int l = rnd.next(0, (int)a.size() - 1);
        int r = rnd.next(l, (int)a.size() - 1);
        long long s = 0;
        for (int i = l; i <= r; ++i) s += a[i];
        ks.push_back(s);
        if (s > 1) ks.push_back(s - 1);
        if (s < 1000000000LL) ks.push_back(s + 1);
    }

    return rnd.any(ks);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 10);
    int n;
    vector<int> a;
    long long k;

    if (mode == 1) {
        // Single element edge cases
        n = 1;
        a.resize(1);
        a[0] = rnd.next(1, 20);
        vector<long long> ks;
        ks.push_back(1LL);
        ks.push_back((long long)a[0]);
        if (a[0] > 1) ks.push_back((long long)a[0] - 1);
        ks.push_back((long long)a[0] + 1);
        ks.push_back(1000000000LL);
        k = rnd.any(ks);
    } else if (mode == 2) {
        // Very small n, all ones
        n = rnd.next(2, 5);
        a.assign(n, 1);
        if (rnd.next(0, 1) == 0) {
            vector<long long> ks;
            ks.push_back(1LL);
            ks.push_back(2LL);
            ks.push_back((long long)n);
            ks.push_back((long long)n + 1);
            k = rnd.any(ks);
        } else {
            k = genK(a);
        }
    } else if (mode == 3) {
        // Small/medium n, all ones
        n = rnd.next(6, 15);
        a.assign(n, 1);
        k = genK(a);
    } else if (mode == 4) {
        // Random small values
        n = rnd.next(2, 40);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 10);
        k = genK(a);
    } else if (mode == 5) {
        // Random large values
        n = rnd.next(2, 40);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(50000, 100000);
        k = genK(a);
    } else if (mode == 6) {
        // Non-decreasing sequence with small increments
        n = rnd.next(5, 25);
        a.resize(n);
        a[0] = rnd.next(1, 5);
        for (int i = 1; i < n; ++i) {
            int delta = rnd.next(0, 5);
            a[i] = a[i - 1] + delta;
            if (a[i] > 100000) a[i] = 100000;
        }
        k = genK(a);
    } else if (mode == 7) {
        // Decreasing sequence
        n = rnd.next(5, 25);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 100000);
        sort(a.begin(), a.end(), greater<int>());
        k = genK(a);
    } else if (mode == 8) {
        // Alternating small and big
        n = rnd.next(5, 30);
        int small = rnd.next(1, 10);
        int big = rnd.next(50000, 100000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? small : big;
        }
        k = genK(a);
    } else if (mode == 9) {
        // Geometric-like growth (powers of ~2)
        n = rnd.next(5, 20);
        a.resize(n);
        long long cur = 1 + rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            if (cur > 100000) cur = 100000;
            a[i] = (int)cur;
            cur *= 2;
        }
        k = genK(a);
    } else { // mode == 10
        // Fully random within allowed range
        n = rnd.next(1, 40);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 100000);
        k = genK(a);
    }

    println(n);
    println(a);
    println(k);

    return 0;
}
