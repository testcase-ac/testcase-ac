#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 50, "M");
    inf.readEoln();

    vector<int> S;
    S.reserve(M);

    if (M > 0) {
        // Second line: exactly M distinct natural numbers, each in [1, 1000]
        S = inf.readInts(M, 1, 1000, "S_i");
        inf.readEoln();

        // Check distinctness
        vector<int> tmp = S;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < M; ++i) {
            ensuref(tmp[i] != tmp[i - 1],
                    "Duplicate value in set S: %d appears at least twice", tmp[i]);
        }
    } else {
        // When M == 0, the second line is an empty line
        string emptyLine = inf.readLine("[^]*", "empty_line");
        ensuref(emptyLine.empty(),
                "When M = 0, the second line must be empty, but got: '%s'",
                emptyLine.c_str());
    }

    // Now verify that the answer (min |N - x*y*z| over x,y,z not in S) is well-defined
    // by actually computing it and checking it's finite. This also implicitly checks:
    // - There exists at least one natural number not in S usable for x,y,z.
    // Natural numbers here are positive integers, so we consider x,y,z ∈ [1,1000]
    // (beyond 1000 only makes products larger and does not break existence).
    const int MAXV = 1000;
    vector<bool> banned(MAXV + 1, false);
    for (int v : S) {
        banned[v] = true;
    }

    // Collect all candidates in [1, MAXV] not in S
    vector<int> cand;
    for (int v = 1; v <= MAXV; ++v) {
        if (!banned[v]) cand.push_back(v);
    }

    ensuref(!cand.empty(),
            "No available natural number outside S in range [1,%d]; "
            "cannot choose x,y,z not in S.", MAXV);

    // Compute minimal |N - x*y*z|; cap loops to reasonable size to avoid TLE in validator.
    // Since this is just a validator and MAXV=1000, but we loop only over 'cand' which
    // can have up to 1000 elements; worst case 1000^3 = 1e9 is too big.
    // We can restrict search space by limiting to smallest K candidates, since product
    // grows quickly and N<=1000. Taking first K=50 is plenty.
    int K = (int)min<size_t>(50, cand.size());
    long long best = (long long)4e18;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < K; ++k) {
                long long prod = 1LL * cand[i] * cand[j] * cand[k];
                long long diff = prod - N;
                if (diff < 0) diff = -diff;
                if (diff < best) best = diff;
            }
        }
    }
    ensuref(best < (long long)4e18,
            "Failed to compute a finite minimum |N - x*y*z|; something is wrong.");

    inf.readEof();
}
