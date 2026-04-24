#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n+1) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read edges and build DSU, check loops & multi-edges
    DSU dsu(N);
    set<pair<int,int>> seen;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "p_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "q_i");
        inf.readSpace();
        int r = inf.readInt(1, 1000000000, "r_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected on edge index %d: (%d, %d)", i, u, v);

        // No multiple edges
        int a = min(u, v), b = max(u, v);
        ensuref(!seen.count({a,b}),
                "Multiple edges detected on edge index %d: (%d, %d)", i, u, v);
        seen.insert({a,b});

        // Union for connectivity
        dsu.unite(u, v);
    }

    // Check connectivity (tree property)
    if (N >= 2) {
        int root = dsu.find(1);
        for (int i = 2; i <= N; i++) {
            ensuref(dsu.find(i) == root,
                    "Graph is not connected: node %d is in a different component", i);
        }
    }

    // Read queries
    for (int i = 0; i < Q; i++) {
        long long k = inf.readLong(1LL, 1000000000LL, "k_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
        // No further validation on query logic needed
    }

    inf.readEof();
    return 0;
}
