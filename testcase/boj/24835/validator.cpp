#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int v) {
    if (parent[v] == v) return v;
    return parent[v] = findRoot(parent, parent[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    vector<int> dsu(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "loop at tree edge %d: (%d, %d)", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate tree edge %d: (%d, %d)", i, u, v);

        int ru = findRoot(dsu, u);
        int rv = findRoot(dsu, v);
        ensuref(ru != rv, "cycle formed by tree edge %d: (%d, %d)", i, u, v);
        dsu[ru] = rv;
    }

    int root = findRoot(dsu, 1);
    for (int v = 2; v <= n; ++v) {
        ensuref(findRoot(dsu, v) == root, "tree is disconnected at vertex %d", v);
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int k = inf.readInt(1, 1000000000, "k_i");
        inf.readEoln();

        ensuref(x != y, "query %d has x == y == %d", i, x);
        ensuref(edges.find(minmax(x, y)) == edges.end(),
                "query %d adds existing edge (%d, %d)", i, x, y);
        (void)a;
        (void)b;
        (void)k;
    }

    inf.readEof();
}
