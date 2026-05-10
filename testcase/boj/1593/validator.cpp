#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // g: length of W, n: length of S
    const int G_MAX = 3000;
    const int N_MAX = 3000000;

    int g = inf.readInt(1, G_MAX, "g");
    inf.readSpace();
    int n = inf.readInt(g, N_MAX, "n");
    inf.readEoln();

    // Read W: length exactly g, alphabet letters, case-sensitive
    string W = inf.readToken("[A-Za-z]+", "W");
    inf.readEoln();
    ensuref((int)W.size() == g,
            "Length of W (%d) does not match given g (%d)", (int)W.size(), g);

    // Read S: length exactly n, alphabet letters, case-sensitive
    string S = inf.readToken("[A-Za-z]+", "S");
    inf.readEoln();
    ensuref((int)S.size() == n,
            "Length of S (%d) does not match given n (%d)", (int)S.size(), n);

    // Global property: the problem guarantees that the answer always exists
    // (it can be zero; no stronger global condition is stated),
    // so we only need to validate input constraints and format.

    // However, we can cheaply verify that counting anagrams is well-defined.
    // We'll compute the number of positions where any permutation of W
    // appears as a substring in S, and ensure the computation stays within
    // reasonable bounds (no overflow etc.). This is not a statement-guaranteed
    // bound, so it's only a sanity self-check, not a constraint on input.

    // Use frequency over 52 letters (A-Z, a-z)
    auto idx = [](char c) -> int {
        if ('A' <= c && c <= 'Z') return c - 'A';
        if ('a' <= c && c <= 'z') return 26 + (c - 'a');
        return -1; // shouldn't happen due to regex
    };

    vector<int> need(52, 0), cur(52, 0);
    for (char c : W) {
        int id = idx(c);
        ensuref(id != -1, "Non-alphabet character in W after regex check");
        need[id]++;
    }

    int diffKinds = 0;
    for (int i = 0; i < 52; ++i)
        if (need[i] > 0) diffKinds++;

    int equalKinds = 0;
    long long answer = 0;

    // initialize first window of size g
    for (int i = 0; i < g; ++i) {
        int id = idx(S[i]);
        ensuref(id != -1, "Non-alphabet character in S after regex check");
        int before = cur[id];
        int after = before + 1;
        cur[id] = after;
    }
    for (int i = 0; i < 52; ++i) {
        if (need[i] == 0 && cur[i] == 0) continue;
        if (need[i] == cur[i]) equalKinds++;
    }
    if (equalKinds == diffKinds) answer++;

    for (int i = g; i < n; ++i) {
        int outId = idx(S[i - g]);
        int inId  = idx(S[i]);
        // update outgoing
        if (need[outId] == cur[outId]) equalKinds--;
        cur[outId]--;
        if (need[outId] == cur[outId]) equalKinds++;

        // update incoming
        if (need[inId] == cur[inId]) equalKinds--;
        cur[inId]++;
        if (need[inId] == cur[inId]) equalKinds++;

        if (equalKinds == diffKinds) answer++;
    }

    // Sanity: answer must be within [0, n-g+1]
    long long maxPos = (long long)n - g + 1;
    ensuref(0 <= answer && answer <= maxPos,
            "Internal sanity check failed: answer=%lld, bounds=[0,%lld]",
            answer, maxPos);

    inf.readEof();
}
