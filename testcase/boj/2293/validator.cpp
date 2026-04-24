#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    // Read coin values, ensure distinctness
    vector<int> coins;
    coins.reserve(n);
    set<int> seen;
    for (int i = 0; i < n; i++) {
        int c = inf.readInt(1, 100000, "c_i");
        inf.readEoln();
        ensuref(!seen.count(c),
                "Duplicate coin value detected at index %d: %d", i, c);
        seen.insert(c);
        coins.push_back(c);
    }

    // Validate the bound on the number of combinations: answer < 2^31
    // Use DP with saturation at 2^31
    const uint64_t LIMIT = (1ULL << 31);
    vector<uint64_t> dp(k+1, 0);
    dp[0] = 1;
    for (int ci : coins) {
        if (ci > k) continue;
        for (int sum = ci; sum <= k; sum++) {
            uint64_t nxt = dp[sum] + dp[sum - ci];
            if (nxt >= LIMIT) nxt = LIMIT;
            dp[sum] = nxt;
        }
    }
    ensuref(dp[k] < LIMIT,
            "Number of combinations for sum k=%d is %llu which is >= 2^31",
            k, (unsigned long long)dp[k]);

    inf.readEof();
    return 0;
}
