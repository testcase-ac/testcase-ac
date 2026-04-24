#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(2, 50000, "N");
    inf.readEoln();

    // DSU for connectivity
    vector<int> parent(N+1);
    for (int i = 1; i <= N; i++) parent[i] = i;
    auto find_root = [&](int x) {
        int r = x;
        while (parent[r] != r) r = parent[r];
        // path compression
        while (x != r) {
            int p = parent[x];
            parent[x] = r;
            x = p;
        }
        return r;
    };

    // Read edges, ensure no loops/multiple edges, build DSU
    set<pair<int,int>> edges;
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({a, b});

        int ru = find_root(u);
        int rv = find_root(v);
        if (ru != rv) {
            parent[ru] = rv;
        }
    }

    // Check connectivity: there must be exactly 1 component
    int comps = 0;
    for (int i = 1; i <= N; i++) {
        if (find_root(i) == i) comps++;
    }
    ensuref(comps == 1, "Graph is not connected: %d components found", comps);

    // Read number of queries
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read queries
    for (int i = 1; i <= M; i++) {
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readEoln();
    }

    // Final checks
    inf.readEof();
    return 0;
}
