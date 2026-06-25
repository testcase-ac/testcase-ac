#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int components;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0), components(n) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        --components;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, n, "w_i");
        inf.readSpace();
        inf.readInt(1, 200000, "c_i");
        inf.readEoln();

        // CHECK: The statement defines the input object as a tree, so the listed
        // N-1 edges must be a simple connected acyclic undirected graph.
        ensuref(v != w, "edge %d is a self-loop at vertex %d", i, v);
        pair<int, int> edge = minmax(v, w);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)", i, v, w);
        ensuref(dsu.unite(v, w),
                "edge %d creates a cycle: (%d, %d)", i, v, w);
    }

    ensuref(dsu.components == 1, "tree is disconnected: %d components", dsu.components);

    inf.readInts(n, -1000, 1000, "A_i");
    inf.readEoln();
    inf.readInts(n, -1000, 1000, "B_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
