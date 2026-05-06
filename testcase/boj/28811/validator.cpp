#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute best rectangle (x <= y, x,y >= 2, x*y = n2p1) with maximal perimeter.
// Return pair<bool, pair<long long,long long>>:
//   first = false  -> no such rectangle
//   first = true   -> second = (x,y)
pair<bool, pair<long long,long long>> bestRectangle(long long v) {
    // v = n^2 + 1, up to (1e6)^2+1 = 1e12+1 fits in 64-bit
    long long bestP = -1;
    long long bestX = -1, bestY = -1;

    // factor search up to sqrt(v)
    long long r = sqrtl((long double)v);
    while ((r + 1) * (r + 1) <= v) ++r;
    while (r * r > v) --r;

    for (long long x = 2; x <= r; ++x) {
        if (v % x != 0) continue;
        long long y = v / x;
        if (y < 2) continue;
        long long P = 2 * (x + y);
        if (P > bestP) {
            bestP = P;
            bestX = x;
            bestY = y;
        }
    }

    if (bestP < 0) return {false, {0, 0}};
    if (bestX > bestY) swap(bestX, bestY);
    return {true, {bestX, bestY}};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int Q_MAX = 1000000;
    const int N_MAX = 1000000;

    int q = inf.readInt(1, Q_MAX, "q");
    inf.readEoln();

    // Precompute all answers to validate the promise that answer always
    // either exists or doesn't, and that constraints are consistent.
    // Also cheap enough: q <= 1e6, each v up to ~1e12, simple sqrt-divisor check.

    vector<long long> ns(q);
    for (int i = 0; i < q; ++i) {
        long long n = inf.readLong(1LL, (long long)N_MAX, "n_i");
        ns[i] = n;
        if (i + 1 < q) inf.readEoln();
    }
    inf.readEoln(); // final line after last n_i

    // Global property check: for each n, either a suitable rectangle exists
    // or not; we ensure internally that when our brute-force says no, it
    // truly means no rectangle x,y>=2 with x*y=n^2+1 exists.
    for (int i = 0; i < q; ++i) {
        long long n = ns[i];
        long long v = n * n + 1;
        auto res = bestRectangle(v);
        // Nothing to "ensure" besides correctness of our own logic;
        // we at least verify we didn't overflow:
        ensuref(v > 0, "Overflow on computing n^2+1 for test %d (n=%lld)", i + 1, n);

        if (!res.first) {
            // No rectangle with x,y>=2. This is valid per statement:
            // output -1 is allowed in such case, and there is no extra promise
            // that a rectangle always exists.
            continue;
        }
        long long x = res.second.first;
        long long y = res.second.second;

        ensuref(x >= 2 && y >= 2, "Found invalid rectangle with side < 2 at test %d", i + 1);
        ensuref(x <= y, "Internal rectangle ordering violated at test %d", i + 1);
        ensuref(x * y == v, "Internal rectangle area mismatch at test %d", i + 1);
    }

    inf.readEof();
}
