#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readSpace();
    int k = inf.readInt(1, m, "k");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "loop at edge index %d: (%d, %d)", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i, u, v);
        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected: vertex %d is not reachable from 1", v);
    }

    inf.readEof();
}
