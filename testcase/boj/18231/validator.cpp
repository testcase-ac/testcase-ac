#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    int maxEdges = n * (n - 1) / 2;
    ensuref(m <= maxEdges, "m=%d exceeds complete graph edge count %d for n=%d", m, maxEdges, n);

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i + 1, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i + 1, u, v);
    }

    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    vector<bool> destroyed(n + 1, false);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int p = inf.readInt(1, n, "p_i");
        ensuref(!destroyed[p], "duplicate destroyed city at position %d: %d", i + 1, p);
        destroyed[p] = true;
    }
    inf.readEoln();

    inf.readEof();
}
