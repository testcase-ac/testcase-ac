#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: size of the sequence
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // A_1 .. A_N
    vector<long long> A(N + 1);
    for (int i = 1; i <= N; ++i) {
        A[i] = inf.readInt(1, 100000, "A_i");
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    // M: number of queries
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    bool hasType3 = false;

    for (int qi = 0; qi < M; ++qi) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        int L = inf.readInt(1, N, "L");
        inf.readSpace();
        int R = inf.readInt(1, N, "R");
        ensuref(L <= R, "Query %d: L(%d) must be <= R(%d)", qi + 1, L, R);

        if (type == 1) {
            inf.readSpace();
            int X = inf.readInt(1, 100000, "X");
            inf.readEoln();
            // Apply A_i += X for checking global behavior if needed
            // But statement does not impose any global property on values,
            // only on query existence, so we don't need to simulate values.
        } else if (type == 2) {
            inf.readEoln();
            // Similarly, we don't need to simulate sqrt operation.
        } else { // type == 3
            inf.readEoln();
            hasType3 = true;
        }
    }

    ensuref(hasType3, "There must be at least one query of type 3");

    inf.readEof();
}
