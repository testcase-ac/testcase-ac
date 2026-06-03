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
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 500000, "M");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    set<long long> weights;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "U_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "V_i");
        inf.readSpace();
        long long c = inf.readLong(-1000000000LL, 1000000000LL, "C_i");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);

        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge %d between vertices %d and %d", i, edge.first, edge.second);
        ensuref(weights.insert(c).second, "duplicate weight at edge %d: %lld", i, c);

        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected: vertex %d is not connected to vertex 1", v);
    }

    inf.readEof();
}
