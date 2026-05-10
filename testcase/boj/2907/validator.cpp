#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 25;
    const int MAXR = 500;
    const long long MAXK = 1000000000LL;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int R = inf.readInt(1, MAXR, "R");
    inf.readEoln();

    // Graph for global checks: directed, allow at most 2 opposite edges between same nodes,
    // but not two edges in same direction.
    vector<vector<int>> g(N + 1);

    // To check "at most 2 edges between two intersections and if 2 then opposite directions"
    // We'll track existing directed edges.
    // dirEdge[u][v] = true if edge u->v exists.
    static bool dirEdge[26][26]; // N <= 25

    for (int i = 0; i < R; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        string s = inf.readToken("[A-Z]{1,4}", "s");
        inf.readEoln();

        // vertices must be different
        ensuref(u != v, "Loop edge detected at road index %d: (%d -> %d)", i, u, v);

        // check letters: only B, J, M, P allowed
        for (char c : s) {
            ensuref(c == 'B' || c == 'J' || c == 'M' || c == 'P',
                    "Invalid ingredient '%c' at road index %d", c, i);
        }

        // multiple edges constraint
        ensuref(!dirEdge[u][v],
                "Multiple edges with same direction (%d -> %d) at road index %d", u, v, i);
        dirEdge[u][v] = true;

        // Check total undirected multiplicity: for pair {u,v}, we can have at most 2 directed edges
        int cnt = (int)dirEdge[u][v] + (int)dirEdge[v][u];
        ensuref(cnt <= 2,
                "More than two edges between intersections %d and %d", u, v);

        g[u].push_back(v);
    }

    long long K = inf.readLong(1LL, MAXK, "K");
    inf.readEoln();

    // Global property: from node 1, there must exist at least one node with outgoing edge,
    // otherwise no movement possible and trivial but allowed by statement? Statement doesn't
    // forbid disconnected graphs or unreachable nodes, only bounds roads. So no extra check
    // on reachability is strictly required by text, except consistency of graph structure,
    // which we already enforce by ranges and multiplicity rules.

    // However, we can still check that the vertex indices are consistent through all edges,
    // which is already enforced by readInt ranges.

    // No further global properties (like guaranteed existence of a route or bound on answer)
    // are stated, so we do not compute or simulate walks.

    inf.readEof();
}
