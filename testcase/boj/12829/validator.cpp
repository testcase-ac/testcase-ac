#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, B, E, H
    int N = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 1000, "M");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readSpace();
    int E = inf.readInt(1, N, "E");
    inf.readSpace();
    int H = inf.readInt(1, N, "H");
    inf.readEoln();

    // Check that B, E, H are all different
    ensuref(B != E && E != H && H != B, "B, E, H must be all different: got B=%d, E=%d, H=%d", B, E, H);

    // Read edges, check for loops and multiple edges
    set<pair<int,int>> edges;
    vector<vector<pair<int,int>>> adj(N+1); // 1-based, stores (neighbor, weight)
    for (int i = 0; i < M; ++i) {
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, N, "w");
        inf.readSpace();
        int t = inf.readInt(1, 1000000, "t");
        inf.readEoln();

        ensuref(v != w, "Loop detected at edge index %d: (%d, %d)", i+1, v, w);

        int a = min(v, w), b = max(v, w);
        ensuref(!edges.count({a, b}), "Multiple edge detected between %d and %d at edge index %d", v, w, i+1);
        edges.insert({a, b});

        adj[v].emplace_back(w, t);
        adj[w].emplace_back(v, t);
    }

    // Check for extra lines
    inf.readEof();

    // No further global property is guaranteed by the statement (e.g., connectivity, path existence, etc.)
    // So, no need to check for connectivity or existence of a path.
    // The only global property is that B, E, H are distinct, and no loops/multiedges.

    return 0;
}
