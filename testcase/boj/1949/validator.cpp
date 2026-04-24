#include "testlib.h"
#include <vector>
#include <set>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of villages
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read populations
    vector<int> w = inf.readInts(N, 1, 10000, "weight");
    inf.readEoln();

    // Prepare DSU for connectivity check
    vector<int> parent(N+1);
    iota(parent.begin(), parent.end(), 0);
    auto findp = [&](int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    };

    // Read edges, check no loops, no multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < N - 1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loop
        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);

        // Normalize edge
        int a = min(u, v), b = max(u, v);
        // No multiple edges
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({a, b});

        // Union in DSU
        int pu = findp(u), pv = findp(v);
        if (pu != pv) {
            parent[pv] = pu;
        }
    }

    // Check connectivity: exactly one component
    set<int> comps;
    for (int i = 1; i <= N; i++) {
        comps.insert(findp(i));
    }
    ensuref(comps.size() == 1,
            "Graph is not connected: %d components found", (int)comps.size());

    // File ends properly
    inf.readEof();
    return 0;
}
