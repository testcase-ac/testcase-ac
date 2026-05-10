#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for(int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) p[a] = b;
        else if (r[b] < r[a]) p[b] = a;
        else { p[b] = a; r[a]++; }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 2500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 4000, "M");
    inf.readEoln();

    // Read gas prices
    vector<int> price = inf.readInts(N, 1, 2500, "price");
    inf.readEoln();

    // Prepare to check edges
    DSU dsu(N);
    set<pair<int,int>> edges;

    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 2500, "w_i");
        inf.readEoln();

        // No loops
        ensuref(u != v, "Loop detected on edge %d: both endpoints are %d", i+1, u);

        // Normalize undirected edge
        int a = min(u, v), b = max(u, v);

        // No multiple edges
        ensuref(!edges.count({a,b}),
                "Multiple edges detected connecting %d and %d on edge %d", a, b, i+1);
        edges.insert({a,b});

        // Union for connectivity
        dsu.unite(u, v);
    }

    // Check connectivity: all cities reachable
    int root = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root,
                "Graph is not connected: city %d is disconnected", i);
    }

    inf.readEof();
    return 0;
}
