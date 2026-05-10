#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, U, D, S
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int U = inf.readInt(1, 10, "U");
    inf.readSpace();
    int D = inf.readInt(1, U, "D"); // D <= U
    inf.readSpace();
    int S = inf.readInt(1, 500001, "S");
    inf.readEoln();

    vector<int> positions;
    positions.reserve(N);

    for (int i = 0; i < N; i++) {
        char bufT[20], bufL[20], bufM[20];
        sprintf(bufT, "T[%d]", i);
        int T = inf.readInt(1, 500000, bufT);
        inf.readSpace();

        sprintf(bufL, "L[%d]", i);
        int L = inf.readInt(1, 500001, bufL);
        inf.readSpace();

        sprintf(bufM, "M[%d]", i);
        int M = inf.readInt(1, 4000, bufM);
        inf.readEoln();

        // Position must not coincide with home position
        ensuref(L != S,
                "Market position L[%d]=%d must not equal home position S=%d",
                i, L, S);

        positions.push_back(L);
    }

    // Check that all market positions are distinct
    sort(positions.begin(), positions.end());
    for (int i = 1; i < N; i++) {
        ensuref(positions[i] != positions[i-1],
                "Duplicate market position detected: %d appears more than once",
                positions[i]);
    }

    inf.readEof();
    return 0;
}
