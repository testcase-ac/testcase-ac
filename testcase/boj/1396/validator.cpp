#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // To check for unique edge weights
    vector<bool> weightUsed(1000000 + 1, false);

    // Read edges
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000, "c_i");
        inf.readEoln();

        // No loops allowed (a != b)
        ensuref(u != v,
                "Loop detected on edge %d: both endpoints are %d", i+1, u);

        // Edge weights must be unique
        ensuref(!weightUsed[w],
                "Duplicate edge weight detected: weight %d appears more than once (at edge %d)", w, i+1);
        weightUsed[w] = true;
    }

    // Read number of queries Q
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < Q; i++) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        // x != y for each query
        ensuref(x != y,
                "Query %d has identical endpoints: both are %d", i+1, x);
    }

    inf.readEof();
    return 0;
}
