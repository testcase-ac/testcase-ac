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

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);

        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge %d: %d %d", i, u, v);

        dsu.unite(u, v);
        (void)w;
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected at vertex %d", v);
    }

    inf.readEof();
}
