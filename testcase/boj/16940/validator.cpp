#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1,0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Prepare DSU and edge set to detect loops, multiple edges, cycles
    DSU dsu(N);
    set<pair<int,int>> edges;

    // Read N-1 edges
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at edge %d: (%d, %d)", i, u, v);

        // No multiple edges (undirected)
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge %d: (%d, %d)", i, u, v);
        edges.insert({a, b});

        // No cycles
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge %d: (%d, %d)", i, u, v);
    }

    // Graph must be connected
    int root1 = dsu.find(1);
    for (int x = 2; x <= N; x++) {
        ensuref(dsu.find(x) == root1,
                "Graph is disconnected: node %d is not reachable from node 1", x);
    }

    // Read BFS sequence
    vector<int> order = inf.readInts(N, 1, N, "order");
    inf.readEoln();

    // Check it's a permutation: no duplicates
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = order[i];
        ensuref(!seen[x],
                "Value %d appears multiple times in BFS sequence", x);
        seen[x] = 1;
    }
    // All 1..N must appear; since range is 1..N and count is N, this is guaranteed

    inf.readEof();
    return 0;
}
