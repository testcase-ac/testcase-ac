#include "testlib.h"

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

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int q = inf.readInt(1, m, "q");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: (%d, %d)", i, x, y);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: (%d, %d)", i, x, y);
        dsu.unite(x, y);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "initial graph is disconnected; vertex %d is separate", v);
    }

    vector<bool> removed(m + 1, false);
    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, m, "a");
        inf.readEoln();

        ensuref(!removed[a], "edge index %d is removed more than once", a);
        removed[a] = true;
    }

    inf.readEof();
}
