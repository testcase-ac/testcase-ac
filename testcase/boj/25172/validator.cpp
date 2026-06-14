#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int maxEdges = min(1LL * n * (n - 1) / 2, 200000LL);
    // CHECK: The statement says M >= 1, but N = 1 is allowed and then the
    // stated upper bound forces M = 0.
    int m = inf.readInt(0, maxEdges, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at %d", i + 1, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "duplicate edge %d: %d %d", i + 1, u, v);
    }

    vector<bool> removed(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int vertex = inf.readInt(1, n, "removed_i");
        inf.readEoln();

        // CHECK: A length-N permanent deletion order over N vertices is treated
        // as a permutation so every listed deletion is meaningful.
        ensuref(!removed[vertex],
                "vertex %d appears more than once in the deletion list", vertex);
        removed[vertex] = true;
    }

    inf.readEof();
}
