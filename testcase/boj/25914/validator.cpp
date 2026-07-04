#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, min(1LL * n * (n - 1) / 2, 200000LL), "M");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u_i < v_i, got %d %d", i, u, v);
        ensuref(edges.insert({u, v}).second, "duplicate edge %d: %d %d", i, u, v);
    }

    set<int> salmon_vertices;
    for (int i = 1; i <= k; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readEoln();
        ensuref(salmon_vertices.insert(x).second, "duplicate salmon vertex %d: %d", i, x);
    }

    inf.readInt(0, 1, "c");
    inf.readEoln();
    inf.readEof();
}
