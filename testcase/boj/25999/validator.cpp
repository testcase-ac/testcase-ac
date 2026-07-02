#include "testlib.h"

#include <algorithm>
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

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    set<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readLong(2LL, 1000000000LL, "h");
        inf.readEoln();

        ensuref(u != v, "self-loop at street %d: %d", i, u);

        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate street at index %d: (%d, %d)", i, u, v);

        int ru = findRoot(parent, u);
        int rv = findRoot(parent, v);
        if (ru != rv) parent[ru] = rv;
    }

    int root = findRoot(parent, 1);
    for (int v = 2; v <= n; ++v) {
        ensuref(findRoot(parent, v) == root,
                "intersection %d is not reachable from intersection 1", v);
    }

    inf.readEof();
}
