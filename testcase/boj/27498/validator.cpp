#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(n, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    Dsu all_edges(n);
    Dsu established_edges(n);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "b_i");
        inf.readSpace();
        inf.readInt(1, 10000, "c_i");
        inf.readSpace();
        int d = inf.readInt(0, 1, "d_i");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate relationship at edge %d: (%d, %d)", i, a, b);

        all_edges.unite(a, b);
        if (d == 1) {
            ensuref(established_edges.unite(a, b),
                    "established relationships contain a cycle at edge %d: (%d, %d)",
                    i, a, b);
        }
    }

    int root = all_edges.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(all_edges.find(v) == root, "graph is disconnected at vertex %d", v);
    }

    inf.readEof();
}
