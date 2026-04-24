#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    int n;
    vector<int> p;
    DSU(int _n): n(_n), p(n+1) {
        for (int i = 1; i <= n; i++) p[i] = i;
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

    // Read N, M, K
    int N = inf.readInt(2, 3000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Prepare DSU for connectivity check
    DSU dsu(N);

    // Read edges, check loops and multiple edges
    set<pair<int,int>> edges;
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int l = inf.readInt(1, 1000, "l_i");
        inf.readEoln();

        ensuref(a != b, "Loop detected at edge index %d: (%d, %d)", i, a, b);
        int u = min(a,b), v = max(a,b);
        ensuref(!edges.count({u,v}),
                "Multiple edges detected between %d and %d at edge index %d", u, v, i);
        edges.insert({u,v});

        // Union for connectivity
        dsu.unite(a, b);
    }

    // Check connectivity: all nodes must share same component
    int comp = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == comp,
                "Graph is not connected: node %d is unreachable from node 1", i);
    }

    // Read mall cities, check uniqueness
    set<int> malls;
    for (int i = 0; i < K; i++) {
        int mcity = inf.readInt(1, N, "mall_i");
        inf.readEoln();
        ensuref(!malls.count(mcity),
                "Duplicate mall city detected: city %d listed more than once", mcity);
        malls.insert(mcity);
    }

    inf.readEof();
    return 0;
}
