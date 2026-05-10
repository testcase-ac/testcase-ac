#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Check if all trees can lose all leaves by day D with optimal use of power
bool can(long long D, const vector<long long>& A, const vector<long long>& B) {
    int n = (int)A.size();
    long long need = 0; // total number of days we must use power
    for (int i = 0; i < n; ++i) {
        long long Ai = A[i], Bi = B[i];
        // minimal days without power
        long long t0 = (Ai + Bi - 1) / Bi; // ceil(Ai / Bi)
        if (t0 <= D) continue; // no need for power on this tree
        // need extra leaves removal: t0 - D days' worth of Bi each
        long long diff_days = t0 - D;
        // each power day gives extra Bi removal, so exactly diff_days days of power needed
        need += diff_days;
        if (need > D) return false; // early prune: can't use power more than D days total
    }
    return need <= D;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<long long> A(N), B(N);
    {
        vector<long long> tmp = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
        for (int i = 0; i < N; ++i) A[i] = tmp[i];
        inf.readEoln();
    }
    {
        vector<long long> tmp = inf.readLongs(N, 1LL, 1000000000LL, "B_i");
        for (int i = 0; i < N; ++i) B[i] = tmp[i];
        inf.readEoln();
    }

    // Global property: answer (earliest day) must exist and be finite.
    // We verify by actually computing minimal D using binary search.
    long long low = 1, high = 0;
    for (int i = 0; i < N; ++i) {
        // Worst case: never using power on this tree
        long long t0 = (A[i] + B[i] - 1) / B[i];
        if (t0 > high) high = t0;
    }
    // high is an upper bound; with using power, answer can only be smaller,
    // so [1, high] always contains some feasible D.
    long long ans = high;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (can(mid, A, B)) {
            ans = mid;
            high = mid - 1;
        } else low = mid + 1;
    }
    // Ensure feasibility (should always hold under given constraints)
    ensuref(can(ans, A, B),
            "Global property violated: no feasible day D found for given A, B");

    inf.readEof();
}
