#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int w;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, M, A, B, C
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500000, "M");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readSpace();
    long long C = inf.readLong(1LL, (long long)1e14, "C");
    inf.readEoln();

    ensuref(A != B, "A and B must be different, got A=%d, B=%d", A, B);

    // Read edges and validate simple graph (no loops, no multiple edges)
    vector<vector<Edge>> g(N + 1);
    // To detect multiple edges, store smaller endpoint first
    static unordered_set<long long> edgeSet;
    edgeSet.reserve(M * 2);
    edgeSet.max_load_factor(0.7);

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge index %d: (%d, %d)", i, u, v);

        int x = u, y = v;
        if (x > y) swap(x, y);
        long long key = ( (long long)x << 32 ) ^ (unsigned long long)y;
        ensuref(edgeSet.find(key) == edgeSet.end(),
                "Multiple edge detected between %d and %d at edge index %d", x, y, i);
        edgeSet.insert(key);

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // Global property: assume (as is typical for such problems) that
    // there exists at least one path from A to B with total cost <= C.
    // The statement only says what to output if impossible (-1) but
    // does not guarantee existence, so we MUST NOT enforce existence.
    // However, we must enforce that the graph is undirected as described
    // (already done) and that the rules about fees and budget behavior
    // do not imply additional constraints that must always hold
    // (none beyond basic model).

    // Nonetheless, it's useful to verify that all numbers and global
    // structural constraints are consistent; no further required
    // global condition is mentioned in the statement.

    inf.readEof();
}
