#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> c(N);
    vector<int> cnt(N + 1, 0);

    for (int i = 0; i < N; ++i) {
        c[i] = inf.readInt(1, N, "c_i");
        inf.readEoln();
        cnt[c[i]]++;
    }

    // Check that c[1..N] is a permutation of 1..N
    for (int v = 1; v <= N; ++v) {
        ensuref(cnt[v] == 1, "c_i values must form a permutation of 1..N; value %d appears %d times", v, cnt[v]);
    }

    // ---- Global property: existence of an acceptable final lineup ----
    // Acceptable lineup is some rotation of 1..N (cyclic order) because:
    // constraints: for all i from 1..N-1: cow i must be left of cow i+1,
    // and cow N must be left of cow 1. This is exactly the cyclic order 1..N.
    //
    // Starting from any permutation, we can obtain any other permutation via
    // adjacent swaps, so an acceptable lineup always exists. Still, we
    // compute the minimal number of adjacent swaps to verify that it fits
    // in 64-bit signed integer (important for some problems).
    //
    // We do the following:
    // For each rotation r (0..N-1), consider final order:
    //   final[r][k] = ((r + k) % N) + 1, k=0..N-1
    // We map current positions of each cow and compute inversions between
    // current positions for that final order. We ensure that minimal swaps
    // fit in 64-bit.

    vector<int> pos(N + 1);
    for (int i = 0; i < N; ++i) pos[c[i]] = i;

    // Fenwick tree for inversion counting
    struct Fenwick {
        int n;
        vector<long long> bit;
        Fenwick(int n = 0) { init(n); }
        void init(int n_) { n = n_; bit.assign(n + 1, 0); }
        void add(int idx, long long val) {
            for (++idx; idx <= n; idx += idx & -idx) bit[idx] += val;
        }
        long long sumPrefix(int idx) {
            long long r = 0;
            for (++idx; idx > 0; idx -= idx & -idx) r += bit[idx];
            return r;
        }
    };

    long long best = (long long)N * (N - 1) / 2; // upper bound on inversions
    // if N is large, this is <= ~5e9, fits in 32-bit signed, but we use 64-bit

    Fenwick fw(N);

    for (int r = 0; r < N; ++r) {
        fw.init(N);
        long long inv = 0;
        for (int k = 0; k < N; ++k) {
            int cow = (r + k) % N + 1;
            int p = pos[cow];
            long long seen = fw.sumPrefix(p);
            inv += k - seen;          // number of previous elements greater than p
            fw.add(p, 1);
        }
        if (inv < best) best = inv;
    }

    // Ensure inversion count (minimal time) is within 64-bit range.
    ensuref(best >= 0, "Computed minimal time is negative, which is impossible");
    // Upper bound: N*(N-1)/2 already in 64-bit safe range for N<=100000
    ensuref(best <= (long long)N * (N - 1) / 2,
            "Computed minimal time exceeds theoretical max inversions");

    inf.readEof();
}
