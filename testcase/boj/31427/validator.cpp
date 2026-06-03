#include "testlib.h"

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

    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 100000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 20000, "Q");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        string z = inf.readToken("[ABCDE]", "z_i");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: %d %d", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "multiple edge at edge %d: %d %d", i, u, v);
        dsu.unite(u, v);
        (void)z;
    }

    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(1) == dsu.find(vertex), "graph is disconnected at vertex %d", vertex);
    }

    for (int j = 1; j <= q; ++j) {
        for (int k = 0; k < 5; ++k) {
            if (k > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 10000000, "cost");
        }
        inf.readEoln();
    }

    inf.readEof();
}
