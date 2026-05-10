#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Simulate whether it is possible to make all elements equal using the Add operation,
// and (optionally) compute the minimal number of operations.
// We only need feasibility to enforce the statement guarantee that the answer always exists.
// However, the statement also guarantees that the minimal number of operations <= 1e25,
// so we check that as well.
static const long long MAX_A = 1000000000LL;
static const __int128 MAX_ANS = (__int128)100000000000000000000000LL; // 1e23 just as safe upper;
// but we will compare with 1e25 exactly using explicit constant.
static const __int128 LIMIT_ANS = (__int128)10000000000000000000000000LL; // 1e25

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(1LL, MAX_A, "A_i");
        inf.readEoln();
    }

    // --- Additional semantic validation based on problem statement ---

    // Check that it's always possible to make all equal and that minimal operations <= 1e25.
    // Analysis:
    // Operation Add(i): choose index i, then consider the maximal contiguous segment of equal
    // values containing i (i.e., j..k where all A[j..k] are equal and either j==1 or A[j-1]!=A[j],
    // either k==n or A[k+1]!=A[k]). Then increment all A[j..k] by 1.
    //
    // Observations:
    // - Operation only increases values.
    // - Therefore any final common value T must be >= max(A).
    // - For a fixed target T, one natural strategy is dynamic programming / greedy on segments.
    //
    // However, deriving and implementing a full optimal algorithm is unnecessary for the
    // validator; we just need to *somehow* compute the exact minimal number and verify it
    // is <= 1e25. But doing a potentially O(T) simulation is impossible because T can be huge.
    //
    // Instead, we use a known characterization:
    // Let diff[i] = A[i+1] - A[i]. Consider total increase needed per position relative to
    // final value T: x[i] = T - A[i] (nonnegative integers). Each operation on a segment
    // [l..r] adds 1 to all x[l..r] simultaneously when viewed in reverse (we start from 0 and
    // "build" x). This is precisely a standard "range increment, minimize number of ops"
    // problem: minimal operations = sum over i of positive part of (x[i] - x[i-1]),
    // with x[0] = 0.
    //
    // So for any T, minimal operations:
    // ops(T) = sum_{i=1..n} max(0, x[i] - x[i-1]), x[i] = T - A[i], x[0] = 0
    //        = sum_{i=1..n} max(0, (T - A[i]) - (T - A[i-1])) with A[0] := T
    //        = sum_{i=1..n} max(0, A[i-1] - A[i]), with A[0] = T.
    // For i=1: term = max(0, T - A[1]) = T - A[1] (since T>=max(A) >= A[1]).
    // For i>=2: term = max(0, A[i-1] - A[i]), depends only on original A, not T.
    //
    // Thus ops(T) = (T - A[1]) + C, where C = sum_{i=2..n} max(0, A[i-1] - A[i]).
    // To also satisfy x[n] = T - A[n] (nonnegative) there is no extra constraint beyond T>=max(A).
    // However, we must ensure that there exists a sequence of segment-operations matching such x.
    // The standard reasoning for "build array with minimal range increments" *does* guarantee
    // feasibility; operations of the form "increment any contiguous segment" are enough.
    //
    // Therefore:
    // - It is *always* possible to reach equality for any T >= max(A).
    // - Minimal operations over all valid T (>=max(A)) is attained at smallest T, i.e. T = max(A).
    //
    // So the minimal operation count is:
    //   T = M := max(A[i])
    //   ans = (M - A[1]) + sum_{i=2..n} max(0, A[i-1] - A[i])
    //
    // We'll compute this value with __int128 and verify it <= 1e25 as per statement.

    long long M = *max_element(a.begin(), a.end());
    __int128 ans = 0;
    ans += (__int128)M - (__int128)a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i-1] > a[i]) {
            ans += (__int128)a[i-1] - (__int128)a[i];
        }
    }

    // Check non-negativity (should always hold)
    ensuref(ans >= 0, "Computed minimal operations negative, internal contradiction.");

    // Check against stated upper bound 1e25.
    ensuref(ans <= LIMIT_ANS,
            "Minimal number of Add operations exceeds 1e25 as forbidden by statement.");

    inf.readEof();
}
