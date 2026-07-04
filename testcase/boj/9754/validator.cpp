#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 200, "N");
        inf.readSpace();
        int k = inf.readInt(1, 10, "K");
        inf.readEoln();

        DSU dsu(n);
        set<pair<int, int>> edges;

        for (int i = 1; i <= n - 1; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readEoln();

            ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);

            auto edge = minmax(a, b);
            ensuref(edges.insert(edge).second,
                    "duplicate edge at edge %d: %d %d", i, a, b);
            ensuref(dsu.unite(a, b),
                    "edge %d creates a cycle: %d %d", i, a, b);
        }

        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == root, "node %d is disconnected", v);
        }
    }

    inf.readEof();
}
