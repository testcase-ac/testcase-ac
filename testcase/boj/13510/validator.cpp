#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0) {
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

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000, "w_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);

        // No multi-edges
        int a = min(u, v);
        int b = max(u, v);
        pair<int,int> e = make_pair(a, b);
        ensuref(!edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        edges.insert(e);

        // No cycles
        bool ok = dsu.unite(u, v);
        ensuref(ok,
                "Cycle detected at edge index %d: (%d, %d)", i, u, v);
    }

    // Check connectivity: all nodes must be in one component
    int root1 = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root1,
                "Graph is not connected: node %d is disconnected", i);
    }

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read queries
    for (int qi = 1; qi <= M; qi++) {
        int t = inf.readInt(1, 2, "type_i");
        inf.readSpace();
        if (t == 1) {
            int idx = inf.readInt(1, N-1, "idx_i");
            inf.readSpace();
            int c = inf.readInt(1, 1000000, "c_i");
            inf.readEoln();
        } else {
            // t == 2
            int u = inf.readInt(1, N, "u2_i");
            inf.readSpace();
            int v = inf.readInt(1, N, "v2_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
