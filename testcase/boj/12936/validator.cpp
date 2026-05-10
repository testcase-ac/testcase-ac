#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 5000;
    const int M_MAX = 50000;

    int N = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(0, M_MAX, "M");
    inf.readEoln();

    // Read P[i]
    vector<int> P = inf.readInts(N, 0, 100, "P");
    inf.readEoln();

    struct Edge {
        int u, v, c;
    };
    vector<Edge> edges;
    edges.reserve(M);

    // To check simple graph property (no self-loop), multiple edges are allowed since
    // the statement does not forbid them.
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int c = inf.readInt(0, 100, "C_i");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at relation index %d: (%d, %d)", i, a, b);

        edges.push_back({a - 1, b - 1, c});
    }

    // No more input
    inf.readEof();
}
