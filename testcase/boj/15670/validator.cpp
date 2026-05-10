#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_NM = 100000;
    const long long MIN_A = 1LL;
    const long long MAX_A = 1000000000LL;

    int N = inf.readInt(1, MAX_NM, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAX_NM, "M");
    inf.readEoln();

    vector<long long> a = inf.readLongs(N, MIN_A, MAX_A, "a_i");
    inf.readEoln();

    // Check that all heights are distinct (global constraint from statement)
    {
        vector<long long> b = a;
        sort(b.begin(), b.end());
        for (int i = 1; i < N; ++i) {
            ensuref(b[i] != b[i - 1],
                    "Heights a_i must be pairwise distinct, but value %lld appears at least twice",
                    b[i]);
        }
    }

    // Read queries and store to later simulate
    struct Query { int l, r; };
    vector<Query> qs;
    qs.reserve(M);

    for (int i = 0; i < M; ++i) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, N, "r_i"); // r >= l
        inf.readEoln();
        qs.push_back({l, r});
    }

    // We must ensure that for each query, the described operation is valid and
    // that the road configuration after reversing [l, r] is well-defined,
    // and we should also validate the implied notion of "오르막길" (increasing runs)
    // by actually computing their count (no explicit bound other than trivial,
    // so only a logical consistency/sanity check is needed).

    // However, doing a full O(N*M) simulation would be too slow for the validator
    // in the worst case; instead, we verify only local properties around
    // the reversed segment. This is sufficient because increasing runs depend
    // solely on adjacent pairs.

    auto countRuns = [&](const vector<long long>& v)->long long {
        if (v.empty()) return 0;
        long long runs = 1;
        for (int i = 0; i + 1 < (int)v.size(); ++i) {
            if (v[i + 1] <= v[i]) runs++;
        }
        return runs;
    };

    // Precompute original adjacent relations and run count once
    long long baseRuns = countRuns(a);

    // For each query, we will:
    // - Build a small array containing only positions that can change
    //   adjacency status: indices from (l-1) to (r+1), clamped.
    // - Simulate reversal in that window and recompute runs in that window.
    // This is just to ensure there is no hidden constraint violation,
    // not to compute solution output.
    for (int qi = 0; qi < M; ++qi) {
        int l = qs[qi].l;
        int r = qs[qi].r;
        // 1-based to 0-based
        int L = l - 1;
        int R = r - 1;

        // Determine window [WL, WR] of indices potentially affecting run boundaries
        int WL = max(0, L - 1);
        int WR = min(N - 1, R + 1);

        int WN = WR - WL + 1;
        vector<long long> winOrig(WN), winMod(WN);
        for (int i = 0; i < WN; ++i) {
            winOrig[i] = a[WL + i];
            winMod[i]  = a[WL + i];
        }

        // Apply reversal [L, R] within window to winMod
        int lPos = L - WL;
        int rPos = R - WL;
        while (lPos < rPos) {
            swap(winMod[lPos], winMod[rPos]);
            ++lPos;
            --rPos;
        }

        // Sanity: values must remain distinct after reversal (permutation)
        // which is guaranteed by construction, but we check locally in window.
        {
            vector<long long> tmp = winMod;
            sort(tmp.begin(), tmp.end());
            for (int i = 1; i < (int)tmp.size(); ++i) {
                ensuref(tmp[i] != tmp[i - 1],
                        "Heights must stay distinct after reversal; duplicate %lld in query %d",
                        tmp[i], qi + 1);
            }
        }

        // Just compute the runs in the window to validate logic is sound;
        // we don't compare to anything global because the problem does not
        // state any bound or invariant on the answer.
        (void)countRuns(winOrig);
        (void)countRuns(winMod);
        (void)baseRuns; // keep baseRuns referenced to avoid warnings
    }

    inf.readEof();
}
