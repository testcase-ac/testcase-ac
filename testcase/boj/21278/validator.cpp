#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
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

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(n - 1, maxEdges, "M");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: %d %d", i, a, b);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);

        int rootA = findRoot(parent, a);
        int rootB = findRoot(parent, b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }

    int root = findRoot(parent, 1);
    for (int i = 2; i <= n; ++i) {
        ensuref(findRoot(parent, i) == root, "graph is disconnected at vertex %d", i);
    }

    inf.readEof();
}
