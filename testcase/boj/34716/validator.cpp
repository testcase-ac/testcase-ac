#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of cells
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // heights h_1 ... h_N
    vector<long long> h = inf.readLongs(N, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    // Q: number of drains
    int Q = inf.readInt(1, N, "Q");
    inf.readEoln();

    // queries: indices, all distinct, 1..N
    vector<int> used(N + 1, 0);
    for (int qi = 0; qi < Q; ++qi) {
        int idx = inf.readInt(1, N, "i");
        inf.readEoln();
        ensuref(!used[idx], "Query index %d appears multiple times", idx);
        used[idx] = 1;
    }

    // No additional global constraints are stated (like existence of answer, etc.)
    // Trapping rain water is always well-defined for any sequence of heights.

    inf.readEof();
}
