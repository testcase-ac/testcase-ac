#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Read edges
    for (int i = 0; i < M; i++) {
        char bufU[30], bufV[30];
        sprintf(bufU, "u_%d", i+1);
        sprintf(bufV, "v_%d", i+1);
        int u = inf.readInt(1, N, bufU);
        inf.readSpace();
        int v = inf.readInt(1, N, bufV);
        inf.readEoln();
        // loops and multi-edges are not forbidden by statement
    }

    // Read closing order: must be a permutation of 1..N
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        char bufC[30];
        sprintf(bufC, "close_%d", i+1);
        int x = inf.readInt(1, N, bufC);
        inf.readEoln();
        ensuref(!seen[x], "Barn %d closed more than once (at closing step %d)", x, i+1);
        seen[x] = 1;
    }
    // All barns must appear exactly once
    // (since we read N values in [1..N] with no repeats, it's a permutation)

    inf.readEof();
    return 0;
}
