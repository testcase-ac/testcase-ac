#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, 1000000, "m");
    inf.readSpace();
    int k = inf.readInt(2, n, "k");
    inf.readEoln();

    vector<bool> hasWormhole(n + 1, false);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int planet = inf.readInt(1, n, "wormhole_i");
        ensuref(!hasWormhole[planet], "duplicate wormhole planet: %d", planet);
        hasWormhole[planet] = true;
    }
    inf.readEoln();

    DisjointSet dsu(n);
    unordered_set<long long> edges;
    edges.reserve(static_cast<size_t>(m) * 2);

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: (%d, %d)", i + 1, a, b);
        int u = min(a, b);
        int v = max(a, b);
        long long key = 1LL * u * (n + 1) + v;
        ensuref(edges.insert(key).second,
                "duplicate train edge at edge %d: (%d, %d)", i + 1, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int planet = 2; planet <= n; ++planet) {
        ensuref(dsu.find(planet) == root, "train graph is disconnected at planet %d", planet);
    }

    inf.readEof();
    return 0;
}
