#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
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
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) {
            return false;
        }
        if (rank[rootA] < rank[rootB]) {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        if (rank[rootA] == rank[rootB]) {
            ++rank[rootA];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 250000, "n");
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;
    for (int edgeIndex = 1; edgeIndex <= n - 1; ++edgeIndex) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "edge %d is a self-loop at %d", edgeIndex, x);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge %d: %d %d", edgeIndex, x, y);
        ensuref(dsu.unite(x, y), "edge %d creates a cycle: %d %d", edgeIndex, x, y);
    }

    int q = inf.readInt(1, 250000, "q");
    inf.readEoln();

    for (int queryIndex = 1; queryIndex <= q; ++queryIndex) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        inf.readInt(1, n, "i");
        inf.readSpace();
        inf.readInt(1, n, "j");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");

        if (type == 1) {
            inf.readEoln();
        } else {
            inf.readSpace();
            int l = inf.readInt(1, n, "l");
            inf.readEoln();

            pair<int, int> closedEdge = minmax(k, l);
            ensuref(edges.count(closedEdge) != 0,
                    "query %d closes non-selected edge: %d %d",
                    queryIndex,
                    k,
                    l);
        }
    }

    inf.readEof();
    return 0;
}
