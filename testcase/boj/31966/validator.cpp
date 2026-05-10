#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> A(N + 1), B(N + 1);

    for (int i = 1; i <= N; ++i) {
        setTestCase(i);

        A[i] = inf.readInt(0, i - 1, "A_i");
        inf.readSpace();
        B[i] = inf.readInt(0, i - 1, "B_i");
        inf.readEoln();
    }

    // Global property check: for each i, T_i is a well-defined full binary tree,
    // and the sum of sizes of all T_i does not exceed what the statement allows
    // in subtasks 4 and 5. Here we compute the exact sizes and ensure no overflow.

    // size[i] = number of nodes in tree T_i
    vector<long long> sz(N + 1, 0);
    sz[0] = 1; // T_0 has exactly one node

    for (int i = 1; i <= N; ++i) {
        long long leftSize  = sz[A[i]];
        long long rightSize = sz[B[i]];

        // Every referenced T_j, j < i, must already be computed
        ensuref(A[i] >= 0 && A[i] < i, "Invalid A_%d = %d (must be in [0, %d])",
                i, A[i], i - 1);
        ensuref(B[i] >= 0 && B[i] < i, "Invalid B_%d = %d (must be in [0, %d])",
                i, B[i], i - 1);

        // Each T_i is made of a new root plus T_{A_i} and T_{B_i}
        // Use __int128 to avoid overflow on intermediate sum
        __int128 cur = 1;
        cur += leftSize;
        cur += rightSize;
        ensuref(cur <= ( (__int128)1 << 60 ),
                "Tree size overflow at T_%d (size too large)", i);
        sz[i] = (long long)cur;
    }

    // Additional holistic cross-checks for subtasks (non-strict in main constraints,
    // but we can at least ensure node counts are consistent and reasonably bounded)

    long long sumNodes = 0;
    for (int i = 1; i <= N; ++i) {
        sumNodes += sz[i];
        ensuref(sumNodes >= 0, "Sum of node counts overflow (prefix at i=%d)", i);
    }
    // The statement gives explicit smaller bounds for some subtasks, but the full
    // task has no extra limit beyond what we already used to avoid overflow.
    // We don't enforce subtask-specific bounds here, as those are for scoring,
    // not validity. We just check that sizes were computable within 2^60.

    inf.readEof();
}
