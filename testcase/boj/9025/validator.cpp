#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap total edge rows to keep
    // numeric input below the local practical-size limit.
    const int maxT = 100000;
    const int maxTotalEdges = 1000000;
    int totalEdges = 0;

    int T = inf.readInt(1, maxT, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 1000, "n");
        inf.readSpace();
        int maxEdges = n * (n - 1) / 2;
        int m = inf.readInt(1, maxEdges, "m");
        inf.readSpace();
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int t = inf.readInt(1, n, "t");
        inf.readEoln();

        ensuref(s != t, "s and t must differ, got %d", s);
        totalEdges += m;
        ensuref(totalEdges <= maxTotalEdges, "too many edge rows: %d", totalEdges);

        DSU dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readSpace();
            inf.readInt(1, 100000, "b");
            inf.readEoln();

            ensuref(u != v, "self-loop at edge %d: %d", i, u);
            auto edge = minmax(u, v);
            ensuref(edges.insert(edge).second,
                    "duplicate undirected edge at edge %d: %d %d", i, u, v);
            dsu.unite(u, v);
        }

        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == root, "graph is not connected; node %d is separate", v);
        }
    }

    inf.readEof();
}
