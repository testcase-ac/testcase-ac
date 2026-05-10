#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long count_periods(const string &t) {
    int L = (int)t.size();
    if (L == 0) return 0;
    // KMP prefix-function to find minimal period
    vector<int> pi(L);
    for (int i = 1; i < L; ++i) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) ++j;
        pi[i] = j;
    }
    int p = L - pi[L - 1];
    if (L % p == 0) return L / p;
    return 1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 8, "N");
    inf.readEoln();

    vector<string> S(N);
    long long totalLen = 0;
    for (int i = 0; i < N; ++i) {
        S[i] = inf.readToken("[A-Z]{1,20}", "S_i");
        inf.readEoln();
        totalLen += (int)S[i].size();
    }

    int K = inf.readInt(1, 200, "K");
    inf.readEoln();

    // Global property: For every permutation, resulting string length <= 160,
    // so max possible number of matching rotations is its length.
    // If K > 160, answer would always be 0 and that's allowed by statement.
    // However, statement does not say "such permutation always exists",
    // so we must NOT enforce existence of a permutation with exactly K matches.
    // We only check that the claimed upper bound holds generically:
    ensuref(totalLen <= 160, "Total concatenated length %lld exceeds 160", totalLen);

    // Additional sanity: For any concrete concatenation, number of matching rotations
    // cannot exceed its length, thus cannot exceed 160; since K <= 200 in input,
    // there exist inputs with no valid permutations, which is allowed.

    // Optional deeper global check (not required by statement):
    // The problem states definition of magical string but does not guarantee
    // bounds on number of valid permutations or existence, so no further
    // global validation is needed.

    inf.readEof();
}
