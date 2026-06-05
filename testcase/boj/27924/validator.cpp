#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
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

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u, v);
        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "edges do not form a connected tree; vertex %d is disconnected", v);
    }

    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readSpace();
    int c = inf.readInt(1, n, "c");
    inf.readEoln();
    ensuref(a != b && a != c && b != c, "a, b, and c must be pairwise distinct: %d %d %d", a, b, c);

    inf.readEof();
}
