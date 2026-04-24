#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

static vector<int> parent;
int find_set(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find_set(parent[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Prepare DSU
    parent.resize(n+1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    int components = n;

    // Check edges: must be exactly n-1 lines
    set<pair<int,int>> edges;
    for (int i = 1; i <= n - 1; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected on edge %d: both endpoints are %d", i, u);

        // No multiple edges
        int a = min(u, v), b = max(u, v);
        pair<int,int> e = make_pair(a, b);
        ensuref(!edges.count(e),
                "Multiple edges detected on edge %d: (%d, %d)", i, u, v);
        edges.insert(e);

        // DSU union; detect cycles
        int ru = find_set(u);
        int rv = find_set(v);
        ensuref(ru != rv,
                "Cycle detected on edge %d: (%d, %d)", i, u, v);
        parent[rv] = ru;
        components--;
    }

    // The graph must be connected (i.e., exactly one component)
    ensuref(components == 1,
            "The graph is not connected: %d components found, expected 1", components);

    // No extra data
    inf.readEof();
    return 0;
}
