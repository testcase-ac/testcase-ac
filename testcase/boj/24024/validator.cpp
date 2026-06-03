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

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 200000, "M");
    inf.readSpace();
    long long x = inf.readLong(0LL, 1000000000LL, "X");
    inf.readEoln();

    (void)x;

    Dsu dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long w = inf.readLong(0LL, 1000000000LL, "w");
        inf.readSpace();
        int p = inf.readInt(0, 2, "p");
        inf.readEoln();

        (void)w;
        (void)p;

        ensuref(u != v, "self-loop at edge %d: %d", i, u);

        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)", i, u, v);

        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "graph is not connected: vertex %d is separated", i);
    }

    inf.readEof();
}
