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
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
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

    int n = inf.readInt(3, 1000, "n");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(n - 1, maxEdges, "m");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        // CHECK: the Korean statement says the positive cost is less than 100;
        // the English variant says 1 <= c <= 100.
        int c = inf.readInt(1, 99, "c");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop: %d", i, a);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at index %d: %d %d", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is not connected; vertex %d is disconnected", v);
    }

    int x = inf.readInt(1, n, "x");
    inf.readSpace();
    int y = inf.readInt(1, n, "y");
    inf.readSpace();
    int z = inf.readInt(1, n, "z");
    inf.readEoln();
    ensuref(x != y && x != z && y != z, "conference switches must be distinct: %d %d %d", x, y, z);

    inf.readEof();
}
