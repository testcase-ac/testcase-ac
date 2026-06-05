#include "testlib.h"

#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct DisjointSet {
    vector<int> parent;
    vector<int> size;

    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    DisjointSet dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: (%d, %d)", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: (%d, %d)", i, u, v);
        dsu.unite(u, v);
    }

    ensuref(static_cast<int>(edges.size()) == n - 1, "expected %d edges, found %d", n - 1, static_cast<int>(edges.size()));
    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "tree is disconnected: vertex %d is not connected to vertex 1", v);
    }

    string colors = inf.readToken("[BR]{2,100000}", "c");
    ensuref(static_cast<int>(colors.size()) == n, "color string length is %d, expected %d", static_cast<int>(colors.size()), n);
    inf.readEoln();
    inf.readEof();
}
