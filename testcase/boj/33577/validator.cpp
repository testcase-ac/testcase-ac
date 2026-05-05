#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of exits
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read A_1..A_N, each in [1, 1e9]
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A");
    inf.readEoln();

    // --- Global property checks implied by the problem text ---

    // From game rules: immunity can never be negative, and starting at 0,
    // we must ensure that there exists some strategy to finish exit N
    // without ever going negative. The statement guarantees that the answer
    // always exists, so the validator must reject inputs where it is impossible.

    // Reasoning: if we skip exit i, immunity += A[i]; if we pass, immunity -= A[i].
    // After k cycles (0-based) of skipping all exits 1..(i-1), immunity at exit i is:
    //   I = k * sum(A[1..i-1]) - A[i]
    // Skipping or passing any exit i never introduces any other restriction
    // except that immediately after any operation, I >= 0.
    //
    // The necessary and sufficient condition for the existence of a valid strategy:
    // There must exist some i where A[i] <= sum(A[1..i-1]).
    // Otherwise, no amount of cycling can ever make immunity high enough to pass
    // exit i (or any such i), since you never get any immunity from exits >= i
    // before passing them for the first time.
    //
    // We check this condition to match the problem's guarantee that an answer exists.

    long long prefixSum = 0;
    long long maxA = 0;
    bool possible = false;
    for (int i = 0; i < N; ++i) {
        if (A[i] <= prefixSum) possible = true;
        prefixSum += A[i];
        if (A[i] > maxA) maxA = A[i];
    }

    // If for all i, A[i] > sum(A[1..i-1]], then no strategy exists.
    ensuref(possible,
            "No valid strategy exists: for all i, A_i > sum_{j < i} A_j "
            "(max A_i = %lld, total sum = %lld)", maxA, prefixSum);

    inf.readEof();
}
