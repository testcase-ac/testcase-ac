#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute lexicographically smallest valid reverse pattern for given strings.
// Returns string of '0'/'1' of length n. Assumes at least one solution exists.
string solveCase(const vector<string>& s) {
    int n = (int)s.size();
    vector<string> r(n);
    for (int i = 0; i < n; ++i) {
        r[i] = s[i];
        reverse(r[i].begin(), r[i].end());
    }

    string ans(n, '0');
    // For each position, greedily choose '0' if possible.
    for (int i = 0; i < n; ++i) {
        bool can0 = true, can1 = true;
        for (int j = 0; j < i; ++j) {
            // previous choice is fixed in ans[j]
            const string& prev =
                (ans[j] == '0' ? s[j] : r[j]);

            // Assume si for '0', ri for '1'
            const string& si = s[i];
            const string& ri = r[i];

            bool ok0 = (prev <= si);
            bool ok1 = (prev <= ri);
            if (!ok0) can0 = false;
            if (!ok1) can1 = false;
        }
        // Additionally, check consistency with following possible choices.
        // However, due to the problem's structure (we only compare consecutive
        // after full pattern is chosen), checking against previous is enough:
        // Once current choice is decided, later positions can always be
        // adjusted if some global solution exists. So we only need prev check.

        // The problem guarantees that at least one full pattern exists.
        // Among choices that can extend some valid completion, we want smallest.

        // Try '0' first. If it's impossible to be part of a valid pattern,
        // we should pick '1'. To detect impossibility, we need to check if
        // there exists at least one completion for the suffix consistent with
        // choosing current bit as '0' or '1'.
        //
        // For small constraints (N<=150, |S[i]|<=20), we can brute force suffix
        // feasibility by dynamic programming on states (index, prevVariant).

        auto feasible = [&](char choice) -> bool {
            const string& cur = (choice == '0' ? s[i] : r[i]);
            if (!can0 && choice == '0') return false;
            if (!can1 && choice == '1') return false;

            // DP: dp[pos][v]: can we reach position pos with variant v (0=s,1=r)
            // given that at position i we fixed 'choice'?
            int m = n;
            vector<array<char,2>> dp(m);
            for (int k = 0; k < m; ++k) dp[k][0] = dp[k][1] = 0;

            // Build prefix fixed up to i (inclusive)
            // At position i: only chosen variant is allowed
            // At position 0..i-1: already fixed in ans[]
            // Start DP from i.
            // State at i: only chosen variant
            // For i, we just mark reachable for chosen variant
            dp[i][choice == '1'] = 1;

            // Build forward from i to n-1
            for (int pos = i + 1; pos < n; ++pos) {
                for (int prevV = 0; prevV <= 1; ++prevV) {
                    if (!dp[pos - 1][prevV]) continue;
                    const string& prevStr =
                        (pos - 1 < i ? (ans[pos - 1] == '0' ? s[pos - 1] : r[pos - 1])
                                     : (prevV == 0 ? s[pos - 1] : r[pos - 1]));
                    // Try both variants for current pos
                    for (int curV = 0; curV <= 1; ++curV) {
                        const string& curStr = (curV == 0 ? s[pos] : r[pos]);
                        if (prevStr <= curStr)
                            dp[pos][curV] = 1;
                    }
                }
            }

            // Need also to ensure consistency backward with fixed prefix
            // from 0..i: prefix already checked via previous choices.
            // But we must ensure that for position i, chosen variant works
            // with its immediate previous (i-1) if any.
            if (i > 0) {
                const string& prev =
                    (ans[i - 1] == '0' ? s[i - 1] : r[i - 1]);
                if (!(prev <= cur)) return false;
            }

            // If any variant is reachable at position n-1, it's feasible
            return (dp[m - 1][0] || dp[m - 1][1]);
        };

        if (feasible('0')) ans[i] = '0';
        else {
            ensuref(feasible('1'),
                    "Internal assumption failed: no feasible choice at position %d",
                    i);
            ans[i] = '1';
        }
    }

    // Final safety: verify that produced pattern really yields nondecreasing seq
    for (int i = 1; i < n; ++i) {
        const string& a = (ans[i - 1] == '0' ? s[i - 1] : r[i - 1]);
        const string& b = (ans[i] == '0' ? s[i] : r[i]);
        ensuref(a <= b, "constructed pattern invalid at pair (%d,%d)", i, i + 1);
    }
    return ans;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 150, "N");
        inf.readEoln();

        vector<string> s(N);
        for (int i = 0; i < N; ++i) {
            s[i] = inf.readToken("[A-Z]{2,20}", "S_i");
            inf.readEoln();
        }

        // Check uniqueness constraints: S[i] != S[j], Reverse(S[i]) != S[j]
        // for all i != j.
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                ensuref(s[i] != s[j],
                        "Duplicate strings S[%d] and S[%d]: %s",
                        i + 1, j + 1, s[i].c_str());
                string rev = s[i];
                reverse(rev.begin(), rev.end());
                ensuref(rev != s[j],
                        "Reverse(S[%d]) equals S[%d]: %s",
                        i + 1, j + 1, s[j].c_str());
                rev = s[j];
                reverse(rev.begin(), rev.end());
                ensuref(rev != s[i],
                        "Reverse(S[%d]) equals S[%d]: %s",
                        j + 1, i + 1, s[i].c_str());
            }
        }

        // Problem guarantees that at least one reverse pattern exists.
        // We validate this by actually computing one (lexicographically smallest).
        string pattern = solveCase(s);
        (void)pattern; // silence unused warning if any
    }

    inf.readEof();
}
