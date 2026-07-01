#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = findRoot(parent, parent[x]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "n");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    set<pair<int, int>> edges;

    for (int i = 0; i < n; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u < v, found %d %d", i + 1, u, v);
        ensuref(edges.insert({u, v}).second,
                "duplicate edge at index %d: %d %d", i + 1, u, v);

        int ru = findRoot(parent, u);
        int rv = findRoot(parent, v);
        if (ru != rv) {
            parent[rv] = ru;
        }
    }

    int root = findRoot(parent, 1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(findRoot(parent, vertex) == root,
                "graph is disconnected; vertex %d is not reachable from vertex 1",
                vertex);
    }

    inf.readEof();
}
