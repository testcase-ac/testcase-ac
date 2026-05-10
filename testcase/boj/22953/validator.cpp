#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute maximum dishes producible in time T given times a[]
long long maxDishesInTime(long long T, const vector<long long> &a) {
    long long total = 0;
    for (long long t : a) {
        total += T / t;
        if (total > (long long)1e18) break; // avoid overflow, large cap
    }
    return total;
}

// Given base times a and C encourages, compute best reduced times b
// under rules: each encourage reduces some a[i] by 1 (not below 1)
vector<long long> bestReducedTimes(const vector<long long> &a, int C) {
    int n = (int)a.size();
    vector<long long> b = a;
    // Greedy: always encourage the current slowest cook (largest b[i] > 1)
    // N <= 10, C <= 5, so simple is fine
    for (int c = 0; c < C; ++c) {
        int idx = -1;
        long long mx = 0;
        for (int i = 0; i < n; ++i) {
            if (b[i] > 1 && b[i] > mx) {
                mx = b[i];
                idx = i;
            }
        }
        if (idx == -1) break; // all are already 1
        b[idx]--;
    }
    return b;
}

// Compute minimal time using best encouragement distribution
long long minimalTime(long long K, const vector<long long> &a, int C) {
    vector<long long> b = bestReducedTimes(a, C);
    long long lo = 0;
    long long hi = 1;
    // find upper bound hi s.t. maxDishesInTime(hi) >= K
    while (maxDishesInTime(hi, b) < K) {
        hi <<= 1;
        // hi can grow big; but K<=1e6, min time per dish >=1, so hi won't exceed 2^20
    }
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (maxDishesInTime(mid, b) >= K) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000LL, "K");
    inf.readSpace();
    int C = inf.readInt(0, 5, "C");
    inf.readEoln();

    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readLong(1LL, 1000000LL, "A_i");
        if (i + 1 < N) inf.readSpace();
        else inf.readEoln();
    }

    // Optional global property check:
    // Problem states the minimal time always exists.
    // With constraints (A_i >=1, K>=1), it's guaranteed mathematically,
    // but we can still compute once to ensure no overflow/logic issues.
    long long ans = minimalTime(K, A, C);
    ensuref(ans >= 0, "Computed minimal time must be non-negative");

    inf.readEof();
}
