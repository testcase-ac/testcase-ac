#include "testlib.h"

#include <algorithm>
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
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, format("u[%d]", i).c_str());
        inf.readSpace();
        int v = inf.readInt(1, n, format("v[%d]", i).c_str());
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "edge %d duplicates edge (%d, %d)",
                i,
                edge.first,
                edge.second);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle between %d and %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "vertex %d is not connected to vertex 1", v);
    }

    inf.readEof();
}
