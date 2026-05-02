#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of distinct stickers
    int N = inf.readInt(1, 32, "N");
    inf.readEoln();

    // Prices: natural numbers (>=1) and <= 30,000,000
    vector<int> price = inf.readInts(N, 1, 30000000, "price_i");
    inf.readEoln();

    // Values: integers 1..30,000,000
    vector<int> value = inf.readInts(N, 1, 30000000, "value_i");
    inf.readEoln();

    // K: 0 <= K <= 1e9
    long long K = inf.readLong(0LL, 1000000000LL, "K");
    inf.readEoln();

    // M: number of stickers currently owned, 0 <= M <= N
    int M = inf.readInt(0, N, "M");
    inf.readEoln();

    vector<int> ownedIdx;
    if (M > 0) {
        ownedIdx = inf.readInts(M, 0, N - 1, "owned_i");
        inf.readEoln();

        // Check no duplicates in owned stickers
        sort(ownedIdx.begin(), ownedIdx.end());
        for (int i = 1; i < M; ++i) {
            ensuref(ownedIdx[i] != ownedIdx[i - 1],
                    "Duplicate owned sticker index %d at positions %d and %d in owned list",
                    ownedIdx[i], i - 1, i);
        }
    }

    // Global property implied by problem:
    // With unlimited buying/selling and finite prices, for sufficiently large initial money
    // any subset of stickers is achievable. Thus it is impossible (answer = -1)
    // iff even owning all stickers cannot reach value >= K.
    long long sumAllValues = 0;
    for (int i = 0; i < N; ++i) {
        sumAllValues += value[i];
    }
    // This doesn't reject inputs; just a sanity check on computation.
    ensuref(sumAllValues >= 0, "Sum of values overflowed or negative");

    // If K > sumAllValues, any correct solution must output -1. We don't need
    // to enforce it further; this just encodes the implied guarantee.

    inf.readEof();
}
