#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: even, 2 <= N <= 36
    int N = inf.readInt(2, 36, "N");
    ensuref(N % 2 == 0, "N must be even, got %d", N);
    inf.readEoln();

    const long long SCORE_MIN = 1LL;
    const long long SCORE_MAX = (long long)1e15;

    // Read scores from leader 1
    vector<long long> a = inf.readLongs(N, SCORE_MIN, SCORE_MAX, "a_i");
    inf.readEoln();

    // Read scores from leader 2
    vector<long long> b = inf.readLongs(N, SCORE_MIN, SCORE_MAX, "b_i");
    inf.readEoln();

    // --- Global property check: there always exists a partition into two teams
    // of equal size (N/2 each) minimizing |sum1 - sum2|; statement guarantees
    // "always" but that's tautologically true, so nothing to check beyond
    // constraints. However, we can at least check that basic sums do not overflow.
    __int128 sumA = 0, sumB = 0;
    for (int i = 0; i < N; ++i) {
        sumA += (__int128)a[i];
        sumB += (__int128)b[i];
    }
    // Ensure they fit in 128-bit range trivially (always true here),
    // but keep as sanity.
    ensuref(sumA >= 0 && sumB >= 0, "Internal sum overflow sanity check failed");

    inf.readEof();
}
