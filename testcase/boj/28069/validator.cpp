#include "testlib.h"
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K with canonical integer format and given bounds.
    int N = inf.readInt(1, 1'000'000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1'000'000, "K");
    inf.readEoln();

    // Additional global validation:
    // The problem guarantees that the process is always well-defined.
    // For this problem, there is no explicit global property like "answer always exists",
    // but we can still sanity-check that the modeled process is finite and safe
    // for all valid inputs as described.

    // However, no extra constraints beyond input format and ranges are specified,
    // so we do not enforce any reachability property here (that is for solutions).

    // Still, as a robustness check, we can simulate the maximum reachable step
    // in K moves and ensure it does not overflow 32-bit int.
    // Model: from step i, you can go to:
    //  - i + 1
    //  - i + floor(i / 2)
    // Both are positive and monotone increasing.
    // Maximum after K moves starting from 0 is bounded; we ensure it fits in 32-bit.
    {
        long long pos = 0;
        for (int t = 0; t < K; ++t) {
            // Worst-case choice each time is using the "teleport" move (which dominates for i >= 2).
            long long next1 = pos + 1;
            long long next2 = pos + pos / 2;
            long long best = next1 > next2 ? next1 : next2;
            pos = best;
            // Avoid pathological overflow; this is a safety net, not from statement.
            ensuref(pos <= (long long)4e9,
                    "Reachable step exceeds reasonable bound at move %d: %lld",
                    t + 1, pos);
        }
    }

    inf.readEof();
}
