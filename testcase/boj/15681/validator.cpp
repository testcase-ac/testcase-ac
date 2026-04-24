#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) {
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

    // Read first line: N, R, Q
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        edges.insert({a, b});
        dsu.unite(u, v);
    }

    // Check connectivity
    int root0 = dsu.find(1);
    int comp = 0;
    for (int i = 1; i <= N; i++) {
        if (dsu.find(i) != root0) {
            comp++;
        }
    }
    ensuref(comp == 0, "Graph is not connected: %d nodes are disconnected", comp);

    // Read queries
    for (int i = 0; i < Q; i++) {
        int u = inf.readInt(1, N, "query");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
