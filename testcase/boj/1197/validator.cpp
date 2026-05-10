#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read V and E
    int V = inf.readInt(1, 10000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 100000, "E");
    inf.readEoln();

    // Read edges and build DSU for connectivity test
    DSU dsu_conn(V);
    struct Edge { int a, b, c; };
    vector<Edge> edges;
    edges.reserve(E);

    for (int i = 0; i < E; i++) {
        int a = inf.readInt(1, V, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, V, "B_i");
        inf.readSpace();
        int c = inf.readInt(-1000000, 1000000, "C_i");
        inf.readEoln();

        edges.push_back({a, b, c});
        dsu_conn.unite(a, b);
    }

    // Check connectivity: all vertices must be connected
    int root1 = dsu_conn.find(1);
    for (int v = 2; v <= V; v++) {
        ensuref(dsu_conn.find(v) == root1,
                "Graph is not connected: vertex %d is not reachable from vertex 1", v);
    }

    // Compute MST weight via Kruskal
    sort(edges.begin(), edges.end(), [](const Edge &x, const Edge &y) {
        return x.c < y.c;
    });
    DSU dsu_mst(V);
    __int128 total = 0;
    int used = 0;
    for (auto &e : edges) {
        if (dsu_mst.unite(e.a, e.b)) {
            total += e.c;
            used++;
            if (used == V - 1) break;
        }
    }
    ensuref(used == V - 1,
            "Unable to build MST: only %d edges used for %d vertices", used, V);

    // Check MST weight bounds
    long long tot_ll = (long long) total;
    ensuref(total >= ( (__int128) numeric_limits<int32_t>::min() )
            && total <= ( (__int128) numeric_limits<int32_t>::max() ),
            "MST weight %lld out of allowed 32-bit signed range", tot_ll);

    inf.readEof();
    return 0;
}
