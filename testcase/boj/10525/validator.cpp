#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = findRoot(parent, parent[v]);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "n");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    set<pair<int, int>> edges;

    for (int edgeIndex = 1; edgeIndex < n; ++edgeIndex) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readEoln();

        ensuref(i != j, "loop at edge index %d: (%d, %d)", edgeIndex, i, j);

        pair<int, int> edge = minmax(i, j);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge index %d: (%d, %d)",
                edgeIndex,
                i,
                j);

        int rootI = findRoot(parent, i);
        int rootJ = findRoot(parent, j);
        if (rootI != rootJ) {
            parent[rootI] = rootJ;
        }
    }

    int root = findRoot(parent, 1);
    for (int node = 2; node <= n; ++node) {
        ensuref(findRoot(parent, node) == root,
                "graph is not connected: node %d is separated from node 1",
                node);
    }

    inf.readEof();
}
