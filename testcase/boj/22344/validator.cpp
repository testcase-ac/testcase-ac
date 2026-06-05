#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int v) {
        while (parent[v] != v) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
    };

    set<pair<int, int>> edges;
    for (int j = 1; j <= m; ++j) {
        int a = inf.readInt(1, n, "a_j");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_j");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "c_j");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: %d %d", j, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", j, a, b);

        int ra = findRoot(a);
        int rb = findRoot(b);
        if (ra != rb) {
            parent[rb] = ra;
        }
    }

    int root = findRoot(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(findRoot(i) == root, "graph is not connected: vertex %d is disconnected from vertex 1", i);
    }

    inf.readEof();
}
