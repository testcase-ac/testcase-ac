#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    parent[x] = findRoot(parent, parent[x]);
    return parent[x];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    vector<int> parent(n + 1), size(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
    set<pair<int, int>> edges;
    int components = n;

    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d", i, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u, v);

        int ru = findRoot(parent, u);
        int rv = findRoot(parent, v);
        if (ru != rv) {
            if (size[ru] < size[rv]) swap(ru, rv);
            parent[rv] = ru;
            size[ru] += size[rv];
            --components;
        }
    }

    ensuref(components == 1, "corridor graph is not connected");
    inf.readEof();
}
