#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(N - 1, 200000, "M");
    inf.readEoln();

    // DSU for connectivity check
    vector<int> parent(N + 1, -1);
    int compCount = N;
    auto findRoot = [&](int x) {
        int r = x;
        while (parent[r] >= 0) r = parent[r];
        while (x != r) {
            int p = parent[x];
            parent[x] = r;
            x = p;
        }
        return r;
    };
    auto unite = [&](int a, int b) {
        int ra = findRoot(a);
        int rb = findRoot(b);
        if (ra == rb) return false;
        // union by size (parent stores -size)
        if (parent[ra] > parent[rb]) swap(ra, rb);
        parent[ra] += parent[rb];
        parent[rb] = ra;
        return true;
    };

    // To detect multiple edges
    set<pair<int,int>> seenEdges;

    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected on edge %d: (%d,%d)", i+1, u, v);

        // No multiple edges (undirected)
        int a = min(u, v), b = max(u, v);
        ensuref(!seenEdges.count({a, b}),
                "Multiple edges detected on edge %d: (%d,%d)", i+1, a, b);
        seenEdges.insert({a, b});

        // Build DSU
        if (unite(u, v)) {
            compCount--;
        }
    }

    // Check connectivity
    ensuref(compCount == 1,
            "Graph is not connected: %d components found", compCount);

    inf.readEof();
    return 0;
}
