#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;

    // First line: N, K, Q
    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int K = inf.readInt(1, 3, "K");
    inf.readSpace();
    int Q = inf.readInt(1, N, "Q");
    inf.readEoln();

    // Second line: A_1..A_N
    vector<int> A = inf.readInts(N, 1, 3, "A_i");
    inf.readEoln();

    // Third line: X_1..X_Q with 1 <= X_1 < ... < X_Q <= N
    vector<int> X(Q);
    if (Q > 0) {
        X = inf.readInts(Q, 1, N, "X_i");
    }
    inf.readEoln();

    // Check strictly increasing X sequence
    for (int i = 1; i < Q; ++i) {
        ensuref(X[i - 1] < X[i],
                "X sequence must be strictly increasing: X[%d]=%d, X[%d]=%d",
                i, X[i - 1], i + 1, X[i]);
    }

    // Global property: For each query prefix, the number of valid intervals
    // (contiguous subarrays within first X_i students that contain no student of grade K)
    // must be well-defined and fits in 64-bit; we check the promised conditions by
    // actually computing these counts and ensuring no overflow / negative issues.

    // Precompute for all prefixes up to N: total number of valid intervals in [1..i]
    // where an interval is "valid" if it does not contain any student with grade K.
    //
    // Strategy:
    // We scan the array, keeping the current length of the ongoing segment that
    // contains no grade K (len). When we see A[i] != K, len++, and we increase
    // current answer for prefix i by len (all intervals ending at i in that segment).
    // When we see A[i] == K, len resets to 0.
    //
    // Answer for prefix i is prefix sum of these increments; each is <= i, so total
    // for full array is <= N*(N+1)/2 <= ~5e9, well within 64-bit.
    vector<long long> prefixAns(N + 1, 0);
    long long len = 0;
    for (int i = 1; i <= N; ++i) {
        if (A[i - 1] == K) {
            len = 0;
        } else {
            len++;
        }
        // number of valid intervals ending exactly at i is len
        long long add = len;
        // defensive overflow check (should never fail under given limits)
        ensuref(add >= 0, "Internal error: negative count at position %d", i);
        __int128 cur = (__int128)prefixAns[i - 1] + add;
        ensuref(cur <= ( (__int128)9e18 ),
                "Count overflow for prefix %d", i);
        prefixAns[i] = (long long)cur;
    }

    // For each query X_j, ensure the requested prefix is within range already enforced,
    // and the precomputed value is non-negative (sanity).
    for (int j = 0; j < Q; ++j) {
        int x = X[j];
        ensuref(x >= 1 && x <= N, "X_%d=%d out of range 1..N", j + 1, x);
        ensuref(prefixAns[x] >= 0, "Negative number of ways for prefix %d", x);
    }

    inf.readEof();
}
