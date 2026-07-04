#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 300000, "k");
    inf.readEoln();

    long long maxEdges = 1LL * n * (n - 1) / 2;
    ensuref(m <= maxEdges, "m=%d exceeds maximum simple graph edges for n=%d", m, n);

    vector<int> color(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        color[i] = inf.readInt(1, k, "a_i");
    }
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u_i < v_i, got (%d, %d)", i, u, v);
        ensuref(edges.insert({u, v}).second, "multiple edge at index %d: (%d, %d)", i, u, v);
        ensuref(color[u] != color[v],
                "given coloring is invalid at edge %d: (%d, %d) both have color %d",
                i, u, v, color[u]);
    }

    inf.readEof();
}
