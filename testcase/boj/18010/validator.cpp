#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class DSU {
public:
    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 20, "K");
    inf.readEoln();

    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000, "m");
        inf.readEoln();

        inf.readInts(n, 0, 1000000, "w_i");
        inf.readEoln();

        DSU dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= m; ++i) {
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "y_i");
            inf.readEoln();

            ensuref(x != y, "self-loop at edge %d: %d %d", i, x, y);
            pair<int, int> edge = minmax(x, y);
            ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, x, y);
            dsu.unite(x, y);
        }

        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.find(v) == dsu.find(1), "graph is not connected: vertex %d", v);
        }

        inf.readInt(1, n, "s");
        inf.readEoln();
    }

    inf.readEof();
}
