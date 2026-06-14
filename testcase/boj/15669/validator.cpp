#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class DSU {
public:
    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
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

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "tree_u");
        inf.readSpace();
        int v = inf.readInt(1, n, "tree_v");
        inf.readEoln();

        ensuref(u != v, "tree edge %d is a loop: %d %d", i, u, v);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate tree edge %d: %d %d", i, u, v);
        ensuref(dsu.unite(u, v), "tree edge %d creates a cycle: %d %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "tree is disconnected; vertex %d is not connected to 1", v);
    }

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "query_u");
        inf.readSpace();
        int v = inf.readInt(1, n, "query_v");
        inf.readSpace();
        int c = inf.readInt(0, 1, "c");
        inf.readEoln();

        ensuref(u != v, "query %d has equal endpoints: %d %d", i, u, v);
        ensuref(edges.count(minmax(u, v)) != 0,
                "query %d uses non-edge direction %d -> %d with color %d", i, u, v, c);
    }

    inf.readEof();
}
