#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute minimal rotations to transform given S (only 'C' and 'U')
// into some balanced parentheses sequence, under the rules:
//
// For each character independently, we can rotate it in 90° steps:
//   'C': as '(' (0 rotations) or ')' (2 rotations)
//   'U': as '(' (1 rotation cw) or ')' (1 rotation ccw)
// Goal: choose '(' / ')' for each position so that full string is a
// correct parentheses sequence, minimizing total rotations.
// Return that minimum, or -1 if impossible.
// This function is used only for validation to ensure the claimed
// property "answer always exists" actually holds for every state.
long long computeMinRotations(const string &S) {
    int n = (int)S.size();
    // Balanced sequence requires exactly n/2 opens and n/2 closes.
    int cntC = 0, cntU = 0;
    for (char c : S) {
        if (c == 'C') cntC++;
        else cntU++;
    }
    int needOpen = n / 2;
    int needClose = n / 2;
    // For each char, we may choose open or close.
    // We must ensure possibility: 0 <= openC <= cntC, 0 <= openU <= cntU
    // totalOpen = openC + openU = needOpen.
    // For 'C': cost('(')=0, cost(')')=2. For 'U': cost both = 1 (either '(' or ')').
    // So total cost = openC*0 + (cntC - openC)*2 + cntU*1 = 2*cntC - 2*openC + cntU.
    // To minimize, maximize openC subject to feasibility.
    // Feasibility:
    //   0 <= openC <= cntC
    //   0 <= needOpen - openC <= cntU
    //   => needOpen - cntU <= openC <= needOpen
    // Final intersection:
    //   L = max(0, needOpen - cntU)
    //   R = min(cntC, needOpen)
    int L = max(0, needOpen - cntU);
    int R = min(cntC, needOpen);
    if (L > R) {
        // No feasible assignment -> impossible to form balanced parentheses at all.
        return -1;
    }
    int openC = R; // maximize openC
    long long cost = 2LL * cntC - 2LL * openC + cntU;

    // We must also ensure that some parentheses order exists (with that total
    // number of opens/closes) that is a correct bracket sequence.
    // But given we may assign '(' / ')' arbitrarily per position, and only the
    // counts of '(' and ')' matter for basic balance existence, we must confirm
    // that there exists some permutation with n/2 opens & n/2 closes forming
    // a correct sequence. That is always true if counts match; e.g. sequence of
    // all opens then all closes. However, characters are fixed in positions:
    // but their final '(' / ')' assignment is independent per position, so
    // we can imitate any parentheses pattern. Hence feasibility is only about counts.
    // Therefore whenever counts allow, answer exists.

    return cost;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;
    const int MAXQ = 200000;

    int N = inf.readInt(2, MAXN, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    ensuref(N % 2 == 0, "N must be even, got %d", N);

    string S = inf.readToken("[CU]{1,200000}", "S");
    inf.readEoln();
    ensuref((int)S.size() == N, "Length of S must be N (%d), got %d", N, (int)S.size());

    // Check minimal rotations for initial S exists
    long long initCost = computeMinRotations(S);
    ensuref(initCost >= 0, "Initial string cannot be transformed into a valid parentheses sequence");

    // Process Q queries; each toggles S[x-1] between 'C' and 'U'.
    for (int qi = 0; qi < Q; ++qi) {
        int x = inf.readInt(1, N, "x");
        inf.readEoln();

        // Apply update to S as described in statement
        char &ch = S[x - 1];
        if (ch == 'C') ch = 'U';
        else ch = 'C';

        long long cost = computeMinRotations(S);
        ensuref(cost >= 0,
                "After query %d (position %d), string cannot be transformed into a valid parentheses sequence",
                qi + 1, x);
    }

    inf.readEof();
}
