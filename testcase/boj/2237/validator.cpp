#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int T = inf.readInt(-10000, 10000, "T");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, 100, "A_i");
    inf.readEoln();

    const int maxAbs = 10000;
    const int offset = maxAbs;
    vector<char> dp(2 * maxAbs + 1), nextDp(2 * maxAbs + 1);

    if (N == 1) {
        dp[offset + A[0]] = 1;
    } else {
        dp[offset + A[0] - A[1]] = 1;
        for (int i = 2; i < N; ++i) {
            fill(nextDp.begin(), nextDp.end(), 0);
            for (int sum = -maxAbs; sum <= maxAbs; ++sum) {
                if (!dp[offset + sum]) {
                    continue;
                }
                if (sum + A[i] <= maxAbs) {
                    nextDp[offset + sum + A[i]] = 1;
                }
                if (sum - A[i] >= -maxAbs) {
                    nextDp[offset + sum - A[i]] = 1;
                }
            }
            dp.swap(nextDp);
        }
    }

    ensuref(dp[offset + T],
            "Target T=%d is not reachable from the given sequence A", T);

    inf.readEof();
    return 0;
}
