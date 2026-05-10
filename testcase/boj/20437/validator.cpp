#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read string W: lowercase letters only, length 1..10000
        string W = inf.readToken("[a-z]{1,10000}", "W");
        inf.readEoln();
        int n = (int)W.size();

        // Read K: 1 <= K <= |W|
        int K = inf.readInt(1, n, "K");
        inf.readEoln();

        // Now enforce the global property:
        // If no substring exists that contains exactly K copies of some character
        // and starts/ends with that character, the correct answer is -1.
        // The statement guarantees no further special property about existence,
        // so we just precompute to ensure the instance is consistent with the
        // problem's constraints (no extra promises to check).
        //
        // However, to align with the instructions, we verify:
        // - the minimal length result is in [K, n] if it exists
        // - the maximal length result is in [K, n] if it exists
        // - and if no such substring exists then those conceptual answers are -1.
        //
        // We compute them here and only use them for sanity checks.
        int minLen = INT_MAX;
        int maxLen = -1;

        // For each character, keep positions where it appears
        vector<int> pos[26];
        for (int i = 0; i < n; ++i) {
            pos[W[i] - 'a'].push_back(i);
        }

        for (int c = 0; c < 26; ++c) {
            int sz = (int)pos[c].size();
            if (sz < K) continue;
            for (int i = 0; i + K - 1 < sz; ++i) {
                int l = pos[c][i];
                int r = pos[c][i + K - 1];
                int len = r - l + 1;
                minLen = min(minLen, len);
                maxLen = max(maxLen, len);
            }
        }

        // Sanity checks on computed bounds
        if (minLen == INT_MAX) {
            ensuref(maxLen == -1, "Inconsistent substring existence in test case %d", tc + 1);
        } else {
            ensuref(minLen >= K && minLen <= n, "Invalid minimal length in test case %d", tc + 1);
            ensuref(maxLen >= minLen && maxLen <= n, "Invalid maximal length in test case %d", tc + 1);
        }
    }

    inf.readEof();
}
