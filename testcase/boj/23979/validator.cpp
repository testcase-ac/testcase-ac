#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
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
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(2, 100000, "Q");
    inf.readEoln();

    DisjointSet dsu(n);
    set<pair<int, int>> edges;
    set<int> costs;

    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "edge_u");
        inf.readSpace();
        int v = inf.readInt(1, n, "edge_v");
        inf.readSpace();
        int c = inf.readInt(1, 200000, "C");
        inf.readEoln();

        ensuref(u != v, "tree edge %d is a loop: %d %d", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate tree edge %d: %d %d", i, u, v);
        ensuref(costs.insert(c).second, "duplicate tree edge cost at edge %d: %d", i, c);
        ensuref(dsu.unite(u, v), "tree edge %d creates a cycle: %d %d", i, u, v);
    }

    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == dsu.find(1), "tree is disconnected at vertex %d", v);
    }

    for (int i = 1; i <= q; ++i) {
        int u = inf.readInt(1, n, "query_u");
        inf.readSpace();
        int v = inf.readInt(1, n, "query_v");
        inf.readSpace();
        int w = inf.readInt(1, 200000, "w");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(u != v, "query %d adds a loop: %d %d", i, u, v);
        (void)w;
        (void)a;
        (void)b;
    }

    inf.readEof();
}
