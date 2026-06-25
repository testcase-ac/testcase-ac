#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
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
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    int p = inf.readInt(1, n, "P");
    inf.readSpace();
    int g = inf.readInt(1, n, "G");
    ensuref(p != g, "P and G must be distinct: %d", p);
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "U");
        inf.readSpace();
        int v = inf.readInt(1, n, "V");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "D");
        ensuref(u != v, "self-loop at edge %d: %d", i, u);

        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: %d %d", i, u, v);
        dsu.unite(u, v);

        inf.readEoln();
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected at vertex %d", v);
    }

    inf.readEof();
}
