#include "testlib.h"
#include <vector>
#include <cassert>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int T = inf.readInt(-10000, 10000, "T");
    inf.readEoln();

    // Read array A
    vector<int> A = inf.readInts(N, 1, 100, "A_i");
    inf.readEoln();

    // Check that T is reachable by some sequence of CON operations.
    // It is known that the final value is Σ ε_i * A[i], where ε[1]=+1 and ε[i] = ±1 for i>1.
    // We do a DP over possible sums.
    int S = 0;
    for (int x : A) {
        S += x;
    }
    // DP range will be [-S..S], offset by S
    int width = 2 * S + 1;
    vector<char> dp(width, 0), next_dp(width, 0);
    int offset = S;
    // Initial: only A[0] with +1
    dp[offset + A[0]] = 1;

    for (int i = 1; i < N; i++) {
        int ai = A[i];
        // clear next_dp
        memset(next_dp.data(), 0, width * sizeof(char));
        for (int j = 0; j < width; j++) {
            if (!dp[j]) continue;
            // plus ai
            int p = j + ai;
            if (p >= 0 && p < width) {
                next_dp[p] = 1;
            }
            // minus ai
            int m = j - ai;
            if (m >= 0 && m < width) {
                next_dp[m] = 1;
            }
        }
        dp.swap(next_dp);
    }

    // Check reachability of T
    long idx = offset + (long)T;
    ensuref(idx >= 0 && idx < width,
            "Target T=%d out of reachable sum range [-%d, %d]", T, S, S);
    ensuref(dp[idx],
            "Target T=%d is not reachable from the given sequence A", T);

    inf.readEof();
    return 0;
}
