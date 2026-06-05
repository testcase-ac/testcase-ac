#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 10000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 20000, "M");
        inf.readSpace();
        int p = inf.readInt(1, n, "p");
        inf.readSpace();
        int q = inf.readInt(1, n, "q");
        inf.readEoln();

        // CHECK: The statement describes p and q as two cities connected by the route being asked about.
        ensuref(p != q, "query route must connect two distinct cities: p=q=%d", p);

        vector<int> parent(n + 1);
        iota(parent.begin(), parent.end(), 0);

        auto findRoot = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };

        auto unite = [&](int a, int b) {
            a = findRoot(a);
            b = findRoot(b);
            if (a != b) {
                parent[b] = a;
            }
        };

        set<pair<int, int>> edges;
        set<int> weights;
        bool hasQueryEdge = false;
        pair<int, int> queryEdge = {min(p, q), max(p, q)};

        for (int i = 1; i <= m; ++i) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readSpace();
            int w = inf.readInt(1, 400000, "w");
            inf.readEoln();

            // CHECK: A road connects two cities, so self-loops are not valid road candidates.
            ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);

            pair<int, int> edge = minmax(u, v);
            ensuref(edges.insert(edge).second, "duplicate road at edge %d: %d %d", i, u, v);
            ensuref(weights.insert(w).second, "duplicate road length at edge %d: %d", i, w);

            if (edge == queryEdge) {
                hasQueryEdge = true;
            }
            unite(u, v);
        }

        // CHECK: The queried route is described as the road the engineer is considering building.
        ensuref(hasQueryEdge, "query road %d-%d is not among surveyed routes", p, q);

        int root = findRoot(1);
        for (int city = 2; city <= n; ++city) {
            ensuref(findRoot(city) == root, "graph is disconnected: city %d is not reachable from city 1", city);
        }
    }

    inf.readEof();
}
