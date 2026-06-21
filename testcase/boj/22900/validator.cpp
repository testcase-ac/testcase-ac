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

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d", i, x);
        auto edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, x, y);
        ensuref(dsu.unite(x, y), "cycle introduced at edge %d: %d %d", i, x, y);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected at vertex %d", v);
    }

    inf.readEof();
}
