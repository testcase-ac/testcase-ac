#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    int n;
    vector<int> p;
    DSU(int _n): n(_n), p(n+1) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    // returns true if merged, false if already in same set
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of nodes
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read edges: should form a tree (no loops, no cycles, exactly N-1 edges)
    DSU dsu(N);
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_edge");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_edge");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge #%d: both endpoints are %d", i, u);
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge #%d: adding (%d, %d) creates a cycle or duplicate edge", 
                i, u, v);
    }

    // Number of queries
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Each query: two valid node indices
    for (int i = 1; i <= M; i++) {
        int a = inf.readInt(1, N, "u_query");
        inf.readSpace();
        int b = inf.readInt(1, N, "v_query");
        inf.readEoln();
        // No need to check a != b; LCA of same node is that node.
    }

    inf.readEof();
    return 0;
}
