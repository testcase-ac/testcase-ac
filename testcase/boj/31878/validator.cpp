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

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 111222, "N");
    inf.readEoln();

    set<int> values;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int value = inf.readInt(-1000000000, 1000000000, "A_i");
        ensuref(values.insert(value).second, "A_%d is not distinct: %d", i, value);
    }
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at vertex %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "edge %d is duplicated: %d %d", i, a, b);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle: %d %d", i, a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "tree is disconnected at vertex %d", v);
    }

    inf.readEof();
}
