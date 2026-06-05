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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "A_i");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at index %d: (%d, %d)", i, a, b);
        ensuref(dsu.unite(a, b), "cycle created by edge index %d: (%d, %d)", i, a, b);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "tree is disconnected: vertex %d is not connected to 1", i);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "x_i");
        inf.readSpace();
        inf.readInt(1, n, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
