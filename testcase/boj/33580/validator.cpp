#include "testlib.h"

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

    int n = inf.readInt(3, 5000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    set<pair<int, int>> edges;

    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "loop at edge index %d: (%d, %d)", i + 1, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i + 1, u, v);

        int rootU = findRoot(parent, u);
        int rootV = findRoot(parent, v);
        ensuref(rootU != rootV, "cycle formed at edge index %d: (%d, %d)", i + 1, u, v);
        parent[rootU] = rootV;
    }

    for (int i = 0; i < t; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, n, "C_i");
    }
    inf.readEoln();

    inf.readEof();
}
