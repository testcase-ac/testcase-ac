#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        // CHECK: The statement describes direct connections as computer pairs, so the validator treats the network as a simple undirected graph.
        ensuref(u != v, "self-loop at edge %d: %d %d", i + 1, u, v);
        ensuref(edges.insert({min(u, v), max(u, v)}).second,
                "duplicate edge at edge %d: %d %d", i + 1, u, v);
    }

    inf.readEof();
    return 0;
}
